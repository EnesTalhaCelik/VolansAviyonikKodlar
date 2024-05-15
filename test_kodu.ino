// aviyonik ve haberleşme testleri bu kod ile yapılacak




#include <MPU6050.h>
#include <Wire.h>
MPU6050 mpu;


 typedef union {
    float           sayi;
    unsigned char   array[4];
}Float_Int_Donusturucu;
Float_Int_Donusturucu test;

char paketSayaci = 0; 
int x,y,z; //geçici olarak yaptım değiştireceğim
void setup() {
  Serial.begin(9600);

  Wire.begin();
  mpu.initialize();
  
  Serial.println("MPU6050'ye baglaniliyor");
  Serial.print(mpu.testConnection() ? "MPU6050 ile baglanti kuruldu" : "MPU6050 ile baglanti kurulamadi");
}

void loop() {
  // Read accelerometer and gyroscope data
  

  x = mpu.getRotationX();
  y = mpu.getRotationY();
  z = mpu.getRotationZ();

  // Print data
  
  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(x);
  Serial.print(" Y = "); Serial.print(y);
  Serial.print(" Z = "); Serial.println(z);
  
  delay(1000);
}
//seri haberleşme ile veri göndermek için
void PaketGonder(float aciX,float aciY,float aciZ,float basinc,char tetiklenmeBasinc,char tetiklenmeAci,char paketSayac){
  int checksumDegeri;
  //Serial.print(0x7B);// başlangıç
  
  //Serial.print(0x2F); //ayırıcı
  //Serial.print(0x75);//identifier test paketine özel tanımlayıcı kod 0x75 !!
  //Serial.print(0x2F); //ayırıcı
  test.sayi=basinc;
  Serial.print(test.array[0]);
  Serial.print(test.array[1]);
  Serial.print(test.array[2]);
  Serial.print(test.array[3]);
  Serial.print(0x2F); //ayırıcı
  test.sayi=aciX;
  Serial.print(test.array[0]);
  Serial.print(test.array[1]);
  Serial.print(test.array[2]);
  Serial.print(test.array[3]);
  Serial.print(0x2F); //ayırıcı
  test.sayi=aciY;
  Serial.print(test.array[0]);
  Serial.print(test.array[1]);
  Serial.print(test.array[2]);
  Serial.print(test.array[3]);
  Serial.print(0x2F); //ayırıcı
  test.sayi=aciZ;
  Serial.print(test.array[0]);
  Serial.print(test.array[1]);
  Serial.print(test.array[2]);
  Serial.print(test.array[3]);
  Serial.print(0x2F); //ayırıcı
  Serial.print(0x76);//Basınç ile ayrılma tetiklendi mi
  Serial.print(0x2F); //ayırıcı
  Serial.print(0x76);//Açı ile ayrılma tetiklendi mi
  Serial.print(0x2F); //ayırıcı
  Serial.print(0x76);//Doğrulama Kodu
  Serial.print(0x2F); //ayırıcı
  Serial.print(0x76);//Paket Sayacı
  //Serial.print(false); //ayırıcı
  //Serial.println(0x7D);//Paket bitiş kodu
  

}
//lora ile veri göndermek için
void LoraPaketGonder(float aciX,float aciY,float aciZ,float basinc,char tetiklenmeBasinc,char tetiklenmeAci,char paketSayac){
  int checksumDegeri;
  
  Serial.print(0x00);
  Serial.print(0x3F);//adresleri dinamik yap
  Serial.print(0x17);

  //Serial.print(0x7B);// başlangıç
  //Serial.print(0x2F); //ayırıcı
  //Serial.print(0x75);//identifier test paketine özel tanımlayıcı kod 0x75 !!
  //Serial.print(0x2F); //ayırıcı
  test.sayi=basinc;
  Serial.print(test.array[0]);
  Serial.print(test.array[1]);
  Serial.print(test.array[2]);
  Serial.print(test.array[3]);
  Serial.print(0x2F); //ayırıcı
  test.sayi=aciX;
  Serial.print(test.array[0]);
  Serial.print(test.array[1]);
  Serial.print(test.array[2]);
  Serial.print(test.array[3]);
  Serial.print(0x2F); //ayırıcı
  test.sayi=aciY;
  Serial.print(test.array[0]);
  Serial.print(test.array[1]);
  Serial.print(test.array[2]);
  Serial.print(test.array[3]);
  Serial.print(0x2F); //ayırıcı
  test.sayi=aciZ;
  Serial.print(test.array[0]);
  Serial.print(test.array[1]);
  Serial.print(test.array[2]);
  Serial.print(test.array[3]);
  Serial.print(0x2F); //ayırıcı
  Serial.print(0x76);//Basınç ile ayrılma tetiklendi mi
  Serial.print(0x2F); //ayırıcı
  Serial.print(0x76);//Açı ile ayrılma tetiklendi mi
  Serial.print(0x2F); //ayırıcı
  Serial.print(0x76);//Doğrulama Kodu
  Serial.print(0x2F); //ayırıcı
  Serial.print(0x76);//Paket Sayacı
 //Serial.print(false); //ayırıcı
 // Serial.println(0x7D);//Paket bitiş kodu
  

}
