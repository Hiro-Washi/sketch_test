#include <ros.h>
#include <std_msgs/String.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#define TFT_CS   5
#define TFT_RST  4
#define TFT_DC   22
#define TFT_SCLK 18
#define TFT_MOSI 23
#define display_width 160
#define display_height 80
#define ROS_INFO
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
int display_pixel_x, display_pixel_y, Offset_pixel = 20;
ros::NodeHandle nh;

void espCB(const std_msgs::String& eye_topic) {
  ROS_INFO(eye_topic.data);

  if (eye_topic.data == "true") {
    Serial.print(eye_topic.data);
    Emoji("(^u^)", ST7735_YELLOW);
  }
  else if (eye_topic.data == "false") {
    Serial.print(eye_topic.data);
    Emoji("(xox)", ST7735_BLUE);
  }
  else {
    void(0); //pass
  }
  delay(3000);
  tft.fillScreen(ST7735_BLACK);
}

ros::Subscriber<std_msgs::String> sub("eye_topic", &espCB );

void setup(void) {
  nh.initNode();
  nh.subscribe(sub);
    //Serial.begin(9600);           ＜ーーコイツガハンニン、コイツキライ
  tft.initR(INITR_MINI160x80);
  tft.setRotation(3);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(3);
  tft.setCursor(15, 15);
  tft.print("SUTA-TO!");
  delay(1000);
  tft.fillScreen(ST7735_BLACK);
}

void loop(void) {
  Serial.print("waiting for message");
  tft.fillScreen(ST7735_WHITE);
  Emoji("(^o^)", ST7735_GREEN);
  delay(500);
  tft.fillScreen(ST7735_MAGENTA);
  Emoji("(-_-)", ST7735_BLUE);
  delay(500);
  tft.fillScreen(ST7735_BLACK);  
  nh.spinOnce();
}


void Emoji(char *text, uint16_t color) {
  tft.setCursor(5, 15);
  tft.setTextSize(5);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
