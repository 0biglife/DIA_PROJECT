#include <SoftwareSerial.h>
SoftwareSerial slave(2,3); 

// MASTER ADDR : 0021:09:002B85
void setup()
{
  Serial.begin(9600); 
  slave.begin(9600); 
  Serial.println("Enter AT commands");
}

void loop()
{
  //for AT MODE
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (slave.available()){
    Serial.write(slave.read());
  }

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    slave.write(Serial.read());

}
