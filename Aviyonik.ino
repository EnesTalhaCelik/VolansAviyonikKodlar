#include <SoftwareSerial.h>
#include "Arduino.h"



//reciver

#define LED 27
#define LEDMESAJ 26
#define AUX_PIN 34
#define E32TX_PIN 35
#define E32RX_PIN 32
#define M1_PIN 23
#define M0_PIN 25


SoftwareSerial mySerial(35, 32);

byte decimalNumber = 0; // Your decimal number
void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  pinMode(LEDMESAJ,OUTPUT);
  mySerial.begin(115200);
  Serial.begin(9600);


    String hexString = String(decimalNumber, HEX);
}

void loop() {
  
  digitalWrite(LED,HIGH);
    delay(5000);
 
      if (mySerial.available()>1){
      int x = mySerial.read();
      digitalWrite(LEDMESAJ,HIGH);
      delay(100);
      digitalWrite(LEDMESAJ,LOW);
       }  

  mySerial.write(decimalNumber);
  mySerial.write(0x2C); 
  mySerial.write(0x17); 
  mySerial.write(0x76);//V
  mySerial.write(0x6F);//O
  mySerial.write(0x6C);//L
  mySerial.write(0x61);//A
  mySerial.write(0x6E);//N
  mySerial.write(0x73);//S

  digitalWrite(LED,LOW);
  delay(5000);
}

