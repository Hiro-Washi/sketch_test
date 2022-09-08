#include "BluetoothSerial.h"
#include "ros.h"
#include "std_msgs/Empty.h"

BluetoothSerial BTS;
int val;
int val_input;

void setup() {
  Serial.begin(9600);
  BTS.begin("Start ESP32 test");
}

void loop() {
  if (BTS.available()) {
    String recieveData = BTS.readStringUntil(";");
    val_input = receiveData.toInt(); // to int

    if (val_input < 0 | 180 < val_input {
      BTS.print("invalid input\n"); // send message to phone
    }
    else {
      val = val_input;
      BTS.print("Set Number" + recieveData);
    }
    
  }
  Serial.print("val");
  
}
