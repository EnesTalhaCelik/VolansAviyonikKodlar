#include <SoftwareSerial.h>
#include "Arduino.h"
//

#define LED 27
#define LEDMESAJ 26
#define AUX_PIN 34
#define E32TX_PIN 35 //e32'nin TX PİNİ!!! yani rx
#define E32RX_PIN 32 //e32'nin RX PİNİ!!! yani rx
#define M1_PIN 23
#define M0_PIN 25


SoftwareSerial loraSerial(E32TX_PIN, E32RX_PIN);
byte decimalNumber = 0; //kod içerisinde lazım 

void setup() {
 
  pinMode(LED,OUTPUT);
  pinMode(LEDMESAJ,OUTPUT);
  loraSerial.begin(115200);
  Serial.begin(9600);


    String hexString = String(decimalNumber, HEX);
}

void loop() {
  
  digitalWrite(LED,HIGH);
    delay(5000);
 
      if (loraSerial.available()>1){
      int x = loraSerial.read();
      digitalWrite(LEDMESAJ,HIGH);
      delay(100);
      digitalWrite(LEDMESAJ,LOW);
       }  

  loraSerial.write(decimalNumber);
  loraSerial.write(0x2C); 
  loraSerial.write(0x17); 
  loraSerial.write(0x76);//V
  loraSerial.write(0x6F);//O
  loraSerial.write(0x6C);//L
  loraSerial.write(0x61);//A
  loraSerial.write(0x6E);//N
  loraSerial.write(0x73);//S

  digitalWrite(LED,LOW);
  delay(5000);
}

