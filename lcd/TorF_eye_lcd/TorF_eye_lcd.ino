#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <stdlib.h>
#include <time.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h> ///
#define TFT_RST    5
#define TFT_DC     6
#define TFT_CS     7
#define TFT_SCLK 13
#define TFT_MOSI 11
#define display_width 160
#define display_height 80
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
int  r,display_pixel_x, display_pixel_y, Offset_pixel = 2;
char success[20] = "recieved message", miss[20] = "missed message";

ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher res_pub("lcd_res", &str_msg);
//ros::Publisher pub =
//nh.advertise<pkg::MSG_FILE>("ros_msg", 10);
//PKG::MSG_FILE msg;  msg.data = ***;  pub.publish(msg);

#define ROS_INFO

void lcdCB( const std_msgs::Bool& msg) 
{
  res_pub.publish(&str_msg);
  //char str_msg = msg.data; ROS_INFO(msg); ROS_INFO(msg.data);
  nh.loginfo("msg.data");
  if (msg.data) {
    tft.fillScreen(ST7735_YELLOW);
    Emoji("(^v^)", ST7735_BLACK);
    delay(3000);
  }

  else {
    tft.fillScreen(ST7735_BLUE);
    Emoji("(x_x)", ST7735_BLACK);
    delay(3000);
  }
  tft.fillScreen(ST7735_BLACK);
}

ros::Subscriber<std_msgs::String> eye_sub("eye_control", &lcdCB );

void setup(void)
{
  nh.initNode();
  nh.subscribe(eye_sub);
  nh.advertise(res_pub);

  tft.initR(INITR_MINI160x80);
  tft.setRotation(3);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(3);
  tft.setCursor(15, 15);
  tft.setTextColor(ST7735_BLUE);
  tft.print("GEN-3-");
  delay(1000);
  tft.fillScreen(ST7735_BLACK);
  Emoji("(0_0)", ST7735_GREEN);
}

void loop(void) {
  srand((unsigned int)time(NULL));
  r = rand()%30;
  nh.loginfo("Waiting for message");
  if (r = 1) {
    tft.fillScreen(ST7735_BLACK);
    Emoji("(-_-)", ST7735_GREEN);
    delay(500);
    tft.fillScreen(ST7735_BLACK);
    Emoji("(0_0)", ST7735_GREEN); // MAGENTA
  }
  delay(200); 
  nh.spinOnce();
  //if (ROS.available) delay(3000);
}

void Emoji(char *text, int color) {
  tft.setCursor(5, 15);
  tft.setTextSize(5);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
