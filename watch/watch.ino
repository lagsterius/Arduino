int i = 0;
int dl = 25;
int divi = 0;
unsigned long millis_start;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
}

void loop() {
  sd(i);
  i = (i+1)%10;
}

void blink (int pin, int del) {
  digitalWrite(pin+1, LOW);
  delay(dl/del);
  digitalWrite(pin+1, HIGH);
}

void sd(int digit) {
  millis_start = millis();
  switch (digit) {
    case 0:
      divi = 7;
      while ((millis_start + 1000) > millis())  {
        blink(2, divi);
        blink(3, divi);
        blink(4, divi);
        blink(5, divi);
        blink(6, divi);
        blink(7, divi);
        blink(8, divi);
      }
      break;
    case 1:
      divi = 2;
      while ((millis_start + 1000) > millis())  {
        blink(5, divi);
        blink(8, divi);
      }
      break;
    case 2:
      divi = 6;
      while ((millis_start + 1000) > millis())  {
        blink(1, divi);
        blink(3, divi);
        blink(4, divi);
        blink(5, divi);
        blink(6, divi);
        blink(7, divi);
      }
      break;
    case 3: 
      divi = 5;
      while ((millis_start + 1000) > millis())  {
        blink(1, divi);
        blink(4, divi);
        blink(5, divi);
        blink(7, divi);
        blink(8, divi);
      }
      break;

    case 4: 
      divi = 5;
      while ((millis_start + 1000) > millis())  {
        blink(1, divi);
        blink(2, divi);
        blink(3, divi);
        blink(5, divi);
        blink(8, divi);
      }
      break;
    case 5: 
      divi = 5;
      while ((millis_start + 1000) > millis())  {
        blink(1, divi);
        blink(2, divi);
        blink(4, divi);
        blink(7, divi);
        blink(8, divi);
      }
      break;
    case 6:
      divi = 7;
      while ((millis_start + 1000) > millis())  {
        blink(1, divi);
        blink(2, divi);
        blink(3, divi);
        blink(4, divi);
        blink(6, divi);
        blink(7, divi);
        blink(8, divi);
      }
    case 7:
      divi = 3;
      while ((millis_start + 1000) > millis())  {
        blink(4, divi);
        blink(5, divi);
        blink(8, divi);
      }
      break;
    case 8:
      divi = 8;
      while ((millis_start + 1000) > millis())  {
        blink(1, divi);
        blink(2, divi);
        blink(3, divi);
        blink(4, divi);
        blink(5, divi);
        blink(6, divi);
        blink(7, divi);
        blink(8, divi);
      }
    default:
      divi = 6;
      while ((millis_start + 1000) > millis())  {
        blink(1, divi);
        blink(2, divi);
        blink(4, divi);
        blink(5, divi);
        blink(7, divi);
        blink(8, divi);
      }
  }
}









