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
  Serial.print("Mapping Count : ");
  Serial.println(map(myData.Att, 0, 100, 0, 16));
}
 
void setup() {
  Serial.begin(57600);
  pwm.begin();
  pwm.setPWMFreq(1600);

  WiFi.mode(WIFI_STA);

  Serial.print("WIFI : ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  Leds(0);
  
  esp_now_register_recv_cb(OnDataRecv);
}

int mul;
int mapCnt;
int mapMin;
int mapMax;
int mapInc;

unsigned long preMillis = 0;
//unsigned long preMillis2 = 0;
//long interval = 500;

void Leds(uint16_t i){
  for(int pin = 0; pin < 16; pin ++){
    pwm.setPWM(pin, 0, i);
  }
}

void LedsOff(){
  for(int pin = 0; pin < 16; pin ++){
    pwm.setPWM(pin, 0, 0);
  }
}

void RandomLeds(int randomPin, int minNum, int maxNum, int increment) {
  unsigned long curMillis = millis();
  uint8_t temp[randomPin];
  uint8_t except[16 - randomPin];
  
  for(int i = 0; i < randomPin; i++){
    temp[i] = random(0, 16);

    if(i>0){ // 중복 난수 삭제
      for(int j = 1 ; j <randomPin; j++){
        if(temp[i] == temp[i-j]){
          temp[i] = random(0,16);
        }
      }
    }
  }

  Serial.print("TEMP : ");
  for(int i = 0; i < randomPin; i++){
    if(temp[i] < 10){
      Serial.print("0");
    }
    if(i == randomPin-1){
      Serial.println(temp[i]);
    }else{
      Serial.print(temp[i]);
      Serial.print(" ");
    }
  }
  
  for (uint16_t i= minNum; i<maxNum; i += increment ) {
    for(int j = 0; j < randomPin ; j++){
      pwm.setPWM(temp[j], 0, i);
    }
    delay(10);
  }
  for (uint16_t i=maxNum; i>minNum; i -= increment) {
    for(int j = 0; j < randomPin ; j++){
      pwm.setPWM(temp[j], 0, i);
    }
    delay(10);
  }
  LedsOff();
}

void wave(int minNum, int maxNum, int increment){
  for (uint16_t i= minNum; i<maxNum; i += increment ) {
//    for(int pin = pinNum; pin < 16; pin += 3){
//      pwm.setPWM(pin, 0, i); 
//    }
    Leds(i);
    delay(10);
  }
  for (uint16_t i=maxNum; i>minNum; i -= increment) {
//    for(int pin = pinNum; pin < 16; pin += 3){
//      pwm.setPWM(pin, 0, i);
//    }
    Leds(i);
    delay(10);
  }
}

void RandomLedsOn(int pinNum, int minNum, int maxNum, int increment){
//  uint8_t temp[pinNum];
//  uint8_t except[16 - pinNum];
//  
//  for(int i = 0; i < pinNum; i++){
//    temp[i] = random(0, 16);
//
//    if(i>0){ // 중복 난수 삭제
//      for(int j = 1 ; j <pinNum; j++){
//        if(temp[i] == temp[i-j]){
//          temp[i] = random(0,16);
//        }
//      }
//    }
//  }
//
//  Serial.print("TEMP : ");
//  for(int i = 0; i < pinNum; i++){
//    if(temp[i] < 10){
//      Serial.print("0");
//    }
//    if(i == pinNum-1){
//      Serial.println(temp[i]);
//    }else{
//      Serial.print(temp[i]);
//      Serial.print(" ");
//    }
//  }

  for (uint16_t i= minNum; i<maxNum; i += increment ) {
    for(int j = 0; j < pinNum ; j++){
      pwm.setPWM(j, 0, i);
    }
    delay(10);
  }
  for (uint16_t i=maxNum; i>minNum; i -= increment) {
    for(int j = 0; j < pinNum ; j++){
      pwm.setPWM(j, 0, i);
    }
    delay(10);
  }
//  for(int i = 0 ; i < pinNum; i++){
//    pwm.setPWM(temp[i], 4096, 0);
//    pwm.setPWM(i, 4096, 0);
//  }
//  LedsOff();
}

void pwmOn(int pin, int minNum, int maxNum, int increment){
  for (uint16_t i= minNum; i<maxNum; i += increment ) {
    pwm.setPWM(pin, 0, i);
    delay(10);
  }
  for (uint16_t i=maxNum; i>minNum; i -= increment) {
    pwm.setPWM(pin, 0, i);
    delay(10);
  }
}

void loop() {
  mapCnt = map(myData.Att, 0, 100, 0, 16);
  mapMin = map(myData.Att, 0, 100, 128, 2046);
  mapMax = map(myData.Att, 0, 100, 128, 4096);
  mapInc = map(myData.Att, 0, 100, 2, 16);

// 로직0 : 단순히 input에 비례하여 pin 순서대로 점등 
  if( mapCnt == 0 ){
    wave(30, 128, 1);
  }else{   // mapCnt : 6. 5번까지 켜지고 6,7,8,~ 15버는 꺼져야
    for(int i = 0; i < mapCnt; i++){
      for(int j = mapCnt; j < 16 ; j++){
        pwm.setPWM(i, 4096, 0);
        pwm.setPWM(j, 0, 0);
      }
    }
  }

// 로직1 : 특정 범위에서 input에 비례한 밝기 제어 
//        연결 중인 상태(4초 소요 / input = 0) : 모든 LED 약하게 켜졌다 꺼짐
//  if (myData.Att > 0 && myData.Att <= 30){
//    wave(10, 128, 1);
//  }else if(myData.Att > 30 && myData.Att <= 100){
//    wave(
//      map(myData.Att, 0, 100, 1024, 2048), 
//      map(myData.Att, 0, 100, 2048, 4096), 
//      map(myData.Att, 0, 100, 8, 16)
//    );
//  }else if (myData.Att == 0){ //탐지중
//    wave(10, 128, 16);
//  }

// 로직2 : input 범위에 따라 강하게(PWM) 빛날 LED 수를 제어 (개별 함수 선언)
//        연결 중인 상태 : 모든 LED 약하게 켜졌다 꺼짐
// 문제 : 보드마다 딜레이가 달라서 난해한 비주얼 

//  if(myData.Att == 0){
//    wave(30, 128, 1);
//  }else{
//    RandomLeds(mapCnt, mapMin, mapMax, mapInc); 
//  }

//  if(myData.Att == 0){
//    wave(30, 128, 1);
//  }else{
//    RandomLedsOn(mapCnt, 512, 2048, 8);
//  }
}
