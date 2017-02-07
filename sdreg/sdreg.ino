//**************************************************************//
//  Name    : shiftOutCode, Hello World                               
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis
//  Date    : 25 Oct, 2006   
//  Modified: 23 Mar 2010                                
//  Version : 2.0                                            
//  Notes   : Программа использует один сдвиговый регистр 74HC595
//          : для вывода значений от 0 до 255                           
//****************************************************************
 
//Пин подключен к ST_CP входу 74HC595
int latchPin = 8;
//Пин подключен к SH_CP входу 74HC595
int clockPin = 12;
//Пин подключен к DS входу 74HC595
int dataPin = 11;
 
 
 
void setup() {
  //устанавливаем режим OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
 
void loop() {
  // отсчитываем от 0 до 255  и отображаем значение на светодиоде
  for (int numberToDisplay = 0; numberToDisplay < B111; numberToDisplay++) {
    // устанавливаем синхронизацию "защелки" на LOW
    digitalWrite(latchPin, LOW);
    // передаем последовательно на dataPin
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay); 
 
    //"защелкиваем" регистр, тем самым устанавливая значения на выходах
    digitalWrite(latchPin, HIGH);
    // пауза перед следующей итерацией
    delay(500);
  }
}

