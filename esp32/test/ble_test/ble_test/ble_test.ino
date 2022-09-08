#include "BluetoothSerial.h"

BluetoothSerial bt;
const char *bt_name = "washi_esp32"; // Bluetoothのデバイス名

void setup() {
  Serial.begin(115200);
  bt.begin(bt_name);
}

void loop() {
  Serial.print("check\n");
  bt.println(millis() / 1000);
  delay(100);
}
