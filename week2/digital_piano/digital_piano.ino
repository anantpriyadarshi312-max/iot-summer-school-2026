const int buzzer = 8;
const int buttons[4] = {2, 3, 4, 5};
int notes[4] = {262, 294, 330, 349};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  pinMode(buzzer, OUTPUT);
}

void loop() {
  bool played = false;

  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttons[i]) == LOW) {
      tone(buzzer, notes[i]);
      played = true;
      break;
    }
  }

  if (!played) {
    noTone(buzzer);
  }
}