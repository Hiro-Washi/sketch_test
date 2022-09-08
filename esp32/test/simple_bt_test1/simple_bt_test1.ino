#include <SoftwareSerial.h>
 
SoftwareSerial btport(10, 11);
 
void setup() {
    Serial.begin(9600);
    btport.begin(38400);
    Serial.println("Enter AT commands:");
}
 
void loop()
 
{
    if (btport.available())
        Serial.write(btport.read());
    if (Serial.available()){
       btport.write(Serial.read());
    }
}
