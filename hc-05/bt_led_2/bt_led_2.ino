void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char data = Serial.read();
    switch(data) {
      case '1': digitalWrite(13, HIGH); break;
      case '0': digitalWrite(13, LOW);  break;
      default : break;
    }
    Serial.println(data);
  }
  delay(200);
}
