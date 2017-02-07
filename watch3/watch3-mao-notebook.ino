#define B0 31
#define C1 33
#define CS1 35
#define D1 37
#define DS1 39
#define E1 41
#define F1 44
#define FS1 46
#define G1 49
#define GS1 52
#define _A1 55
#define AS1 58
#define B1 62
#define C2 65
#define CS2 69
#define D2 73
#define DS2 78
#define E2 82
#define F2 87
#define FS2 93
#define G2 98
#define GS2 104
#define _A2 110
#define AS2 117
#define B2 123
#define C3 131
#define CS3 139
#define D3 147
#define DS3 156
#define E3 165
#define F3 175
#define FS3 185
#define G3 196
#define GS3 208
#define _A3 220
#define AS3 233
#define B3 247
#define C4 262
#define CS4 277
#define D4 294
#define DS4 311
#define E4 330
#define F4 349
#define FS4 370
#define G4 392
#define GS4 415
#define _A4 440
#define AS4 466
#define B4 494
#define C5 523
#define CS5 554
#define D5 587
#define DS5 622
#define E5 659
#define F5 698
#define FS5 740
#define G5 784
#define GS5 831
#define _A5 880
#define AS5 932
#define B5 988
#define C6 1047
#define CS6 1109
#define D6 1175
#define DS6 1245
#define E6 1319
#define F6 1397
#define FS6 1480
#define G6 1568
#define GS6 1661
#define _A6 1760
#define AS6 1865
#define B6 1976
#define C7 2093
#define CS7 2217
#define D7 2349
#define DS7 2489
#define E7 2637
#define F7 2794
#define FS7 2960
#define G7 3136
#define GS7 3322
#define _A7 3520
#define AS7 3729
#define B7 3951
#define C8 4186
#define CS8 4435
#define D8 4699
#define DS8 4978

#define latchPin 8
#define _clockPin 12
#define _dataPin 11
#define hp 2
#define _hm 3
#define mp 4
#define mm 5
#define ok 6
#define cancel 7
#define pz 9
#define del 143
#define del 4

#include <Wire.h>
#include <DS1307new.h>
#include <EEPROM.h>

uint16_t startAddr = 0x0000;
uint16_t TimeIsSet = 0xaa55;
byte dat = 255;

boolean alarm, change;
byte bh, bm, rejim, max_day, new_day, new_month;
unsigned long prev_time;
//volatile int state = LOW;

void setup() { 
  //1 - OUTPUT, 0 - INPUT
  DDRD = DDRD | B00000000;
  DDRB = DDRB | B00111001;
  DDRC = DDRC | B00000111;
  
  RTC.setRAM(0, (uint8_t *)&startAddr, sizeof(uint16_t));
  RTC.getRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
  RTC.getTime();
  RTC.ctrl = 0x00;
  RTC.setCTRL();
  
  if (EEPROM.read(1) == 255) {
    alarm = false;
    bh = 0;
    bm = 0;
  }
  else {
    alarm = EEPROM.read(1) > 31 ? true : false;
    bh = B00011111 & EEPROM.read(1);
    bm = EEPROM.read(2);
  }
  
  digitalWrite(A0, true);
  analogWrite(10, alarm ? 30 : 0);
  digitalWrite(13, false);
  
  //attachInterrupt(1, ChangeDigits, CHANGE);
}
 
void loop() {
  if (digitalRead(hp)) st(false, false, rejim);
  else if (digitalRead(_hm)) st(false, true, rejim);
  else if (digitalRead(mp)) st(true, false, rejim);
  else if (digitalRead(mm)) st(true, true, rejim);
  else if (digitalRead(ok)) {
    rejim = (rejim + 1) % 3;
    digitalWrite(A0, rejim == 0 ? true : false);
    digitalWrite(A1, rejim == 1 ? true : false);
    digitalWrite(A2, rejim == 2 ? true : false);
    delay(300);
  }
  else if (rejim == 2 && digitalRead(cancel)) {
    sd(8, 252, 0);
    alarm = !alarm;
    delay(300);
    prev_time = millis();
    change = true;
    analogWrite(10, alarm ? 30 : 0);
  }
  
  ChangeDigits();
  
  if (alarm && RTC.hour == bh && RTC.minute == bm && RTC.second == 0) {
      sd(8, 252, 0);
      Tanchiki();
    } 
  
  if (change && prev_time + 30000 < millis()) {
      change = false;
      EEPROM.write(1, (alarm ? 32 : 0) + bh);
      EEPROM.write(2, bm);
  }
}

