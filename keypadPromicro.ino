#include <Keyboard.h>

const byte ROWS = 3;
const byte COLUMNS = 7;
const bool DEBUG = true;
const int MAX_KEYS_PRESSED = 21;



//Must measure current FROM ROWS to COLUMNS due to the diode configuation.
byte cols[COLUMNS] = { 2, 3, 4, 5, 6, 7, 8 };
byte rows[ROWS] = { 9, 10, 16 };

bool KEYS_PRESSED[ROWS][COLUMNS] = { { 0 } };

char keys[ROWS][COLUMNS] = {
  { 'q', 'w', 'e', 'r', 't', 'y', 'u'},
  { 'a', 's', 'd', 'f', 'g', 'h', 'j'},
  { 'z', 'x', 'c', 'v', 'b', 'n', 'm'}
};

void setupKeyMatrix() {
  for (byte c = 0; c < COLUMNS; c++) {
    pinMode(cols[c], INPUT_PULLUP);
  }
  for (byte r = 0; r < ROWS; r++) {
    pinMode(rows[r], OUTPUT);
    digitalWrite(rows[r], HIGH);
  }
}

void scanKeyMatrix() {
  for (int r = 0; r < ROWS; r++)
  {
    for (int c = 0; c < COLUMNS; c++)
    {
      digitalWrite(rows[r], LOW);

      if (digitalRead(cols[c]) == 0){
        KEYS_PRESSED[r][c] = true;
      }
      else{
        KEYS_PRESSED[r][c] = false;
      }
      digitalWrite(rows[r], HIGH);
    }
  }
  if (DEBUG)
    delay(150); //Debugging purposes
}


// Executed once before loop starts looping
void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  setupKeyMatrix();
}

// Loop is executed repeatedly
void loop() {
  scanKeyMatrix();
  for (int r = 0; r < ROWS; r++)
  {
    for (int c = 0; c < COLUMNS; c++)
    {
      if (KEYS_PRESSED[r][c])
      {
        Keyboard.write(keys[r][c]);
        delay(150);
      }
    }
  }
  Serial.println();
}
