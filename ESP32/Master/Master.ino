//STATION
#include "WiFi.h"
#include <esp_now.h>
#include <SoftwareSerial.h>

SoftwareSerial master(22,23); 

byte payloadData[32] = {0};
byte Attention = 0;
byte checkSum = 0;
byte generatedCheckSum = 0;
int Plength, Temp;
int Att_Avg = 0;
int k = 0;
signed int j = 0;

// 1 -> 08:3A:F2:AB:7B:A8
// 2 -> 08:3A:F2:AC:8C:24
// 3 -> 08:3A:F2:AC:4B:E4

// Uno -> 98D3:21:F79642
// ESP -> 08:3A:F2:AB:7B:AA

uint8_t broadcastAddress1[] = {0x08, 0x3A, 0xF2, 0xAC, 0x8C, 0x24};
uint8_t broadcastAddress2[] = {0x08, 0x3A, 0xF2, 0xAC, 0x4B, 0xE4};

typedef struct struct_message {
  int Attention;
} struct_data;

struct_data myData;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup(){
  Serial.begin(115200);
  master.begin(38400);
  
  Serial.println("Attention Value ! ");
  
//  WiFi.mode(WIFI_STA);
  
  // Init ESP-NOW
//  if (esp_now_init() != ESP_OK) {
//    Serial.println("Error initializing ESP-NOW");
//    return;
//  }
//
//  esp_now_register_send_cb(OnDataSent);
//
//  // Register peer
//  peerInfo.channel = 0;  
//  peerInfo.encrypt = false;
//  // Register First peer
//  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
//
//  if (esp_now_add_peer(&peerInfo) != ESP_OK){
//    Serial.println("Failed to add peer");
//    return;
//  }

  // Register Second peer
//  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
//
//  if (esp_now_add_peer(&peerInfo) != ESP_OK){
//    Serial.println("Failed to add peer");
//    return;
//  }
}

byte ReadData(){
  int ByteRead; 
  while(!Serial.available());
  ByteRead = Serial.read();
  return ByteRead;
}
 
void loop(){
//  ReadData();
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
              Serial.print("Attention Value : ");
              Serial.println(Attention, DEC);
            }
          }
        }
      }
    }
  }

  // Keep reading from Arduino Serial Monitor and send to HC-05
//  if (Serial.available())
//    master.write(Serial.read());

//  myData.Attention = random(0,10);
//
//  esp_err_t result = esp_now_send(0, (uint8_t *) &myData, sizeof(struct_data));
//  
//  if (result == ESP_OK) {
//    Serial.println("ESP success");
//  }
//  else {
//    Serial.println("Error sending the data");
//  }
//  delay(400);

}
