#include <Automaton.h>
#include "Atm_traffic_assistance.h"
#include "Atm_differential_motion.h"
#include "Pin_layout.h"

// Sketch for main Arduino board executing match finite state machine (FSM)

// Match FSM
Atm_traffic_assistance traffic_assistance;
// Start button FSM
Atm_button button;

char sensor_buffer[40];
Atm_command sensor_board;
//Atm_timer sensor_data_timer;
Atm_differential_motion motion;

constexpr uint16_t sensor_data_timeout = 1000; // ms

constexpr uint8_t obstacleThresh = 40; // obstackle detected if closer than this distance in cm
constexpr uint8_t blackThresh = 25; // black color when sensor output above this value 

struct sens_environment environment;

enum {
  ST,
  UF,       // Front ulstrasound sensor,
  UB,       // back (rear),
  UL,       // left,
  UR,       // right.
  LL,       // Left front line sensor,
  LR,       // front right,
  LML,      // middle left,
  LMR,      // middle right,
  LC,       // center.
  LRL,      // rear left
  LRR       // rear right
};

constexpr char sensor_list[] = "ST";

void on_sensor_data(int idx, int v, int up)
{
  static uint8_t loopCounter=0;
  switch(v) {
    case ST:
        //sensor_data_timer.start();
        environment.obstacleFront = atoi(sensor_board.arg(UF)) > 0 && atoi(sensor_board.arg(UF)) < obstacleThresh;
        environment.obstacleBack = atoi(sensor_board.arg(UB)) > 0 && atoi(sensor_board.arg(UB)) < obstacleThresh;
        environment.obstacleLeft = atoi(sensor_board.arg(UL)) > 0 && atoi(sensor_board.arg(UL)) < obstacleThresh;
        environment.obstacleRight = atoi(sensor_board.arg(UR)) > 0 && atoi(sensor_board.arg(UR)) < obstacleThresh;
        environment.blackLM = atoi(sensor_board.arg(LC)) > blackThresh;
        environment.blackLL = atoi(sensor_board.arg(LL)) > blackThresh;
        environment.blackLR = atoi(sensor_board.arg(LR)) > blackThresh;
        environment.blackLML = atoi(sensor_board.arg(LML)) > blackThresh;
        environment.blackLMR = atoi(sensor_board.arg(LMR)) > blackThresh;        
        uint8_t right = analogRead(3) >> 2;
        uint8_t left = analogRead(2) >> 2;
        environment.blackLRR = right > blackThresh;
        environment.blackLRL = left > blackThresh;
        if(((++loopCounter) & 0x1F) == 0 ){
            Serial.println();
            Serial.println("sensor_board:\tUF\tUB\tUL\tUR\tLL\tLR\tLML\tLMR\tLC\tLRL\tLRR");
            Serial.print("raw_values:");
            for(uint8_t i=1;i<=9;i++){
                Serial.print("\t");
                Serial.print(sensor_board.arg(i));
            }
            Serial.print("\t");
            Serial.print(left,DEC);
            Serial.print("\t");
            Serial.print(right,DEC);
            Serial.println();
            Serial.print("detection:\t");
            Serial.print(environment.obstacleFront?1:0,DEC);
            Serial.print("\t");
            Serial.print(environment.obstacleBack,DEC);
            Serial.print("\t");
            Serial.print(environment.obstacleLeft,DEC);
            Serial.print("\t");
            Serial.print(environment.obstacleRight,DEC);
            Serial.print("\t");
            Serial.print(environment.blackLL,DEC);
            Serial.print("\t");
            Serial.print(environment.blackLR,DEC);
            Serial.print("\t");
            Serial.print(environment.blackLML,DEC);
            Serial.print("\t");
            Serial.print(environment.blackLMR,DEC);
            Serial.print("\t");
            Serial.print(environment.blackLM,DEC);
            Serial.print("\t");
            Serial.print(environment.blackLRL,DEC);
            Serial.print("\t");
            Serial.print(environment.blackLRR,DEC);
            Serial.println();
        }
  }
}

void setup() {
  // Init main serial line for programming and debugging purposes
  Serial.begin(115200);
  traffic_assistance.trace(Serial);
  button.trace(Serial);
 
  // Init FSMs
  traffic_assistance.begin();
  //sensor_data_timer.begin(sensor_data_timeout);
  //sensor_data_timer.start();
  
  button.begin(start_button_pin).onPress([] (int idx, int v, int up) {
    traffic_assistance.trigger(traffic_assistance.EVT_START);
  });
  pinMode(8, OUTPUT);           // set pin to input
  digitalWrite(8, LOW); 
  sensor_board.begin(Serial, sensor_buffer, sizeof(sensor_buffer))
    .list(sensor_list)
    .onCommand(on_sensor_data,1);
  //sensor_data_timer.trace(Serial);
  motion.begin();
  motion.trace(Serial);
}

void loop() {
  automaton.run();
}


