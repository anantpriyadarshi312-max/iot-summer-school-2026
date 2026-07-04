const int buzzer = 8;
const int buttons[4] = {2, 3, 4, 5};
const int modeButton = 6;

bool majorMode = true;
bool lastModeState = HIGH;

int majorNotes[4] = {262, 294, 330, 349}; // Do Re Mi Fa
int minorNotes[4] = {262, 294, 311, 349}; // Minor version

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }

  pinMode(modeButton, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Mode toggle
  bool modeState = digitalRead(modeButton);

  if (modeState == LOW && lastModeState == HIGH) {
    majorMode = !majorMode;
    delay(200); // debounce
  }
  lastModeState = modeState;

  int count = 0;
  int lastPressed = -1;

  // Check pressed buttons
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttons[i]) == LOW) {
      count++;
      lastPressed = i;
    }
  }

  if (count == 0) {
    noTone(buzzer);
  }
  else if (count >= 2) {
    tone(buzzer, 392); // Sol chord substitute
  }
  else {
    if (majorMode) {
      tone(buzzer, majorNotes[lastPressed]);
    } else {
      tone(buzzer, minorNotes[lastPressed]);
    }
  }
}