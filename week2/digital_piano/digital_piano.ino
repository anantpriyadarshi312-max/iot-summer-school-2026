void loop() {
  int count = 0;
  int lastPressed = -1;

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
    tone(buzzer, 392); // Sol
  }
  else {
    tone(buzzer, notes[lastPressed]);
  }
}