/*
-------------------------------------------------------
Ultrasonic Parking Sensor using HC-SR04

Distance > 50 cm
    - SAFE
    - Green LED ON
    - Buzzer OFF

Distance 20 - 50 cm
    - Yellow LED ON
    - Buzzer beeps every 500 ms

Distance 10 - 20 cm
    - Red LED ON
    - Buzzer beeps every 200 ms

Distance < 10 cm
    - All LEDs flash rapidly
    - Buzzer ON continuously

Distance Formula:
distance = (duration * 0.034) / 2

Uses millis() for non-blocking timing.
-------------------------------------------------------
*/

const int trigPin = 9;
const int echoPin = 10;

const int redLED = 2;
const int yellowLED = 3;
const int greenLED = 4;

const int buzzer = 8;

unsigned long previousMillis = 0;
bool toggleState = false;

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  long duration;
  float distance;

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  // Distance formula
  distance = (duration * 0.034) / 2.0;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  unsigned long currentMillis = millis();

  // ---------------- SAFE ----------------
  if (distance > 50) {

    Serial.println("SAFE");

    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);

    noTone(buzzer);
  }

  // ------------ 20 to 50 cm ------------
  else if (distance > 20) {

    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);

    if (currentMillis - previousMillis >= 500) {

      previousMillis = currentMillis;

      toggleState = !toggleState;

      if (toggleState)
        tone(buzzer, 1000);
      else
        noTone(buzzer);
    }
  }

  // ------------ 10 to 20 cm ------------
  else if (distance > 10) {

    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);

    if (currentMillis - previousMillis >= 200) {

      previousMillis = currentMillis;

      toggleState = !toggleState;

      if (toggleState)
        tone(buzzer, 1000);
      else
        noTone(buzzer);
    }
  }

  // ------------ Less than 10 cm ------------
  else {

    tone(buzzer, 1000);

    if (currentMillis - previousMillis >= 100) {

      previousMillis = currentMillis;

      toggleState = !toggleState;

      digitalWrite(redLED, toggleState);
      digitalWrite(yellowLED, toggleState);
      digitalWrite(greenLED, toggleState);
    }
  }
}