#include <SoftwareSerial.h>
#include <Ultrasonic.h>

// SW serial to main control board
SoftwareSerial sensor_serial(4, 5); // RX, TX, SW serial could work only with RX mapped to pin 8, 9, 10, 11

Ultrasonic ul(6, 7);  // An ultrasonic sensor HC-04
Ultrasonic ur(8, 9);  // An ultrasonic sensor HC-04
Ultrasonic ub(10, 11);  // An ultrasonic sensor HC-04
Ultrasonic uf(12, 13);  // An ultrasonic sensor HC-04

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
  // put your setup code here, to run once:
  sensor_serial.begin(4800);
  memset(sens_vals, 255, sizeof(sens_vals));
}

void loop() {

  sens_vals[UF] = uf.distanceRead(CM);
  sens_vals[UB] = ub.distanceRead(CM);
  sens_vals[UL] = ul.distanceRead(CM);
  sens_vals[UR] = ur.distanceRead(CM);

  sens_vals[LL] = analogRead(1)>>2;
  sens_vals[LR] = analogRead(3)>>2;
  sens_vals[LML] = analogRead(0)>>2;
  sens_vals[LMR] = analogRead(4)>>2;
  sens_vals[LC] = analogRead(2)>>2;
  
  sensor_serial.print("ST ");
  sensor_serial.print(sens_vals[UF], DEC);
  sensor_serial.print(" ");
  sensor_serial.print(sens_vals[UB], DEC);
  sensor_serial.print(" ");
  sensor_serial.print(sens_vals[UL], DEC);
  sensor_serial.print(" ");
  sensor_serial.print(sens_vals[UR], DEC);
  
  sensor_serial.print(" ");
  sensor_serial.print(sens_vals[LL], DEC);
  sensor_serial.print(" ");
  sensor_serial.print(sens_vals[LR], DEC);
  sensor_serial.print(" ");
  sensor_serial.print(sens_vals[LML], DEC);
  sensor_serial.print(" ");
  sensor_serial.print(sens_vals[LMR], DEC);
  sensor_serial.print(" ");
  sensor_serial.println(sens_vals[LC], DEC);
 
  delay(100);
}
