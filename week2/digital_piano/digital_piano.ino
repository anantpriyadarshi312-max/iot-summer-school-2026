const int buzzer = 8;
const int buttons[4] = {2, 3, 4, 5};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }

  pinMode(buzzer, OUTPUT);
}

void loop() {
}