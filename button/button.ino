void setup() {
  pinMode(3,OUTPUT);
  pinMode(4,INPUT);
  digitalWrite(4,HIGH);
}

void loop() {
  
  digitalWrite(3,!digitalRead(4));
  delay(500);
}
