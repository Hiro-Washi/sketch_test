/*************************************************************
 * Test program for 480x320 TFT-LCD w/ILI9488(18bit-color)
 * for Arduino Mega, using LCDWIKI libraries.
 *                May 22, 2021              Akira Tominaga
 * ***********************************************************/
#include "LCDWIKI_GUI.h"     // Core graphics library
#include "LCDWIKI_SPI.h"     // SPI library
#define MODEL ILI9488_18     // LCD's IC model selection
// HW-SPI pins: DI(MOSI)=51, SDO(MISO)=50(unused), and SCK=52
// the other LCD pins are to any pins 
#define CS   10              // or to ground if no other SPI used
#define CD   9
#define RST  8
#define LED  -1             // to declare unused (set to 3.3V)
// generate class lcd
LCDWIKI_SPI lcd(MODEL, CS, CD, RST, LED);
uint16_t wW;
uint16_t hH;
uint16_t testNum = 0;

void setup() { // ***** Arduino setup() *****
  Serial.begin(9600);
  wW = lcd.Get_Display_Height();
  hH = lcd.Get_Display_Width();
  Serial.print("*** TFT-LCD ");
  Serial.print(wW);
  Serial.print("x");
  Serial.println(hH);
  lcd.Init_LCD();
  lcd.Fill_Screen(0x0);
  lcd.Set_Rotation(1);   // rotate screen by 90 degrees
  //display main panel
  lcd.Set_Draw_color(16, 16, 96);
  lcd.Fill_Rectangle(0, 0, wW - 1, 19); // draw header bar
  lcd.Set_Text_Mode(1);
  lcd.Set_Text_Size(2);
  lcd.Set_Text_colour(255, 255, 255);
  lcd.Set_Text_Back_colour(0);
  lcd.Print_String("TFT-LCD test with LCDWIKI", CENTER, 3);
  //
  lcd.Fill_Rectangle(0, hH - 19, wW - 1, hH - 1); // draw footer
  lcd.Print_String("<https://a-tomi.hatenablog.com/>", CENTER, hH - 17);
  //
  lcd.Set_Draw_color(255, 0, 0);
  lcd.Draw_Rectangle(0, 20, wW - 1, hH - 20);
}

void loop() { // ***** Arduino loop() *****
  // *** Print_String
  String s = "Test ";
  s.concat(String(testNum));
  lcd.Set_Draw_color(0, 0, 0);
  lcd.Fill_Rectangle(100, 24, 340, 48);
  lcd.Set_Text_Size(3);
  lcd.Set_Text_colour(255, 255, 0);
  lcd.Print_String(s, CENTER, 24);
  // *** Draw  pixel for sin wave
  lcd.Set_Draw_color(0, 255, 255);
  for (int i = 1; i < wW - 1; i++)  {
    lcd.Draw_Pixel(i, hH / 2 + 3 + (sin((i * 3.14 + testNum * 20) / 180) * 100));
  }
  // *** Fill_Circle(x,y,r)
  lcd.Set_Draw_color(testNum * 5, 0, 255 - testNum * 5);
  lcd.Fill_Circle(wW / 2, hH / 2 + 1, testNum * 2);
  //
  delay(1000);
  testNum++;
  if (testNum > 51) {
    Serial.println("*** End ***");
    while (true) {}
  }
}
/* End of Test Program */
