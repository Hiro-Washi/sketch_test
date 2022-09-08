#define RS_PIN 4         //LCDのピン設定
#define E_PIN 7
#define DB4_PIN 8
#define DB5_PIN 9
#define DB6_PIN 10
#define DB7_PIN 11

#define Default_voltage 99.99   //無接続時に表示する値
#define A_voltage_low 16.0      //A電池残量の閾値
#define B_voltage_low 16.0      //B電池残量の閾値
#define KOBUKI_voltage_low 8.00  //KOBUKI電池残量【いちおう付けただけ】

#define voltage_filter 0.5      //無接続時にブザーが鳴らないように設定

#define buzzer 5                //ブザー接続ピン番号

#include <LiquidCrystal.h>;
LiquidCrystal lcd(RS_PIN,E_PIN,DB4_PIN,DB5_PIN,DB6_PIN,DB7_PIN);

void setup(){
  lcd.begin(20,4);              //LCD初期設定　枠のセル数  
  Serial.begin(9600);
}


void loop(){

  int i = 0;
  double A_voltage_min,B_voltage_min,KOBUKI_voltage;

  for(i=0;i<i+1;i++){           //Loopだと都合が悪いので無限for
    double A_value = analogRead(A1);  //Aの電圧読み　PIN15
    double B_value = analogRead(A0);  //Bの電圧読み　PIN14
    double KOBUKI = analogRead(A2);   //KOBUKI 電圧　A2ピン
    
    if(A_value <= voltage_filter){      //A外した時に値初期化
      A_voltage_min = Default_voltage;
    }
    if(B_value <= voltage_filter){      //B外した時に初期化
      B_voltage_min = Default_voltage;
    }

    if(KOBUKI <= voltage_filter){      //KOBUKI外した時に初期化
      KOBUKI_voltage = Default_voltage;
    }

    A_value *= 5;             //読み込んだ値を10進数に戻すやつ
    A_value /= 1023;             //Arduino5Vまで読めるらしいが、
    A_value /= 30;               //PCと電池で電源を供給した場合
    A_value *= 130;              //表示される値が違うというクソ仕様なので
                                 //それっぽい値で計算させてます
    B_value *= 5;             //1023段階で読み取っているので
    B_value /= 1023;             //それなりに計算させて元の電圧計算させてます
    B_value /= 30;               //抵抗は100kと30kなので
    B_value *= 130;              //あとは電気科に訊け

    KOBUKI *= 5;
    KOBUKI /= 1023;
    KOBUKI /= 30;
    KOBUKI *= 130;

    if(A_value <= A_voltage_low){       //Aのブザー鳴らすプログラム
      if(A_value >= voltage_filter){    //無接続時に鳴らないようにするやつ
        tone(buzzer,3136,200);          //pin,Hz,ms
        delay(250);
        tone(buzzer,2793,200);
        delay(250);
        tone(buzzer,3136,200);
        delay(500);
      }
    }
    if(B_value <= B_voltage_low){       //Bのブザー鳴らすプログラム
      if(B_value >= voltage_filter){    //無接続時鳴防止
        tone(buzzer,440,500);           //pin,Hz,ms
        delay(800);
      }
    }

    if(KOBUKI_voltage <= KOBUKI_voltage_low){       //KOBUKIのブザー鳴らすプログラム
      if(KOBUKI_voltage >= voltage_filter){         //無接続時鳴防止
        tone(buzzer,440,500);                       //pin,Hz,ms
        delay(800);
      }
    }

    if(A_value >= voltage_filter){      //A電圧最小値表示システム
      if(A_voltage_min >= A_value){
        A_voltage_min = A_value;
      }
    }
    if(B_value >= voltage_filter){      //B電圧最小表示システム
      if(B_voltage_min >= B_value){
        B_voltage_min = B_value; 
      }
    }

    if(KOBUKI >= voltage_filter){      //B電圧最小表示システム
      if(KOBUKI_voltage >= KOBUKI){
        KOBUKI_voltage = KOBUKI; 
      }
    }

    Serial.println(A_voltage_min);      //ABの電圧値をLCDに表示
    Serial.println(B_voltage_min);
    Serial.println(KOBUKI_voltage);

    lcd.setCursor(0,0);
    lcd.print("404_NOT_FOUND");

    lcd.setCursor(0,1);             //LCDのカーソル設定 横,縦
    lcd.print("Mini_PC_ptp:");    //Aの値を表示
    lcd.setCursor(13,1);
    lcd.print(A_voltage_min);
    lcd.setCursor(19,1);
    lcd.print("v");

    lcd.setCursor(0,2);
    lcd.print("Jetson_beep:");
    lcd.setCursor(13,2);
    lcd.print(B_voltage_min);
    lcd.setCursor(19,2);
    lcd.print("v");

    lcd.setCursor(0,3);
    lcd.print("TANAKA_YUKI:");
    lcd.setCursor(13,3);
    lcd.print(KOBUKI_voltage);
    lcd.setCursor(19,3);
    lcd.print("v");
  }
}
