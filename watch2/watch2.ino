//Пин подключен к ST_CP входу 74HC595
int latchPin = 8;
//Пин подключен к SH_CP входу 74HC595
int clockPin = 12;
//Пин подключен к DS входу 74HC595
int dataPin = 11;
 
int dat1 = 255;
int dat2 = 255;
int s1 = 0;
int s2 = 0;
 
void setup() {
  //устанавливаем режим OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  
}
 
void loop() {
  sd(s2, s1);
  s2 = (s2 + 1) % 10;
  if (s2 == 0) s1 = (s1+1) % 10;
  delay(1000);
}

void sd (int digit1, int digit2) {
  if      (digit1 == 0) dat1 = 129;
  else if (digit1 == 1) dat1 = 243;
  else if (digit1 == 2) dat1 = 73;
  else if (digit1 == 3) dat1 = 97;
  else if (digit1 == 4) dat1 = 51;
  else if (digit1 == 5) dat1 = 37;
  else if (digit1 == 6) dat1 = 5;
  else if (digit1 == 7) dat1 = 241;
  else if (digit1 == 8) dat1 = 1;
  else if (digit1 == 9) dat1 = 33;
  else                  dat1 = 254;
  
  if      (digit2 == 0) dat2 = 129;
  else if (digit2 == 1) dat2 = 243;
  else if (digit2 == 2) dat2 = 73;
  else if (digit2 == 3) dat2 = 97;
  else if (digit2 == 4) dat2 = 51;
  else if (digit2 == 5) dat2 = 37;
  else if (digit2 == 6) dat2 = 5;
  else if (digit2 == 7) dat2 = 241;
  else if (digit2 == 8) dat2 = 1;
  else if (digit2 == 9) dat2 = 33;
  else                  dat2 = 254;
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, dat1); 
  shiftOut(dataPin, clockPin, MSBFIRST, dat2); 
  digitalWrite(latchPin, HIGH);
}
