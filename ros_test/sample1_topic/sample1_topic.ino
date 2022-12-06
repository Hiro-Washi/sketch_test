// 使いたいヘッダーファイルを書いておくぅ〜
#include <ros.h>             // ArduinoのROSのためのライブラリ
#include <std_msgs/Empty.h>  // メッセージの型のライブラリ
#include <std_msgs/String.h> // String型（文字列）
#include <std_msgs/Bool.h>   // Bool型　（True or False）

// ノードオブジェクトの生成＆ROSマスターへ登録
ros::NodeHandle nh;

//  std_msgsのString型をstr_msgという変数を作る
std_msgs::String str_msg;
ros::ServiceClient<Test::Request, Test::Response> client("test_srv");

//　メッセージをArduinoから送りたい場合は、
//  Publishをこんな感じで宣言しておく
ros::Publisher res_pub("lcd_res", &str_msg);
//　ros::Publisher {Publisherの変数の名前}("{任意のメッセージ名(トピック名)}", &トピックの型)

// コールバック関数はSubscriber宣言やsetup()よりも先に
void messageCallback( const std_msgs::Empty& toggle_msg) {
  Serial.print("check ros-communication");
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(50);
}

// Publiserの宣言と同じ要領でSubscriberの宣言を書く（messageCallback）
ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCallback );

// おなじみのセットアップ関数（当然必ず書く）
void setup(){
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); 

  // ROSのノードを初期化（必ず書く）
  nh.initNode();
  // rosserialライブラリはボーレート115200bpsで勝手に動作するので
  // "Serial.begin(9600);"みたいなやつはいらない 
  nh.subscribe(sub);
}

// おなじみのループ関数（当然必ず書く）
void loop(){
  // ROSの信号を"一度だけ"読み取る
  nh.spinOnce();

  delay(200);
}
