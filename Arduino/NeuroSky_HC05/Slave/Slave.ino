#include <SoftwareSerial.h>
SoftwareSerial slave(2,3); 

// MASTER ADDR : 0021:09:002B85
// HC-06 : 98 DA 60 02 D2 1A

int cmd = 0;
int val = 0;

void setup()
{
  Serial.begin(9600); 
  slave.begin(9600); 
  Serial.println("Start");
}

void loop()
{
  while(slave.available() > 0){
    cmd = (int)slave.read();
    Serial.println(cmd);
  }
}
