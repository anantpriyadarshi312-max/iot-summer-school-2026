const int LED = 13;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {

  // Blink 3 times quickly
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED, HIGH);
    delay(200);

    digitalWrite(LED, LOW);
    delay(200);
  }

  // Pause for 2 seconds
  delay(2000);
}
