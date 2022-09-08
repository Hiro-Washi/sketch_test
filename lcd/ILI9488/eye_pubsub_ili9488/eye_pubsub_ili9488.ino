#include "color.h"
#include <stdlib.h>
#include <time.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>

//#include "LCDWIKI_GUI.h"
#include "LCDWIKI_SPI.h"      // IDEバージョンが1.00以上の場合
#define MODEL ILI9488_18
#define CS   10
#define CD   9
#define RST  8
#define LED  -1             // to declare unused (set to 3.3V)
LCDWIKI_SPI lcd(MODEL, CS, CD, RST, LED);
uint16_t wW, hH;
uint16_t NUM = 0;

//char success[20] = "recieved a message",failure[20] = "missed a message";
ros::NodeHandle nh;
//#define ROS_INFO
//std_msgs::String chat;
//ros::Publisher res_pub("eye_res", &chat);

void eyeRightCallback(const std_msgs::Bool& msg){
    //res_pub.publish(&chat);
    nh.loginfo("msg.data");
    if (msg.data/* == True*/){
        // SECCESS
        // chat.data = success;
        
    } else {
        // FALSE
        // chat.data = failure;
        
    }
    //pyb.publish(&chat);
}
ros::Subscriber<std_msgs::Bool> eye_sub("eye_bool_right",&eyeRightCallback);
void setup(){
    nh.initNode();
    nh.subscribe(eye_sub);
    //nh.advertise(res_pub);
    wW = lcd.Get_Display_Height();
    hH = lcd.Get_Display_Width();
    Serial.print("*** TFT-LCD ");
    Serial.print(wW + "x" + hH);
    lcd.Init_LCD();
    lcd.Fill_Screen(0x0);
}
void loop(){
//wink
  
  lcd.Fill_Screen(BLACK);
  //lcd.Set_Text_colour(WHITE);
  //lcd.Set_Text_Back_colour(CYAN);
  lcd.Set_Text_Size(2);
  lcd.Print_String("( o )", CENTER, 0);
  delay(500);
  lcd.Fill_Circle(wW / 2, hH / 2, 2);
  delay(2000);
  
}
void successEye(){
  // Yellow or Orrange (^ ^) for( 5sec )
  //lcd.Rotate(90); lcd.Set_Text_Size(-); print(")"); lcd.Fill_Screen(0x0);
}
void falseEye(){
  //red, (X X), for(until(!ros.available))

  // 白目
  //lcd.Fill_Circle(0,0,0);
}
void wink(float ms){
  // 1wink
}
