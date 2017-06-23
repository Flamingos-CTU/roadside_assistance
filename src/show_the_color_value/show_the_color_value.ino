// Show obstacle avoidance sensor value (TCRT5000) on m-bitbeam display (SSD1306). 

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define DIST_SENSOR_PIN A0

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

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
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("IR obstacle sensor");
  display.println("(line follower)");
  display.setTextSize(2);
  display.println(analogRead(DIST_SENSOR_PIN), DEC);
  display.display();
  delay(100);
}
