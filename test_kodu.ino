// aviyonik ve haberleşme testleri bu kod ile yapılacak
//#include <SoftwareSerial.h>
#include "Arduino.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <MPU6050.h>
#include <Wire.h>
#define SEALEVELPRESSURE_HPA 1013.25
#define BASINC_ESIK 1000
Adafruit_BME280 bme;
#define LORA_TX 5 //loraTX i nin bağlı olduğu pin yani Rx
#define LORA_RX 4 //loraRX i nin bağlı olduğu pin yani Tx
MPU6050 mpu;
unsigned long delayTime;



 typedef union {
    float           sayi;
    unsigned char   array[4];
}Float_Int_Donusturucu;
Float_Int_Donusturucu veriConverter;

char paketSayaci = 0; 
float JiroskopX,JiroskopY,JiroskopZ; //geçici olarak yaptım değiştireceğim
float basinc;

//SoftwareSerial loraSerial(5,4);//hata verdiği için define ile tanımlanmış değişkenleri kaldırdım geri ekleyeceğim.

void setup() {
  
  bool status;
  delayTime = 1000;
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  //loraSerial.begin(9600);
  status = bme.begin(0x76);  //nem sesnsörünün adresibe göre bu kısım değişebilir.
  if (!status) {
    Serial.println("Nem sensörüne bağlanılamadı");
    while (1);
  }
  Serial.println("MPU6050'ye baglaniliyor");
  Serial.print(mpu.testConnection() ? "MPU6050 ile baglanti kuruldu" : "MPU6050 ile baglanti kurulamadi");
}

