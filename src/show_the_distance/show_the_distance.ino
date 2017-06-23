// Show Sharp distance sensor (GP2D12, 2Y0A21) value on m-bitbeam display (SSD1306). 

#include <SharpIR.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

constexpr int distance_sensor_pin = A1;

// Create a new instance of the library
SharpIR sensor(GP2Y0A21YK0F, distance_sensor_pin);

// Variable for manual calculation
float calc_distance = 0;
int raw_val = 0;
int lib_distance = 0;

constexpr int oled_reset = 4;
Adafruit_SSD1306 display(oled_reset);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  display.setTextColor(WHITE);
}

void loop() {
  lib_distance = sensor.getDistance();
  raw_val = analogRead(A1); // Get sensor value for manual calculation of the distance
  calc_distance = (6787.0 / (raw_val - 3.0)) - 4.0; // Calculate distance
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Sharp distance sensor");
  display.print("Raw ADC value: ");
  display.print(raw_val, DEC);
  display.print("\n");
  display.print("Library value: ");
  display.print(lib_distance, DEC);
  display.print("cm\n");
  display.print("Calculated val.: ");  
  display.print((int)calc_distance, DEC);
  display.print("cm\n");
  display.display();
  delay(500); // Wait a half second
}
