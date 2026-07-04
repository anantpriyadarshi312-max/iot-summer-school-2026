const int ledPin = 9;
const int buttonPin = 2;

int mode = 1;
bool lastButtonState = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Mode 1: Slow Breathing");
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {
    mode++;
    if (mode > 3) mode = 1;

    if (mode == 1) Serial.println("Mode 1: Slow Breathing");
    if (mode == 2) Serial.println("Mode 2: Fast Pulse");
    if (mode == 3) Serial.println("Mode 3: SOS Pattern");

    delay(200);
  }

  lastButtonState = buttonState;

  if (mode == 1) slowBreathing();
  else if (mode == 2) fastPulse();
  else if (mode == 3) sosPattern();
}

void slowBreathing() {
  for (int i = 0; i <= 255; i++) {
    analogWrite(ledPin, i);
    delay(6);
  }

  for (int i = 255; i >= 0; i--) {
    analogWrite(ledPin, i);
    delay(6);
  }
}

void fastPulse() {
  analogWrite(ledPin, 255);
  delay(250);
  analogWrite(ledPin, 0);
  delay(250);
}

void sosPattern() {
  blinkShort();
  blinkShort();
  blinkShort();

  blinkLong();
  blinkLong();
  blinkLong();

  blinkShort();
  blinkShort();
  blinkShort();

  delay(500);
}

void blinkShort() {
  analogWrite(ledPin, 255);
  delay(200);
  analogWrite(ledPin, 0);
  delay(200);
}

void blinkLong() {
  analogWrite(ledPin, 255);
  delay(600);
  analogWrite(ledPin, 0);
  delay(200);
}