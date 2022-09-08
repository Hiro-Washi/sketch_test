String voice;
#define BLUE  11
#define GREEN 10
#define RED   9
void setup()
{
  Serial.begin(9600);
  pinMode(, OUTPUT);
  analogWrite(RED, 255);
  pinMode(GREEN, OUTPUT);
  analogWrite(GREEN, 255);
  pinMode(BLUE, OUTPUT);
  analogWrite(BLUE, 255);
}
int redVal;
int greenVal;
int blueVal;
void loop() {
  while (Serial.available()) {
    Serial.print("check\n");
    delay(10);
    char c = Serial.read();
    if (c == '#') {
      break;
    }
    voice += c;
  }
  if (voice.length() > 0) {
    Serial.println(voice);
    if (voice == "*red") {
      analogWrite(RED, 0);
      analogWrite(GREEN, 255);
      analogWrite(BLUE, 255);
    }
  else if (voice == "*green") {
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 255);
  }
  else if (voice == "*blue") {
    analogWrite(RED, 255);
    analogWrite(GREEN, 255);
    analogWrite(BLUE, 0);
  }
  else if (voice == "*white") {
    analogWrite(RED,0);
    analogWrite(GREEN,0);
    analogWrite(BLUE,0);
}
  else if (voice == "*good night") {
    analogWrite(RED,255);
    analogWrite(GREEN,255);
    analogWrite(BLUE,255);
  }
  else if (voice == "*chameleon") {
    redVal = 255;
    greenVal = 0;
    blueVal = 0;
    for (int i = 0; i < 255; i += 1) {
      greenVal += 1;
      redVal -= 1;
      analogWrite(GREEN, 255 - greenVal);
      analogWrite(RED ,255 - redVal);
      delay(10);
    }
    redVal = 0;
    greenVal = 255;
    blueVal = 0;
    for (int i = 0; i < 255; i+= 1) {
      blueVal +=1;
      greenVal -= 1;
      analogWrite(BLUE, 255 - blueVal);
      analogWrite(GREEN, 255 - greenVal);
      delay(10);
    }
    redVal = 0;
    greenVal = 0;
    blueVal = 255;
    for (int i = 0; i < 255; i+= 1) {
      redVal +=1;
      blueVal -= 1;
      analogWrite(RED, 255 - redVal);
      analogWrite(BLUE, 255 - blueVal);
      delay(10);
    }
  }
  voice = "";
  }
}
