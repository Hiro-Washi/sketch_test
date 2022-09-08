# PC操作でROSから信号を受け取ったときにLチカする
# roscore
# rosrun rosserial_python serial_node.py /dev/ttyACM0
# rostopic pub toggle_led std_msgs/Empty --once

# ROSヘッダー、トピックの型のインクルード
#include <ros.h>
#include <std_msgs/Empty.h>

# setup関数、loop関数の両方で使用するため、
#グローバル変数としてROSノードハンドルの宣言
ros::NodeHandle nh;

# トピックを受け取った時の動作内容
void messageCb( const std_msgs::Empty& toggle_msg) {
  digitalWrite(11, HIGH);
  delay(100);
  digitalWrite(11, LOW);
  delay(100);
}

# 上記で作成したコールバック関数とトピック名を紐付け
ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb );

# Arduino 起動時に一度だけ実行される関数。
# ノードに加え、ノードハンドルの初期化、サブスクライバーの追加を行う必要がある。
void setup(){
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH); 
  nh.initNode();
  nh.subscribe(sub);
}

# Arduino 起動中に繰り返される関数
void loop(){
  # コールバック関数を実行する
  nh.spinOnce();
  delay(1);
}
