/*
Author: ANANT PRIYADARSHI
Date: 30-06-2026
Description: LED blink with serial counter and potentiometer speed control
*/

int count = 0;
int potValue = 0;
int delayTime = 500;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  potValue = analogRead(A0);
  delayTime = map(potValue, 0, 1023, 100, 1000);

  digitalWrite(13, HIGH);
  delay(delayTime);
  digitalWrite(13, LOW);
  delay(delayTime);

  count++;
  Serial.print("Blink count: ");
  Serial.println(count);
}