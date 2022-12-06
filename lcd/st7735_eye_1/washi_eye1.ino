#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#define TFT_RST    5
#define TFT_DC     6
#define TFT_CS     7
#define TFT_SCLK 13
#define TFT_MOSI 11
#define display_width 160
#define display_height 80
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
int display_pixel_x, display_pixel_y, Offset_pixel = 2;

char success = , error;

ros::NodeHandle nh;
#define ROS_INFO

// after reUceive chatter
void lcdCB( const std_msgs::String& msg) {
  //char str_msg = msg.data;
  //ROS_INFO(msg);
  //ROS_INFO(msg.data);
  nh.loginfo(msg.data);
  char success, error;
  if (msg.data == success) {
    tft.fillScreen(ST7735_YELLOW);
    Emoji("(^O^)", ST7735_BLACK);
    delay(3000);
  }
  else if (msg.data == 'error') {
    tft.fillScreen(ST7735_BLUE);
    Emoji("(x_x)", ST7735_BLACK);
    
    delay(3000);
  }
  else {
    void(0); //pass
  }
  tft.fillScreen(ST7735_BLACK);
}

ros::Subscriber<std_msgs::String> sub("eye_topic", &arduinoCB );

void setup(void) {
  nh.initNode();
  nh.subscribe(sub);
  //Serial.begin(9600);           ＜ーーコイツガハンニン、コイツキライ
  tft.initR(INITR_MINI160x80);
  tft.setRotation(3);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(3);
  tft.setCursor(15, 15);
  tft.setTextColor(ST7735_BLUE);
  tft.print("SUTA-TO!");
  delay(1000);

  tft.fillScreen(ST7735_BLACK);
}

void loop(void) {
  nh.loginfo("Waiting for message");
  tft.fillScreen(ST7735_BLACK);
  Emoji("(-o-)", ST7735_GREEN);
  delay(400);
  //tft.fillScreen(ST7735_MAGENTA);
  tft.fillScreen(ST7735_BLACK);
  Emoji("(-_-)", ST7735_CYAN);
  delay(400);
  //tft.fillScreen(ST7735_BLACK);  
  nh.spinOnce();
  //if (ROS.available) delay(3000);
}

void Emoji(char *text, int color) {
  tft.setCursor(5, 15);
  tft.setTextSize(5);
  tft.setTextColor(color);
  tft.setTextWrap(true); //行を折り返す
  tft.print(text);
}
