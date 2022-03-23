#include <DHT.h>
#include <Servo.h>
#include <Wire.h>
#include "RTClib.h"
#define DHTPIN 3
#define DHTTYPE DHT11

float suhu, kelembaban, bts_suhu, bts_kelembaban;
int lampu = 4;
int kipas = 5;
int mist = 6;
int srv = 7;

DHT dht(DHTPIN, DHTTYPE);
Servo servo;
RTC_DS1307 rtc;

void setup() {
  Serial.begin(115200);
  pinMode(mist, OUTPUT);
  dht.begin();
  servo.attach(srv);
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  suhu = dht.readTemperature();
  kelembaban = dht.readHumidity();
  DateTime now = rtc.now();
  unsigned int j = rtc.hour();
  unsigned int m = rtc.minute();
  int  angle;

  if(suhu>=bts_suhu){
    analogWrite(lampu, 512);
    analogWrite(kipas, 1024);
  }
  else{
    analogWrite(lampu, 1024);
    analogWrite(kipas, 512);
  }

  if(kelembaban<bts_kelembaban){
    digitalWrite(mist, HIGH);
  }
  else if(kelembaban>70){
    digitalWrite(mist, LOW);
    analogWrite(kipas, 1024);
  }
  
  if(j%4=0){
    if(m=0){
      for(int n; n<=60; n++){
        servo.write(n);
        delay(50);
      }
    }
  }
}
