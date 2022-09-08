
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

//ディスプレイの配線
#define TFT_CS     6
#define TFT_RST    5
#define TFT_DC     7
#define TFT_SCLK 13
#define TFT_MOSI 11

//Display Size
#define display_width 160
#define display_height 80

//ST7735のクラス定義
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

int display_pixel_x,display_pixel_y,Offset_pixel=20;
int16_t max_result;
int16_t result = 100;
float multiplier = 1.0f;

void setup(void) {
  Serial.begin(9600);

  // Use this initializer (uncomment) 
  //if you're using a 0.96" 180x60 TFT
  tft.initR(INITR_MINI160x80);

  //画面のローテーション
  tft.setRotation(3);

  tft.fillScreen(ST7735_BLACK);
  TextWrap("Agricalture Chair System", ST7735_GREEN);
  delay(1000);
}

void loop() {  
  result = result -1;

  if(result < 0) result = 100;

  //Show Word
  TextWrap("ThreshHold", ST7735_RED);

  //Max update
  max_result = MaxUpdate(max_result, result);

  //Draw LineGraph
  DrawLineGraph(result, max_result);

  //Draw Axis
  DrawAxis_x();

  Serial.println(result);
  delay(10);
}

void TextWrap(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

int16_t MaxUpdate(int16_t max_result, int16_t result){
  //Max update
  if(max_result < result){
    max_result = result;
    tft.fillScreen(ST7735_BLACK);
  }

  return max_result;
}

void DrawLineGraph(int value ,int max_result){
  //表示ディスプレイの範囲
  int16_t display_max_height = 70;
  int16_t display_min_height = 20;

  //mapで表示範囲の変換
  int16_t graph_result = map(value,0,max_result,display_max_height,display_min_height);
  tft.drawLine(display_pixel_x + Offset_pixel, display_pixel_y, display_pixel_x + Offset_pixel + 1, graph_result, ST7735_WHITE);

  display_pixel_y = graph_result;
  display_pixel_x++;

  //update line display
  if(display_pixel_x + Offset_pixel > display_width){
    display_pixel_x = 0;
    tft.fillScreen(ST7735_BLACK);
  }  
}

int16_t map_normalize(int16_t value, int16_t max_result){
  //表示ディスプレイの範囲
  int16_t display_max_height = 70;
  int16_t display_min_height = 20;

  //mapで表示範囲の変換
  int16_t graph_result = map(value,0,max_result,display_max_height,display_min_height);
  tft.drawLine(display_pixel_x + Offset_pixel, display_pixel_y, display_pixel_x + Offset_pixel + 1, graph_result, ST7735_WHITE);
}

void DrawAxis_x(){
  //表示ディスプレイの範囲
  int16_t display_max_height = 70;
  int16_t display_min_height = 20;

  int16_t axis_x = 45;
  tft.drawLine(display_pixel_x + Offset_pixel, axis_x, display_width, axis_x, ST7735_RED);
  tft.drawLine(20, display_min_height, 20, display_max_height, ST7735_RED);

  tft.setTextSize(1);
  tft.setCursor(0, axis_x);
  tft.print("0");
  tft.setCursor(0, display_min_height);
  tft.print("20");
  tft.setCursor(0, display_max_height);
  tft.print("-20");
}
