#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
 
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "OakOLED.h"
#define REPORTING_PERIOD_MS 1000
OakOLED oled;
 
PulseOximeter pox;
 
uint32_t tsLastReport = 0;
 
const unsigned char bitmap [] PROGMEM=
{
0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x00, 0x0f, 0xe0, 0x7f, 0x00, 0x3f, 0xf9, 0xff, 0xc0,
0x7f, 0xf9, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xf0,
0xff, 0xf7, 0xff, 0xf0, 0xff, 0xe7, 0xff, 0xf0, 0xff, 0xe7, 0xff, 0xf0, 0x7f, 0xdb, 0xff, 0xe0,
0x7f, 0x9b, 0xff, 0xe0, 0x00, 0x3b, 0xc0, 0x00, 0x3f, 0xf9, 0x9f, 0xc0, 0x3f, 0xfd, 0xbf, 0xc0,
0x1f, 0xfd, 0xbf, 0x80, 0x0f, 0xfd, 0x7f, 0x00, 0x07, 0xfe, 0x7e, 0x00, 0x03, 0xfe, 0xfc, 0x00,
0x01, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x3f, 0xc0, 0x00,
0x00, 0x0f, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
 
void onBeatDetected()
{
Serial.println("Beat!");
oled.drawBitmap( 60, 20, bitmap, 28, 28, 1);
oled.display();
}
 
void setup()
{
Serial.begin(9600);
 
oled.begin();
oled.clearDisplay();
oled.setTextSize(1);
oled.setTextColor(1);
oled.setCursor(0, 0);
 
oled.println("Initializing pulse oximeter..");
oled.display();
Serial.print("Initializing pulse oximeter..");
 
if (!pox.begin()) {
Serial.println("FAILED");
oled.clearDisplay();
oled.setTextSize(1);
oled.setTextColor(1);
oled.setCursor(0, 0);
oled.println("FAILED");
oled.display();
for(;;);
} else {
oled.clearDisplay();
oled.setTextSize(1);
oled.setTextColor(1);
oled.setCursor(0, 0);
oled.println("SUCCESS");
oled.display();
Serial.println("SUCCESS");
}
pox.setOnBeatDetectedCallback(onBeatDetected);
}
 
void loop()
{
pox.update();
 
if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
Serial.print("Heart BPM:");
Serial.print(pox.getHeartRate());
Serial.print("-----");
Serial.print("Oxygen Percent:");
Serial.print(pox.getSpO2());
Serial.println("\n");
oled.clearDisplay();
oled.setTextSize(1);
oled.setTextColor(1);
oled.setCursor(0,16);
oled.println(pox.getHeartRate());
if (pox.getSpO2() > 105) {
      //noTone(8);
      // play a note on pin 8 for 500 ms:
      noTone(8);//, 523, 100); 
      }
oled.setTextSize(1);
oled.setTextColor(1);
oled.setCursor(0, 0);
oled.println("Heart BPM");
 
oled.setTextSize(1);
oled.setTextColor(1);
oled.setCursor(0, 30);
oled.println("Spo2");
 
oled.setTextSize(1);
oled.setTextColor(1);
oled.setCursor(0,45);
oled.println(pox.getSpO2());
oled.display();
tsLastReport = millis();
}
if (pox.getSpO2() < 90) {
      //noTone(8);
      // play a note on pin 8 for 500 ms:
      noTone(8);//, 523, 100); 
      }
      else{
      tone(8, 523, 500);
      }
}
