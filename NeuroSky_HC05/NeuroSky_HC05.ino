#include <SoftwareSerial.h>

SoftwareSerial BTSerial(11, 10); // RX | TX
// My ID : 00 81 F9 08 AA 47 // 0081,F9,08AA47
void setup()
{
  pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
  Serial.println("Enter AT commands:");
}

void loop()
{
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    BTSerial.write(Serial.read());
}
