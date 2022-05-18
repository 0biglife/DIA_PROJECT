#include <SoftwareSerial.h>
#define BAUDRATE 57600
SoftwareSerial blueTooth(11, 10); // RX | TX

// Identifier : 0081:F9:08AA47
// AT Mode -> Communication Mode : 누른 상태에서 해제 후, 누르지 않은 상태에서 연결
// Communication Mode -> AT Mode : 누른 상태에서 해제 후, 누른 상태에서 연

// AT MODE 연결 방법
// AT+UART=57600,0,0
// AT+ROLE=1
// AT+PSWD=0000
// AT+CMODE=0
// AT+CLASS=0
// AT+INQM=1, 9, 48
// AT+INQ ..wait
// AT+PAIR=0081:F9:08AA47, 30
// AT+BIND=0081:F9:08AA47
// AT+LINK=0081:F9:08AA47 // -> 연결 마지막 명령어 -> 점등 2연속 3초 간

byte payloadData[32] = {0};
byte Attention[5] = {0};
byte checkSum = 0;
byte generatedCheckSum = 0;
int Plength, Temp;
int Att_Avg = 0;
int k = 0;
signed int j = 0;

void setup()
{
//  pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
//  digitalWrite(9, HIGH);
  Serial.begin(BAUDRATE);
  Serial.println("Average Attention Values");
  delay(15);
//  Serial.begin(38400); //for AT Mode
//  blueTooth.begin(38400);  // HC-05 default speed in AT command more
//  Serial.println("Enter AT commands:");
}

//Read Data
byte ReadData(){
  int ByteRead;
  while(!Serial.available());
  ByteRead = Serial.read();
  return ByteRead;
}

void loop()
{
  while(1){
    Serial.println("test:");
    if(ReadData() == 170){
      if(ReadData() == 170){
        Plength = ReadData();
        if(Plength == 32){
          generatedCheckSum = 0;
          for(int i = 0; i < Plength; i++){
            payloadData[i] = ReadData();
            generatedCheckSum += payloadData[i];
          }
          generatedCheckSum = 255 - generatedCheckSum;
          checkSum = ReadData();

          if(checkSum == generatedCheckSum){
            if(payloadData[28] == 4){
              if(j<4){
                Attention[k] = payloadData[29];
                Temp += Attention[k];
                j++;
              }
              else{
                Att_Avg = Temp/4;
                Serial.println(Att_Avg, DEC);

                if(Att_Avg > 50){
                  // Additional Logic ~
                }
              }
            }
          }
        }
      }
    }
  }

  //for AT MODE
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (blueTooth.available()){
    Serial.write(blueTooth.read());
  }

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    blueTooth.write(Serial.read());

}
