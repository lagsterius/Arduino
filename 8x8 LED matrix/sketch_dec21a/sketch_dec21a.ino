int rows[] = {A2, A3, 2, 3, 4, 5, 6, 7};
int columns[] = {8, 9, 10, 11, 12, 13, A0, A1};

boolean pic1[8][8] = {
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 1, 1, 1, 0, 1},
  {1, 0, 1, 0, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 1, 0, 1},
  {1, 0, 1, 0, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1}
};

boolean pic2[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

boolean pic3[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

boolean pic4[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

boolean pic[8][8];

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 8; i++) {
    pinMode(rows[i], OUTPUT);
    pinMode(columns[i], OUTPUT);
    digitalWrite(rows[i], true);
    digitalWrite(columns[i], false);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      lights(i, j, pic1[i][j]);
    }
  }
}

void lights(int row, int column, boolean state) {
  digitalWrite(rows[row], !state);
  digitalWrite(columns[column], state);
  digitalWrite(rows[(row + 8 - 1) % 8], true);
  digitalWrite(columns[(column + 8 - 1) % 8], false);
}

 