void ChangeDigits()
{
  if (rejim < 2) {
    RTC.getTime();
    if (rejim == 1) {
      sd(RTC.day/10, 128, 0);
      delay(del);
      sd(RTC.day%10, 64, 1);
      delay(del);
      sd(RTC.month/10, 32, 0);
      delay(del);
      sd(RTC.month%10, 16, 1);
      delay(del);
      sd(RTC.year%100/10, 8, 0);
      delay(del);
      sd(RTC.year%10, 4, 0);
      delay(del);
    }
    else {
      sd(RTC.hour/10, 128, RTC.second);
      delay(del);
      sd(RTC.hour%10, 64, RTC.second);
      delay(del);
      sd(RTC.minute/10, 32, RTC.second);
      delay(del);
      sd(RTC.minute%10, 16, RTC.second);
      delay(del);
      sd(RTC.second/10, 8, RTC.second);
      delay(del);
      sd(RTC.second%10, 4, RTC.second);
      delay(del);
    }
  }
  else {
    sd(bh/10, 128, 0);
    delay(del);
    sd(bh%10, 64, alarm ? 1 : 0);
    delay(del);
    sd(bm/10, 32, 0);
    delay(del);
    sd(bm%10, 16, alarm ? 1 : 0);
    delay(del);
    sd(0, 8, 0);
    delay(del);
    sd(alarm ? 11 : 12, 4, 0);
    delay(del);
  }
  //state != state;
}



void sd (int digit, int p, int tick) {
  if      (digit == 0)  dat = B10000001;
  else if (digit == 1)  dat = B11110011;
  else if (digit == 2)  dat = B01001001;
  else if (digit == 3)  dat = B01100001;
  else if (digit == 4)  dat = B00110011;
  else if (digit == 5)  dat = B00100101;
  else if (digit == 6)  dat = B00000101;
  else if (digit == 7)  dat = B11110001;
  else if (digit == 8)  dat = B00000001;
  else if (digit == 9)  dat = B00100001;
  else if (digit == 11) dat = B10010001;
  else if (digit == 12) dat = B00011101;
  else                  dat = B11111110;
  
  digitalWrite(latchPin, LOW);
  
  //128 - H1, 64 - H2, 32 - M1, 16 - M2, 8 - S1, 4 - S2
  shiftOut(_dataPin, _clockPin, MSBFIRST, p); 
  shiftOut(_dataPin, _clockPin, MSBFIRST, dat - tick % 2); 
  digitalWrite(latchPin, HIGH);
}

void st(boolean hm, boolean pm, int rejim) {
  sd(0, 0, 0);
  
  if (rejim < 2) {
    TimeIsSet = 0xffff;
    RTC.setRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
    RTC.getRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
    RTC.stopClock();
    
    if (rejim == 0) {
      RTC.fillByHMS(hm ? (RTC.hour) : (pm ? (RTC.hour == 0 ? 23 : RTC.hour - 1) : (RTC.hour == 23 ? 0 : RTC.hour + 1)), hm ? (pm ? (RTC.minute == 0 ? 59 : RTC.minute -1) : (RTC.minute == 59 ? 0 : RTC.minute + 1)) : (RTC.minute), 1);
    }
    else {
      new_month = hm ? (pm ? (RTC.month == 1 ? 12 : RTC.month - 1) : (RTC.month == 12 ? 1 : RTC.month + 1)) : RTC.month;
      RTC.fillByYMD(RTC.year, new_month, RTC.day);
      max_day = (RTC.month == 4 || RTC.month == 6 || RTC.month == 9 || RTC.month == 11) ? 30 : (RTC.month == 2 ? (RTC.year % 4 == 0 ? 29 : 28) : 31);
      new_day = hm ? (RTC.day) : (pm ? (RTC.day == 1 ? max_day : RTC.day - 1) : (RTC.day == max_day ? 1 : RTC.day + 1));
      new_day = (RTC.day > max_day) ? max_day : new_day;
      RTC.fillByYMD(RTC.year, new_month, new_day);
    }
  
    RTC.setTime();
    TimeIsSet = 0xaa55;
    RTC.setRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
    RTC.startClock();
    RTC.ctrl = 0x00;
    RTC.setCTRL();
  }
  else {
    prev_time = millis();
    if (hm) bm = pm ? (bm == 0 ? 59 : (bm - 1)) : (bm == 59 ? 0 : (bm + 1));
    else bh = pm ? (bh == 0 ? 23 : (bh - 1)) : (bh == 23 ? 0 : (bh + 1));
    change = true;
  }
  
  delay(300);
}


void Tanchiki() {
   t(C3);
   t(D3);
   t(DS3);
   t(C3);
   t(D3);
   t(DS3);
   
   t(DS3);
   t(F3);
   t(G3);
   t(DS3);
   t(F3);
   t(G3);
   
   t(F3);
   t(G3);
   t(_A3);
   t(F3);
   t(G3);
   t(_A3);
   
   t(GS3);
   t(AS3);
   t(C4);
   t(GS3);
   t(AS3);
   t(C4);
   
   t(C4);
   delay(1.5*del);
   t(C4);
   t(C4);
   t(C4);
   t(C4);
}

void t(unsigned int M) {
  tone(pz, M, del);
  delay(del);
}

