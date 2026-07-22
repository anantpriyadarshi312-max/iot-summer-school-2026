#include <Stepper.h>

const int stepsPerRev = 2048;

Stepper motor(stepsPerRev, 8, 10, 9, 11);

#define POT A0
#define CW_BTN 2
#define CCW_BTN 3
#define HOME_BTN 4

long currentSteps = 0;

void setup() {
  Serial.begin(9600);

  motor.setSpeed(10);

  pinMode(CW_BTN, INPUT_PULLUP);
  pinMode(CCW_BTN, INPUT_PULLUP);
  pinMode(HOME_BTN, INPUT_PULLUP);
}

void loop() {

  int pot = analogRead(POT);
  int targetAngle = map(pot, 0, 1023, 0, 360);

  if (digitalRead(CW_BTN) == LOW) {
    motor.step(512);      // 45°
    currentSteps += 512;
    delay(200);
  }

  if (digitalRead(CCW_BTN) == LOW) {
    motor.step(-512);     // -45°
    currentSteps -= 512;
    delay(200);
  }

  if (digitalRead(HOME_BTN) == LOW) {
    currentSteps = 0;
    Serial.println("Home Position Set");
    delay(200);
  }

  float currentAngle = (currentSteps % stepsPerRev) * 360.0 / stepsPerRev;

  if (currentAngle < 0)
    currentAngle += 360;

  Serial.print("Target: ");
  Serial.print(targetAngle);
  Serial.print(" deg  ");

  Serial.print("Current: ");
  Serial.print(currentAngle);
  Serial.println(" deg");

  delay(300);
}