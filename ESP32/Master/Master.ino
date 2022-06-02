//STATION
#include "WiFi.h"
#include <esp_now.h>

// 1 -> 08:3A:F2:AB:7B:A8
// 2 -> 08:3A:F2:AC:8C:24
// 3 -> 08:3A:F2:AC:4B:E4

uint8_t broadcastAddress1[] = {0x08, 0x3A, 0xF2, 0xAC, 0x8C, 0x24};
//uint8_t broadcastAddress2[] = {0x08, 0x3A, 0xF2, 0xAC, 0x4B, 0xE4};

typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_data;

struct_data myData;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup(){
  Serial.begin(115200);

  //for MacAddress
//  WiFi.mode(WIFI_MODE_STA);
//  Serial.println(WiFi.macAddress());

  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop(){
  strcpy(myData.a, "THIS IS A CHAR");
  myData.b = random(1,20);
  myData.c = 1.2;
  myData.d = false;

  esp_err_t result = esp_now_send(broadcastAddress1, (uint8_t *) &myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(1000);
}
