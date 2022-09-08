char in_value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available() > 0)
  {
    in_value = Serial.read();
    Serial.print(in_value);
    Serial.print("\n");
    if (in_value == "1")
      digitalWrite(13, HIGH);
    else if (in_value == "0")
      digitalWrite(13, LOW);
  }
  delay(200);
}
