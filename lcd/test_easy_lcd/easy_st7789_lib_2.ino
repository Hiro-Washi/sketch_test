#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.initR(INITR_GREENTAB);
 //
  tft.fillScreen(ST7789_BLACK);
  tft.setRotation(0);
  tft.setTextColor(ST7789_GREEN);
  tft.setCursor(1,60);
  tft.print(“Hellow World”);
  }

void loop() {

}
