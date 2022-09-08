#include <ILI9488_t3.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include "ILI9488_t3_font_Arial.h"
#include "ILI9488_t3_font_ArialBold.h"

// TFT LCD and Touch Screen 3.5",Teensy 4.0
const int TFT_DC = 6; // For optimized ILI9488_t3 library
const int TFT_CS = 7;
const int TFT_MOSI = 11;
//const int TFT_MISO = 12;
const int TFT_SCLK = 13;
//const int TFT_RST = 255; // Not used
//const int Touch_CS = 6; // CS signal for Resistive Touchscreen

// Initialize the Touchscreen
XPT2046_Touchscreen ts(Touch_CS);
// Initialize the LCD
ILI9488_t3 tft = ILI9488_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);

void setup() {
Serial.begin(38400);
tft.begin();
tft.setRotation(3);
tft.fillScreen(ILI9488_BLACK);
ts.begin();
ts.setRotation(3);
while (!Serial && (millis() <= 1000));
}

boolean wastouched = true;

void loop() {
boolean istouched = ts.touched();
if (istouched) {
TS_Point p = ts.getPoint();
if (!wastouched) {
tft.fillScreen(ILI9488_BLACK);

tft.drawRect(0, 0, 479, 319, ILI9488_WHITE);
tft.fillRect(40, 30, 10, 200, ILI9488_WHITE);
tft.fillCircle(45, 20, 10, ILI9488_YELLOW);
tft.fillRect(60, 30, 100, 60, ILI9488_WHITE);
tft.fillCircle(110, 60, 20, ILI9488_RED);

tft.drawCircle(250, 60, 30, ILI9488_BLUE);tft.drawCircle(250, 60, 26, ILI9488_BLUE);
tft.drawCircle(285, 90, 30, ILI9488_YELLOW);tft.drawCircle(285, 90, 26, ILI9488_YELLOW);
tft.drawCircle(320, 60, 30, ILI9488_WHITE);tft.drawCircle(320, 60, 26, ILI9488_WHITE);
tft.drawCircle(355, 90, 30, ILI9488_GREEN);tft.drawCircle(355, 90, 26, ILI9488_GREEN);
tft.drawCircle(390, 60, 30, ILI9488_RED);tft.drawCircle(390, 60, 26, ILI9488_RED);
tft.setTextColor(ILI9488_WHITE);
tft.setFont(Arial_16);
tft.setCursor(250, 130);
tft.print("TOKYO 2021");

tft.setTextColor(ILI9488_YELLOW);
tft.setFont(Arial_40);
tft.setCursor(60, 180);
tft.print("Touch");
tft.setFont(Arial_24);
tft.setCursor(30, 240);
tft.print("3.5(inch) TFT SPI ILI9488");
tft.setCursor(20, 280);
tft.print("480*320(Pixel)RGB 65K color");
}
tft.fillRect(260, 170, 140, 60, ILI9488_BLACK);
tft.setTextColor(ILI9488_GREEN);
tft.setFont(Arial_24);
tft.setCursor(260, 170);
tft.print("X = ");
tft.print(p.x);
tft.setCursor(260, 200);
tft.print("Y = ");
tft.print(p.y);
Serial.print(", x = ");
Serial.print(p.x);
Serial.print(", y = ");
Serial.println(p.y);
} else {
if (wastouched) {
tft.fillScreen(ILI9488_BLACK);
tft.setTextColor(ILI9488_RED);
tft.setFont(Arial_48);
tft.setCursor(190, 100);
tft.print("No");
tft.setCursor(140, 170);
tft.print("Touch");
}
Serial.println("no touch");
}
wastouched = istouched;
delay(100);
}
Read less
Customer imageCustomer image
Helpful
Report abuse
See all reviews
