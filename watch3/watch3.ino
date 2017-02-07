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

#include <Wire.h>
#include <DS1307new.h>

uint16_t startAddr = 0x0000;            // Start address to store in the NV-RAM
uint16_t TimeIsSet = 0xaa55;            // Helper that time must not set again

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
int hp = 2;
int hm = 3;
int mp = 4;
int mm = 5;
int ok = 6;
int cancel = 7;
int pz = 9;

int rejim = 0;
int dat = 255;

int m, d;
int bh = 0;
int bm = 0;



void setup() {
  //устанавливаем режим OUTPUT
  pinMode(latchPin, OUTPUT); 
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  pinMode(hp, INPUT);
  pinMode(hm, INPUT);
  pinMode(mp, INPUT);
  pinMode(mm, INPUT);
  pinMode(ok, INPUT);
  pinMode(cancel, INPUT);
  
  RTC.setRAM(0, (uint8_t *)&startAddr, sizeof(uint16_t));// Store startAddr in NV-RAM address 0x08
  RTC.getRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
  RTC.getTime();
  RTC.ctrl = 0x00;
  RTC.setCTRL();
}
 
void loop() {
  if (digitalRead(hp) == true) 
  {
    sd(0, 0, 0);
    st(false, false, rejim);
    delay(300);
  }
  else if (digitalRead(hm) == true)
  {
    sd(0, 0, 0);
    st(false, true, rejim);
    delay(300);
  }
  else if (digitalRead(mp) == true)
  {
    sd(0, 0, 0);
    st(true, false, rejim);
    delay(300);
  }
  else if (digitalRead(mm) == true)
  {
    sd(0, 0, 0);
    st(true, true, rejim);
    delay(300);
  }
  
  if (rejim == 0 || rejim == 1)
  {
    RTC.getTime();
    if (rejim == 1)
    {
      sd(RTC.day/10, 128, 0);
      delay(5);
      sd(RTC.day%10, 64, 0);
      delay(5);
      sd(RTC.month/10, 32, 0);
      delay(5);
      sd(RTC.month%10, 16, 0);
      delay(5);
    }
    else 
    {
      sd(RTC.hour/10, 128, RTC.second);
      delay(5);
      sd(RTC.hour%10, 64, RTC.second);
      delay(5);
      sd(RTC.minute/10, 32, RTC.second);
      delay(5);
      sd(RTC.minute%10, 16, RTC.second);
      delay(5);
    }
  }
  else
  {
    sd(bh/10, 128, 1);
    delay(5);
    sd(bh%10, 64, 1);
    delay(5);
    sd(bm/10, 32, 1);
    delay(5);
    sd(bm%10, 16, 1);
    delay(5);
  }
  
  if (RTC.hour == bh && RTC.minute == bm && RTC.second == 0)
    {
      sd(8, 240, 0);
      Tanchiki();
    } 
  if (digitalRead(ok) == true)
  {
    rejim = (rejim+1) % 3;
    delay(300);
  }
}

void sd (int digit, int p, int tick)
{
  if      (digit == 0) dat = 129;
  else if (digit == 1) dat = 243;
  else if (digit == 2) dat = 73;
  else if (digit == 3) dat = 97;
  else if (digit == 4) dat = 51;
  else if (digit == 5) dat = 37;
  else if (digit == 6) dat = 5;
  else if (digit == 7) dat = 241;
  else if (digit == 8) dat = 1;
  else if (digit == 9) dat = 33;
  else                 dat = 254;
  
  if (tick % 2 == 0) dat--;
  
  digitalWrite(latchPin, LOW);
  
  //128 - H1, 64 - H2, 32 - M1, 16 - M2
  shiftOut(dataPin, clockPin, MSBFIRST, p); 
  shiftOut(dataPin, clockPin, MSBFIRST, dat); 
  digitalWrite(latchPin, HIGH);
}

void st(boolean hm, boolean pm, int rejim)
{
  if (rejim == 0 || rejim == 1)
  {
  TimeIsSet = 0xffff;
  RTC.setRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
  RTC.getRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
  RTC.stopClock();
  if (rejim == 0)
  {
    RTC.fillByHMS(RTC.hour + (hm ? 0 : 1) * (pm ? -1 : 1), RTC.minute + (hm ? 1 : 0) * (pm ? -1 : 1), 1);
  }
  else
  {
    RTC.fillByYMD(RTC.year, hm ? (pm ? (RTC.month == 1 ? 12 : RTC.month - 1) : (RTC.month == 12 ? 1 : RTC.month + 1)) : RTC.month, RTC.day + (hm ? 0 : 1) * (pm ? -1 : 1));
  }
  RTC.setTime();
  TimeIsSet = 0xaa55;
  RTC.setRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
  RTC.startClock();
  RTC.ctrl = 0x00;
  RTC.setCTRL();
  }
  else
  {
    bh += (hm ? 0 : 1) * (pm ? -1 : 1) % 24;
    bm += (hm ? 1 : 0) * (pm ? -1 : 1) % 24;
  }
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


