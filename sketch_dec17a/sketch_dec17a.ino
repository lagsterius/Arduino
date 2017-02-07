byte rows[8] = {16, 17, 2, 3, 4, 5, 6, 7};
byte cols[8] = {8, 9, 10, 11, 12, 13, 14, 15};
byte prev_i = -1, prev_j = -1, text_lenght, k, last_i, last_j, probel_bukva = 1, probel_konec = 8, probel = 4;
unsigned int text_speed = 1000;
byte bukva_len[] = {4, 4};
unsigned long int prev_time;

byte zero_row;

byte prev_matrix[8];

const byte bukva[][6] =
  {
    {
      B01111111,
      B10001000,
      B10001000,
      B11111111,
      0,
      0
    },
    {
      B11111111,
      B10010001,
      B10010001,
      B10001110,
      0,
      0
    }
    
  };

void turn_off_prev() {
  if (prev_i != -1 && prev_j != -1)
  {
    digitalWrite(rows[prev_i], HIGH);
    digitalWrite(cols[prev_j], LOW);
  }
}

void turn_off(int i, int j)
{
  digitalWrite(rows[i], HIGH);
  digitalWrite(cols[j], LOW);
}

void turn_on(int i, int j)
{
  turn_off_prev();
  dr(rows[i], 0);
  dr(cols[j], 1);
  prev_i = i;
  prev_j = j;
}

void dr(byte pin, bool state)
{
  if (pin > 13)
  {
    PORTD = state ? PORTD | round(pow(2,(pin - 14))) : PORTD & round(pow(2, (pin - 14)));
  }
  else if (pin > 7)
  {
    PORTB = state ? PORTB | round(pow(2, (pin - 8))) : PORTB & round(pow(2,(pin - 8)));
  }
  else
  {
    PORTC = state ? PORTC | round(pow(2, pin)) : PORTC & round(pow(2, pin));
  }
}

void setup() {
  Serial.begin(9600);
  
  DDRD |= B11111100;
  DDRB |= B00111111;
  DDRC |= B00001111;

  PORTD = B00111111;
  PORTB = B00000000;
  PORTC = B00001100;

  prev_time = millis();
}

void loop() {
  String hello = "A";
  for (int i = 0; i < hello.length(); i++)
    if (hello[i] != ' ')
      case_bukva(hello[i]);
    else
      space(probel);
  space(probel_konec);
}

void space(byte len)
{
  
}

void case_bukva(char x)
{
  switch (x)
  {
    case 'A':
      Serial.println("A");
      print_bukva(0);
      break;
     case 'B':
      Serial.println("B");
      print_bukva(1);
      break;
  }
}

void print_bukva(byte x)
{
  k = 0;
  while (k < bukva_len[x] + probel_bukva)
  {
    if ((prev_time + text_speed) < millis())
    {
      zero_row = (k < bukva_len[x]) ? bukva[x][k] : 0;
      prev_time = millis();
      k++;
      for (int i = 0; i < 7; i++)
        prev_matrix[i] = prev_matrix[i + 1];
      prev_matrix[7] = zero_row;

      for (int i = 0; i < 8; i++)
      {
        
        Serial.println(prev_matrix[i], BIN);
        digitalWrite(cols[i == 0 ? 7 : i - 1], LOW);
        for (int j = 0; j < 8; j++)
          if (B00000001 & prev_matrix[i] >> j) digitalWrite(rows[j], LOW); 
        digitalWrite(cols[i], HIGH);
      }
      Serial.println();
    }
  }


}

int my_pow(int x, int y)
{
  for (int i = 0; i < y; i++)
    x *= x;
  return x;
}

