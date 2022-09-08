//　　C　　　D　　E　　　F　　G　　　A　　　B
//　　ド   　レ   ミ   　ファ  ソ    ラ    シ
//1   131   147   165   175   196   220   247
//2   262   294   330   349   392   440   494
//3   523   587   659   698   784   880   988
int ss=50;int s=100;int b=150;int l=200;int ll=250;
// 音の長さを指定
int pin = 13;     // ブザーを接続したピン番号
int le=147;int lf=165;int lg=175;
int e=330;int f=349;int g=392;
int he=659;int hf=698;int hg=784;

int sta;int lb;int db;int hb;
sta=f; lb=lf; mb=f; hb=hf;
//int std = f;int lb=lf;int lb

void setup() {
}

void loop() {
// O HA YO -
  speak("ohayo");
  speak("h_ohayo");
  delay(1000) ;         // 1秒待機
}

void speak(char s){
  if (s = "ohayo"){
    mytone(13,f,b);mytone(13,g,b);mytone(13,g,ll);
  }
  if (s="h_ohayo"){
    mytone(13,hf,b);mytone(13,hg,b);mytone(13,hg,ll);
  }
  else int pass = 0;
}

void speak2(int level,char s){
  if (level = 1) std=lf;
  if (level = 2) std=f;
  if (level = 3) std=hf;
  if (s = "ohayo") {
    mytone(13,f,b);mytone(13,g,b);mytone(13,g,l); }
  if (s="h_ohayo") {
    mytone(13,std,b);mytone(13,std,b);mytone(13,std,ll); }
  else int pass = 0;
}

void mytone(int pin,int freq,int beep_time){
  tone(pin,freq, beep_time);
  delay(beep_time);
}
