#include <Ultrasonic.h>

constexpr long scan_period = 100; //period of measurement of data


Ultrasonic ul(6, 7, 10000UL);  // left ultrasonic sensor HC-04
Ultrasonic ur(8, 9, 10000UL);  // right ultrasonic sensor HC-04
Ultrasonic ub(10, 11, 10000UL);  // back ultrasonic sensor HC-04
Ultrasonic uf(12, 13, 10000UL);  // front ultrasonic sensor HC-04

enum {
  UF,       // Front ulstrasound sensor,
  UB,       // back (rear),
  UL,       // left,
  UR,       // right.
  LL,       // Left front line sensor,
  LR,       // front right,
  LML,      // middle left,
  LMR,      // middle right,
  LC,       // center.
  NOS       // Number of sensors
};

uint8_t sens_vals[NOS];

void setup() {
  // hardware serial used for debugging
  Serial.begin(115200);
  // software serial used for communication with main board
  Serial1.begin(115200);
  pinMode(5, INPUT);           // set pin to input
  digitalWrite(5, HIGH); 
}

void loop() {
  long scan_start = millis();

  // reading ultrasonic distances
  sens_vals[UF] = uf.distanceRead(CM);
  sens_vals[UB] = ub.distanceRead(CM);
  sens_vals[UL] = ul.distanceRead(CM);
  sens_vals[UR] = ur.distanceRead(CM);

  // reading line sensors values
  // value is converted to range 0..255 (originaly was 0..1024)
  sens_vals[LL] = analogRead(1)>>2; 
  sens_vals[LR] = analogRead(3)>>2;
  sens_vals[LML] = analogRead(0)>>2;
  sens_vals[LMR] = analogRead(4)>>2;
  sens_vals[LC] = analogRead(2)>>2;
  
  long send_start = millis();
  if(digitalRead(5)==0){
      Serial1.begin(115200);
      // send the data
      Serial1.print("ST");
      for(int i=0; i<NOS; i++){
        Serial1.print(" ");
        Serial1.print(sens_vals[i], DEC);
      }
      Serial1.println();
  }
  else{
      Serial1.end();  
  }
  
  //debugging output... length of measurement
  Serial.print("measure time: ");
  Serial.println(send_start-scan_start,DEC);

  //debugging output... length of measurement
  Serial.print("sending time: ");
  Serial.println(millis()-send_start,DEC);

  // wait for next period start
  while(millis()< (scan_start + scan_period));
}
