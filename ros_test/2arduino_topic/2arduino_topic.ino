#include <ros.h>
#include <std_msgs/Empty.h>

ros::NodeHandle nh;


void messageCb( const std_msgs::Empty& toggle_msg) {
  //Serial.print("check");
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}

ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb );
// ros::Subscriber<{ﾒｯｾｰｼﾞﾊﾟｯｹｰｼﾞ名}::{型}> {Subscriber変数名}("{ﾒｯｾｰｼﾞ(ﾄﾋﾟｯｸ)名}", &{ｺｰﾙﾊﾞｯｸ関数名} );

void setup(){
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); 
  
  nh.initNode();
  nh.subscribe(sub);  // rosserialライブラリがボーレート115200bpsで動作するので
                      // "Serial.begin(***);"みたいなのはいらない

}

void loop(){
  nh.spinOnce();
  delay(200);
}
