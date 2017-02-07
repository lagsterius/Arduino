#include <IRremote.h>

const int two = 2;
const int three = 4;
const int ir = 6;
const int pz = 9;

int lvl = 0;
long int sw_btn = 551334792;
long int btn = 1150532780;

IRrecv irrecv(ir);
decode_results results;

void setup() {
  irrecv.enableIRIn();
  pinMode(two, OUTPUT);
  pinMode(three, OUTPUT);
  pinMode(pz, OUTPUT);
}

void loop() {
  if ((irrecv.decode(&results))) {
    if (results.value == btn) light();
    else if (results.value == sw_btn) switch_button();
    delay(50);
    irrecv.resume();
  }
}

void light() {
  switch(lvl) {
  case 0:
    digitalWrite(two, 1);
    digitalWrite(three, 0);
    lvl = 1;
    break;
  case 1:
    digitalWrite(two, 0);
    digitalWrite(three, 1);
    lvl = 2;
    break;
  case 2:
    digitalWrite(two, 1);
    digitalWrite(three, 1);
    lvl = 3;
    break;
  default:
    digitalWrite(two, 0);
    digitalWrite(three, 0);
    lvl = 0;
  }
}

void switch_button() {
  play();
  while(!(irrecv.decode(&results))||results.value==sw_btn) {
    irrecv.resume();
    delay(100);
  }
  btn = results.value;
  play();
}

void play() {
    beep(50);
    beep(50);
    beep(50);
    beep(50);
    beep(50);
    beep(50);
    beep(50);
    beep(50);
    beep(50);
}

void beep(unsigned char delayms){
  analogWrite(pz, 20);
  delay(delayms);
  analogWrite(pz, 0);
  delay(delayms); 
}










