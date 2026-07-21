#include <Arduino.h>

#define MQ2 A0
#define FLAME 7

#define GREEN 10
#define YELLOW 11
#define RED 12

#define BUZZER 9

unsigned long previousMillis = 0;
bool beepState = false;

void setup() {
  Serial.begin(9600);

  pinMode(FLAME, INPUT);

  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  Serial.println("Gas & Fire Alert System");
}

void loop() {

  int gasValue = analogRead(MQ2);
  int gasPercent = map(gasValue, 0, 1023, 0, 100);

  bool flameDetected = (digitalRead(FLAME) == LOW);

  // SAFE
  if (gasPercent < 30 && !flameDetected) {

    digitalWrite(GREEN, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, LOW);

    digitalWrite(BUZZER, LOW);

    Serial.print("GAS: ");
    Serial.print(gasPercent);
    Serial.println("%  STATUS: SAFE");
  }

  // WARNING
  else if (gasPercent >= 30 && gasPercent <= 60 && !flameDetected) {

    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(RED, LOW);

    if (millis() - previousMillis >= 500) {
      previousMillis = millis();
      beepState = !beepState;
      digitalWrite(BUZZER, beepState);
    }

    Serial.print("GAS: ");
    Serial.print(gasPercent);
    Serial.println("%  STATUS: WARNING");
  }

  // DANGER
  else {

    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, HIGH);

    digitalWrite(BUZZER, HIGH);

    Serial.print("GAS: ");
    Serial.print(gasPercent);

    if (flameDetected)
      Serial.println("%  FLAME DETECTED  STATUS: DANGER");
    else
      Serial.println("%  STATUS: DANGER");
  }

  delay(1000);
}