#include <SPI.h>
#include <MFRC522.h>

#define _B0 31
#define _C1 33
#define _CS1 35
#define _D1 37
#define _DS1 39
#define _E1 41
#define _F1 44
#define _FS1 46
#define _G1 49
#define _GS1 52
#define _A1 55
#define _AS1 58
#define _B1 62
#define _C2 65
#define _CS2 69
#define _D2 73
#define _DS2 78
#define _E2 82
#define _F2 87
#define _FS2 93
#define _G2 98
#define _GS2 104
#define _A2 110
#define _AS2 117
#define _B2 123
#define _C3 131
#define _CS3 139
#define _D3 147
#define _DS3 156
#define _E3 165
#define _F3 175
#define _FS3 185
#define _G3 196
#define _GS3 208
#define _A3 220
#define _AS3 233
#define _B3 247
#define _C4 262
#define _CS4 277
#define _D4 294
#define _DS4 311
#define _E4 330
#define _F4 349
#define _FS4 370
#define _G4 392
#define _GS4 415
#define _A4 440
#define _AS4 466
#define _B4 494
#define _C5 523
#define _CS5 554
#define _D5 587
#define _DS5 622
#define _E5 659
#define _F5 698
#define _FS5 740
#define _G5 784
#define _GS5 831
#define _A5 880
#define _AS5 932
#define _B5 988
#define _C6 1047
#define _CS6 1109
#define _D6 1175
#define _DS6 1245
#define _E6 1319
#define _F6 1397
#define _FS6 1480
#define _G6 1568
#define _GS6 1661
#define _A6 1760
#define _AS6 1865
#define _B6 1976
#define _C7 2093
#define _CS7 2217
#define _D7 2349
#define _DS7 2489
#define _E7 2637
#define _F7 2794
#define _FS7 2960
#define _G7 3136
#define _GS7 3322
#define _A7 3520
#define _AS7 3729
#define _B7 3951
#define _C8 4186
#define _CS8 4435
#define _D8 4699
#define _DS8 4978

int pz = 5;
byte* x;
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

String nmb;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Scan PICC to see UID and type...");
}

void loop() {
  nmb="";
  if (!mfrc522.PICC_IsNewCardPresent()||!mfrc522.PICC_ReadCardSerial()) return;
  Serial.print("old Card UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) nmb+=String(mfrc522.uid.uidByte[i], HEX); 
  Serial.println(nmb);
  nmb="";
  Serial.print("new Card UID: ");
  byte cmdBuffer[2];
  cmdBuffer[0] = 0xA0;
  cmdBuffer[1] = 0-0xff;
  mfrc522.PCD_MIFARE_Transceive(cmdBuffer, 2);
  x = &0xabcdef11;
  mfrc522.PCD_MIFARE_Transceive(x, 16);
  for (byte i = 0; i < mfrc522.uid.size; i++) nmb+=String(mfrc522.uid.uidByte[i], HEX); 
  Serial.print(nmb);
  
  //if(nmb=="44fc4a4d3383") Tanchiki();
  //if(nmb=="43944a4d3383") NokiaTune();
  //if(nmb=="34c18b1a4b36") NEM();
  Serial.println();
  delay(1000);
}

void NEM() {
  int del = 350;

  tone(pz,_E2,del);
  delay(del);
  tone(pz,_G3,del);
  delay(del);
  tone(pz,_B3,del);
  delay(del);
  tone(pz,_E4,del);
  delay(del);
  tone(pz,_B3,del);
  delay(del);
  tone(pz,_G3,del);
  delay(del); 

  tone(pz,_E2,del);
  delay(del);
  tone(pz,_G3,del);
  delay(del);
  tone(pz,_B3,del);
  delay(del);
  tone(pz,_E4,del);
  delay(del);
  tone(pz,_B3,del);
  delay(del);
  tone(pz,_G3,del);
  delay(del);

  tone(pz,_E2,del);
  delay(del);
  tone(pz,_G3,del);
  delay(del);
  tone(pz,_B3,del);
  delay(del);
  tone(pz,_E4,del);
  delay(del);
  tone(pz,_B3,del);
  delay(del);

  tone(pz,_B4,del);
  delay(del); 
  tone(pz,_B4,del);
  delay(del); 
  tone(pz,_B3,del);
  delay(del);
  tone(pz,_G3,del);
  delay(del);
  tone(pz,_B4,.5*del);
  delay(.5*del); 
  tone(pz,_E4,.5*del);
  delay(.5*del);
  tone(pz,_B3,del);
  delay(del);
  tone(pz,_G3,del);
  delay(del); 

  tone(pz,_E2,del);
  delay(del);
  tone(pz,_G3,del);
  delay(del);
  tone(pz,_B4,del);
  delay(del); 
  tone(pz,_C5,del);
  delay(del);
  tone(pz,_B4,del);
  delay(del); 
  tone(pz,_A4,del);
  delay(del);
  tone(pz,_B4,del);
  delay(del);
  tone(pz,_A4,del);
  delay(del);
  tone(pz,_G4,del);
  delay(del);
  tone(pz,_E4,del);
  delay(del); 
}

void NokiaTune() {
  int del=180;
  tone(pz,_E7,del);
  delay(del);
  tone(pz,_D7,del);
  delay(del);
  tone(pz,_FS6,2*del);
  delay(2*del);
  tone(pz,_GS6,1.8*del);
  delay(2*del);

  tone(pz,_CS7,del);
  delay(del);
  tone(pz,_B6,del);
  delay(del);
  tone(pz,_D6,2*del);
  delay(2*del);
  tone(pz,_E6,1.8*del);
  delay(2*del);

  tone(pz,_B6,del);
  delay(del);
  tone(pz,_A6,del);
  delay(del);
  tone(pz,_CS6,2*del);
  delay(2*del);
  tone(pz,_E6,1.5*del);
  delay(2*del);

  tone(pz,_A6,3*del);
}

void Tanchiki() {
  int del = 143;
  tone(pz,_C3,del);
  delay(del);
  tone(pz,_D3,del);
  delay(del);
  tone(pz,_DS3,del);
  delay(del);
  tone(pz,_C3,del);
  delay(del);
  tone(pz,_D3,del);
  delay(del);
  tone(pz,_DS3,del);
  delay(del);

  tone(pz,_DS3,del);
  delay(del);
  tone(pz,_F3,del);
  delay(del);
  tone(pz,_G3,del);
  delay(del);
  tone(pz,_DS3,del);
  delay(del);
  tone(pz,_F3,del);
  delay(del);
  tone(pz,_G3,del);
  delay(del);

  tone(pz,_F3,del);
  delay(del);
  tone(pz,_G3,del);
  delay(del);
  tone(pz,_A3,del);
  delay(del);
  tone(pz,_F3,del);
  delay(del);
  tone(pz,_G3,del);
  delay(del);
  tone(pz,_A3,del);
  delay(del);

  tone(pz,_GS3,del);
  delay(del);
  tone(pz,_AS3,del);
  delay(del);
  tone(pz,_C4,del);
  delay(del);
  tone(pz,_GS3,del);
  delay(del);
  tone(pz,_AS3,del);
  delay(del);
  tone(pz,_C4,del);
  delay(del);

  tone(pz,_C4,del);
  delay(2.5*del);

  tone(pz,_C4,del);
  delay(del);
  tone(pz,_C4,del);
  delay(del);
  tone(pz,_C4,del);
  delay(del);
  tone(pz,_C4,del);
}

