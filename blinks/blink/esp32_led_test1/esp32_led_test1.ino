//esp32_led_test1
#include <ros.h>
#include <SPI.h>

void  setup(){
  Serial.begin(115200);
  pinMode(2, OUTPUT);
}

void loop() {
  Serial.print("check");
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
}