void loop() {
  
  


  JiroskopX = mpu.getRotationX();
  JiroskopY = mpu.getRotationY();
  JiroskopZ = mpu.getRotationZ();
  basinc = bme.readPressure() / 100.0F;
  // Print data
  
  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(JiroskopX);
  Serial.print(" Y = "); Serial.print(JiroskopY);
  Serial.print(" Z = "); Serial.println(JiroskopZ);
  Serial.print(" Basınç = "); Serial.println(basinc);
  //BASINÇ VE AÇI TETİKLENME KODU 
  //GEREKLİ DEĞERLER SAĞLANDIĞINDA LED YAK


  //LoraPaketGonder(JiroskopX,JiroskopY,JiroskopZ,basinc,BasincTetiklenme(basinc,BASINC_ESIK),char tetiklenmeAci,paketSayaci);
  delay(1000);
}
//seri haberleşme ile veri göndermek için
void PaketGonder(float aciX,float aciY,float aciZ,float basinc,char tetiklenmeBasinc,char tetiklenmeAci,char paketSayac){
  int checksumDegeri;
  //Serial.print(0x7B);// başlangıç
  
  //Serial.print(0x2F); //ayırıcı
  //Serial.print(0x75);//identifier test paketine özel tanımlayıcı kod 0x75 !!
  //Serial.print(0x2F); //ayırıcı
  veriConverter.sayi=basinc;
  Serial.print(veriConverter.array[0]);
  Serial.print(veriConverter.array[1]);
  Serial.print(veriConverter.array[2]);
  Serial.print(veriConverter.array[3]);
  Serial.print(0x2F); //ayırıcı
  veriConverter.sayi=aciX;
  Serial.print(veriConverter.array[0]);
  Serial.print(veriConverter.array[1]);
  Serial.print(veriConverter.array[2]);
  Serial.print(veriConverter.array[3]);
  Serial.print(0x2F); //ayırıcı
  veriConverter.sayi=aciY;
  Serial.print(veriConverter.array[0]);
  Serial.print(veriConverter.array[1]);
  Serial.print(veriConverter.array[2]);
  Serial.print(veriConverter.array[3]);
  Serial.print(0x2F); //ayırıcı
  veriConverter.sayi=aciZ;
  Serial.print(veriConverter.array[0]);
  Serial.print(veriConverter.array[1]);
  Serial.print(veriConverter.array[2]);
  Serial.print(veriConverter.array[3]);
  Serial.print(0x2F); //ayırıcı
  Serial.print(0x76);//Basınç ile ayrılma tetiklendi mi
  Serial.print(0x2F); //ayırıcı
  Serial.print(0x76);//Açı ile ayrılma tetiklendi mi
  Serial.print(0x2F); //ayırıcı
  Serial.print(0x76);//Doğrulama Kodu
  Serial.print(0x2F); //ayırıcı
  Serial.print(paketSayac);//Paket Sayacı
  //Serial.print(false); //ayırıcı
  //Serial.println(0x7D);//Paket bitiş kodu

 if(paketSayac != 255){
    paketSayac++; //paket sayacının 255 olma durumunu hesaba kat o kodu ekle
 }
 else{
  paketSayac = 0;
 }

}
//lora ile veri göndermek için
void LoraPaketGonder(float aciX,float aciY,float aciZ,float basinc,char tetiklenmeBasinc,char tetiklenmeAci,char paketSayac){
  int checksumDegeri;
  //pinleri lora serial olarak değiştir.
  //loraSerial.print(0x00);//burada hata var bunun çözümü baika bir kodda vardı.
  //loraSerial.print(0x3F);//adresleri dinamik yap
  //loraSerial.write(0x17); sketchy shit dont touch
  //Serial.print(0x7B);// başlangıç
  //Serial.print(0x2F); //ayırıcı
  //Serial.print(0x75);//identifier test paketine özel tanımlayıcı kod 0x75 !!
  //Serial.print(0x2F); //ayırıcı
  veriConverter.sayi=basinc;
  loraSerial.write(veriConverter.array[0]);
  loraSerial.write(veriConverter.array[1]);
  loraSerial.write(veriConverter.array[2]);
  loraSerial.write(veriConverter.array[3]);
  loraSerial.write(0x2F); //ayırıcı
  veriConverter.sayi=aciX;
  loraSerial.print(veriConverter.array[0]);
  loraSerial.print(veriConverter.array[1]);
  loraSerial.print(veriConverter.array[2]);
  loraSerial.print(veriConverter.array[3]);
  loraSerial.print(0x2F); //ayırıcı
  veriConverter.sayi=aciY;
  loraSerial.print(veriConverter.array[0]);
  loraSerial.print(veriConverter.array[1]);
  loraSerial.print(veriConverter.array[2]);
  loraSerial.print(veriConverter.array[3]);
  loraSerial.print(0x2F); //ayırıcı
  veriConverter.sayi=aciZ;
  loraSerial.print(veriConverter.array[0]);
  loraSerial.print(veriConverter.array[1]);
  loraSerial.print(veriConverter.array[2]);
  loraSerial.print(veriConverter.array[3]);
  loraSerial.print(0x2F); //ayırıcı
  loraSerial.print(0x76);//Basınç ile ayrılma tetiklendi mi
  loraSerial.print(0x2F); //ayırıcı
  loraSerial.print(0x76);//Açı ile ayrılma tetiklendi mi
  loraSerial.print(0x2F); //ayırıcı
  loraSerial.print(0x76);//Doğrulama Kodu
  loraSerial.print(0x2F); //ayırıcı
  loraSerial.print(paketSayac);//Paket Sayacı
  //Serial.print(false); //ayırıcı
  // Serial.println(0x7D);//Paket bitiş kodu
  if(paketSayac != 255){
    paketSayac++; //paket sayacının 255 olma durumunu hesaba kat o kodu ekle
 }
 else{
  paketSayac = 0;
 }
}

char BasincTetiklenme(float basincDeger,float basincEsik)
{
   if(basincDeger >= basincEsik){
   
   return 1;
   }
  else{
   return 0;
  }

//açı ile tetiklenme fonksiyonu
 




 
}

