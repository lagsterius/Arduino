int rows[] = {A2, A3, 2, 3, 4, 5, 6, 7};
int columns[] = {8, 9, 10, 11, 12, 13, A0, A1};

boolean digit[10][5][3] = {{
  {1, 1, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 1, 1}
},
{
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0}
},
{
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1},
  {1, 0, 0},
  {1, 1, 1}
},
{
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1}
},
{
  {1, 0, 1},
  {1, 0, 1},
  {1, 1, 1},
  {0, 0, 1},
  {0, 0, 1}
},
{
  {1, 1, 1},
  {1, 0, 0},
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1}
},
{
  {1, 1, 1},
  {1, 0, 0},
  {1, 1, 1},
  {1, 0, 1},
  {1, 1, 1}
},
{
  {1, 1, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 1, 0},
  {1, 0, 0}
},
{
  {1, 1, 1},
  {1, 0, 1},
  {1, 1, 1},
  {1, 0, 1},
  {1, 1, 1}
},
{
  {1, 1, 1},
  {1, 0, 1},
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1}
}};

byte digitLen[] = {3, 1, 3, 3, 3, 3, 3, 3, 3, 3};

bool cur_state[8][8];

unsigned long curTime;
byte msgSize, curPos, curLetter, curWS, whiteSpace = 8;
int curSpeed = 500;
char msg[] = "18091996 26091992";

void setup() {
  //Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    pinMode(rows[i], OUTPUT);
    pinMode(columns[i], OUTPUT);
  }
  msgSize = (sizeof msg / sizeof msg[0]) - 1;
}

void loop() {
      
  if ((curTime + curSpeed) < millis()) {    
    //Перенос текста на один столбец
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 7; j++)
        cur_state[i][j] = cur_state[i][j+1];
    
    //Заполнение нового столбца
    for (int j = 1; j < 6; j++)
        cur_state[j][7] =
          (curPos == digitLen[(int)msg[curLetter] - 48]) ? false : digit[(int)msg[curLetter] - 48][j-1][curPos];

    if (curPos == digitLen[(int)msg[curLetter] - 48]) {
      if (curLetter == (msgSize - 1)) {
        curWS++;
        if (curWS == (whiteSpace - 1)) {
          curLetter = 0;
          curWS = 0;
          curPos = 0;
        }
      }
      else {
        curPos = 0;
        curLetter++;
      }
    }
    else {
      curPos++;
    }
    //curPos = (curPos + 1) % msgLen;
    
    //Выключение 1-й и 6-й строки, моргание последней
    //cur_state[7][7] = (curPos % 2) == 1; 
    //cur_state[0][7] = false;
    //cur_state[6][7] = false;
    
    curTime = millis();
  }

  matrixOn();
}

//Включение матрицы
void matrixOn() {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      lights(i, j);
}

//Зажигание светодиода с координатами (i, j)
void lights(int r, int c) {
  //Выключение предыдущего светодиода
  digitalWrite(rows[(r + 8 - 1) % 8], true);
  digitalWrite(columns[(c + 8 - 1) % 8], false);
  //Включение светодиода
  digitalWrite(rows[r], !cur_state[r][c]);
  digitalWrite(columns[c], cur_state[r][c]);
}

 
