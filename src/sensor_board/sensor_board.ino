#include <SoftwareSerial.h>
#include <Ultrasonic.h>

constexpr long scan_period = 100; //period of measurement of data

// SW serial to main control board
SoftwareSerial sensor_serial(4, 5); // RX, TX, SW serial could work only with RX mapped to pin 8, 9, 10, 11

Ultrasonic ul(6, 7);  // left ultrasonic sensor HC-04
Ultrasonic ur(8, 9);  // right ultrasonic sensor HC-04
Ultrasonic ub(10, 11);  // back ultrasonic sensor HC-04
Ultrasonic uf(12, 13);  // front ultrasonic sensor HC-04

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
  sensor_serial.begin(4800);
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

  // send the data
  sensor_serial.print("ST");
  for(int i=0; i<NOS; i++){
    sensor_serial.print(" ");
    sensor_serial.print(sens_vals[i], DEC);
  }
  sensor_serial.println();

  //debugging output... length of measurement
  Serial.print("measure time: ");
  Serial.println(millis()-scan_start,DEC);

  // wait for next period start
  while(millis()< (scan_start + scan_period));
}
