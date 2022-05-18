#include <SoftwareSerial.h>
#define BAUDRATE 57600
SoftwareSerial blueTooth(11, 10); // RX | TX

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
  Serial.begin(BAUDRATE);
  Serial.println("Average Attention Values");
  delay(15);
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
  int ByteRead;
    ByteRead = Serial.read();
  while(1){
    Serial.println(ByteRead);
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
                j = 0;
                Temp = 0;
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
}
