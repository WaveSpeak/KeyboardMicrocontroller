#include <Keyboard.h>

const byte ROWS = 3;
const byte COLUMNS = 3;


byte cols[COLUMNS] = { 5, 6, 7 };
byte rows[ROWS] = { 2, 3, 4 };

String keys[COLUMNS][ROWS] = {
  { "3", "6", "9" },
  { "2", "5", "8" },
  { "1", "4", "7" }
};

void setupKeypad() {
  for (byte r = 0; r < COLUMNS; r++) {
    pinMode(cols[r], OUTPUT);
    digitalWrite(cols[r], HIGH);
  }
  for (byte c = 0; c < ROWS; c++) {
    pinMode(rows[c], INPUT_PULLUP);
  }
}

String getKey() {
  for (byte r = 0; r < COLUMNS; r++) {
    digitalWrite(cols[r], LOW);
    for (byte c = 0; c < ROWS; c++) {
      if (digitalRead(rows[c]) == LOW) {
        delay(10);
        if (digitalRead(rows[c]) == LOW) {
          digitalWrite(cols[r], HIGH);
          Serial.println(keys[r][c].c_str());
          return keys[r][c];
        }
      }
    }
    digitalWrite(cols[r], HIGH);
  }
  return "";
}



// Executed once before loop starts looping
void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  setupKeypad();
}

// Loop is executed repeatedly
void loop() {
  String currentKey = getKey();

  Serial.println(currentKey);
  Keyboard.print(currentKey);

  while (currentKey != "") {
    currentKey = getKey();
  }
}
