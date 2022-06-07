#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

typedef struct test_struct {
  int Att;
} test_struct;

test_struct myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Attention Value : ");
  Serial.println(myData.Att);
}
 
void setup() {
  Serial.begin(57600);
  pwm.begin();
  pwm.setPWMFreq(1600);

  WiFi.mode(WIFI_STA);

  Serial.print(WiFi.macAddress());

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_recv_cb(OnDataRecv);
  
    pwm.setPWM(0, 0, 0);
    pwm.setPWM(1, 0, 0);
    pwm.setPWM(2, 0, 0);
    pwm.setPWM(3, 0, 0);
    pwm.setPWM(4, 0, 0);
    pwm.setPWM(5, 0, 0);
    pwm.setPWM(6, 0, 0);
    pwm.setPWM(7, 0, 0);
}

int mul;
 
void loop() {
////  mul = map(myData.Att, 0, 100, 0, 255);
  if (myData.Att > 0 && myData.Att < 20){
//    for (uint16_t i=0; i<256; i += 8){
    pwm.setPWM(0, 0, 255);
    pwm.setPWM(1, 0, 0);
    pwm.setPWM(2, 0, 0);
    pwm.setPWM(3, 0, 0);
    pwm.setPWM(4, 0, 0);
    pwm.setPWM(5, 0, 0);
    pwm.setPWM(6, 0, 0);
    pwm.setPWM(7, 0, 0);
//    }
  }else if(myData.Att >= 20 && myData.Att < 40){
    pwm.setPWM(0, 0, 255);
    pwm.setPWM(1, 0, 255);
    pwm.setPWM(2, 0, 0);
    pwm.setPWM(3, 0, 0);
    pwm.setPWM(4, 0, 0);
    pwm.setPWM(5, 0, 0);
    pwm.setPWM(6, 0, 0);
    pwm.setPWM(7, 0, 0);
  }else if(myData.Att >= 40 && myData.Att < 50){
    pwm.setPWM(0, 0, 255);
    pwm.setPWM(1, 0, 255);
    pwm.setPWM(2, 0, 255);
    pwm.setPWM(3, 0, 0);
    pwm.setPWM(4, 0, 0);
    pwm.setPWM(5, 0, 0);
    pwm.setPWM(6, 0, 0);
    pwm.setPWM(7, 0, 0);
  }else if(myData.Att >= 50 && myData.Att < 60){
    pwm.setPWM(0, 0, 255);
    pwm.setPWM(1, 0, 255);
    pwm.setPWM(2, 0, 255);
    pwm.setPWM(3, 0, 255);
    pwm.setPWM(4, 0, 0);
    pwm.setPWM(5, 0, 0);
    pwm.setPWM(6, 0, 0);
    pwm.setPWM(7, 0, 0);
  }else if(myData.Att >= 60 && myData.Att < 70){
    pwm.setPWM(0, 0, 255);
    pwm.setPWM(1, 0, 255);
    pwm.setPWM(2, 0, 255);
    pwm.setPWM(3, 0, 255);
    pwm.setPWM(4, 0, 255);
    pwm.setPWM(5, 0, 0);
    pwm.setPWM(6, 0, 0);
    pwm.setPWM(7, 0, 0);
  }else if(myData.Att >= 70 && myData.Att < 80){
    pwm.setPWM(0, 0, 255);
    pwm.setPWM(1, 0, 255);
    pwm.setPWM(2, 0, 255);
    pwm.setPWM(3, 0, 255);
    pwm.setPWM(4, 0, 255);
    pwm.setPWM(5, 0, 255);
    pwm.setPWM(6, 0, 0);
    pwm.setPWM(7, 0, 0);
  }else if(myData.Att >= 80 && myData.Att < 90){
    pwm.setPWM(0, 0, 255);
    pwm.setPWM(1, 0, 255);
    pwm.setPWM(2, 0, 255);
    pwm.setPWM(3, 0, 255);
    pwm.setPWM(4, 0, 255);
    pwm.setPWM(5, 0, 255);
    pwm.setPWM(6, 0, 255);
    pwm.setPWM(7, 0, 0);
  }else if(myData.Att >= 90){
    pwm.setPWM(0, 0, 255);
    pwm.setPWM(1, 0, 255);
    pwm.setPWM(2, 0, 255);
    pwm.setPWM(3, 0, 255);
    pwm.setPWM(4, 0, 255);
    pwm.setPWM(5, 0, 255);
    pwm.setPWM(6, 0, 255);
    pwm.setPWM(7, 0, 255);
  }
}
