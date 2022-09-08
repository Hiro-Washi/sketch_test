#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>

#include <SPI.h>

#include <Adafruit_I2CDevice.h>

#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_ST77xx.h>

#include <LiquidCrystal.h>

LiquidCrystal lcd( 4, 6, 10, 11, 12, 13 );

void setup() {
  lcd.begin( 16, 2 );
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
}

void loop() {

}
