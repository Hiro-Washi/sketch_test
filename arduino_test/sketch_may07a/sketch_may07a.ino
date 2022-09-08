// 使いたいヘッダーファイルを書いておくぅ〜
#include <ros.h>             // ArduinoのROSのためのライブラリ
#include <std_msgs/Empty.h>  // メッセージの型のライブラリ
#include <std_msgs/String.h> // String型（文字列）
#include <std_msgs/Bool.h>   // Bool型　（True or False）

#include <SPI.h>
#include <stdlib.h>
#include <time.h>

// 
ros::NodeHandle nh;

//  std_msgsのString型をstr_msgという変数を
std_msgs::String str_msg;

//　メッセージをArduinoから送りたい場合は、
//  Publishをこんな感じで宣言しておく
ros::Publisher res_pub("lcd_res", &str_msg);
//　ros::Publisher {Publisherの変数の名前}("{任意のメッセージ名(トピック名)}", &トピックの型)

void messageCb( const std_msgs::Empty& toggle_msg) {
  //Serial.print("check");
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}

ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb );

void setup(){
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); 

  // ROSのノードを初期化（必ず書く）
  nh.initNode();
  // Serial.begin(9600); 
  nh.subscribe(sub);
}

void loop(){
  nh.spinOnce();
  delay(200);
}
