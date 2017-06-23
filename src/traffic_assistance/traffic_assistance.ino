#include <Automaton.h>
#include "Atm_traffic_assistance.h"
#include "Pin_layout.h"
#include <SoftwareSerial.h>

// Sketch for main Arduino board executing match finite state machine (FSM)

// Match FSM
Atm_traffic_assistance traffic_assistance;
// Start button FSM
Atm_button button;

SoftwareSerial sensor_serial(8, 9); // RX, TX, SW serial to main control board
char sensor_buffer[128];
Atm_command sensor_board;

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
};

constexpr char sensor_list[] = "ST UF UB UL UR LL LR LML LMR LC";

void on_sensor_data(int idx, int v, int up)
{
  uint8_t val = atoi(sensor_board.arg(1));
  switch(v) {
    case ST:
    case UF:
    case UB:
    case UL:
    case UR:
    case LL:
    case LR:
    case LML:
    case LMR:
    case LC:
      Serial.print("CMD ");
      Serial.print(v, DEC);
      Serial.print(" VALS: ");
      Serial.print(sensor_board.arg(1));
      Serial.print(" ");
      Serial.print(sensor_board.arg(2));
      Serial.print(" ");
      Serial.print(sensor_board.arg(3));
      Serial.print(" ");
      Serial.println(sensor_board.arg(4));
  }
}

void setup() {
  // Init main serial line for programming and debugging purposes
  Serial.begin(115200);
  traffic_assistance.trace(Serial);
  button.trace(Serial);
  //sensor_board.trace(Serial);

  // Init serial for communication with sensor board
  sensor_serial.begin(4800);
  
  // Init FSMs
  traffic_assistance.begin();
  button.begin(start_button_pin).onPress(traffic_assistance, traffic_assistance.EVT_START);
  sensor_board.begin(sensor_serial, sensor_buffer, sizeof(sensor_buffer))
    .list(sensor_list)
    .onCommand(on_sensor_data,1);
}

void loop() {
  automaton.run();
}


