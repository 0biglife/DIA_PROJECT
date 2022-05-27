#include <SoftwareSerial.h>
#define BAUDRATE 57600
SoftwareSerial blueTooth(2,3); // RX | TX
//2,3으로 업로드 후 0,3로 치환 

byte payloadData[32] = {0};
byte Attention = 0;
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
  delay(10);
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
  while(1){
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
              Attention = payloadData[29];
//              Serial.print("Attention Value : ") ;
              Serial.println(Attention, DEC);
              if(Attention > 50){
                //logic
              }
            }
          }
        }
      }
    }
  }
}
