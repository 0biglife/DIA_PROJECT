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
  //Initialize Serial Monitor
  Serial.begin(57600);
  pwm.begin();
  pwm.setPWMFreq(1600);
  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_recv_cb(OnDataRecv);
}

int mul;
 
void loop() {
//  mul = map(myData.Att, 0, 100, 0, 255);
//  ledcWrite(PWM1_Ch, mul);

  if (myData.Att > 0 && myData.Att < 50){
    for (uint16_t i=0; i<4096; i += 8){
      for (uint8_t pwmnum=0; pwmnum < 4; pwmnum++){
        pwm.setPWM(pwmnum, 0, (i + (4096/16)*pwmnum) % 4096 );
      }
    }
  }else if(myData.Att > 50){
    for (uint16_t i=0; i<4096; i += 8){
      for (uint8_t pwmnum=4; pwmnum < 8; pwmnum++){
        pwm.setPWM(pwmnum, 0, (i + (4096/16)*pwmnum) % 4096 );
      }
    }
  }
}
