const int redLED = 2;
const int yellowLED = 3;
const int greenLED = 4;
const int buttonPin = 7;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
}

void setLight(bool red, bool yellow, bool green, String state) {
  digitalWrite(redLED, red);
  digitalWrite(yellowLED, yellow);
  digitalWrite(greenLED, green);

  Serial.print("Time: ");
  Serial.print(millis());
  Serial.print(" ms | State: ");
  Serial.println(state);
}

void loop() {

  // Check pedestrian button
  if (digitalRead(buttonPin) == LOW) {
    setLight(HIGH, LOW, LOW, "PEDESTRIAN - RED");
    delay(8000);
    return;
  }

  // RED ON for 5 sec
  setLight(HIGH, LOW, LOW, "RED");
  for (int i = 0; i < 50; i++) {
    if (digitalRead(buttonPin) == LOW) {
      setLight(HIGH, LOW, LOW, "PEDESTRIAN - RED");
      delay(8000);
      return;
    }
    delay(100);
  }

  // YELLOW ON for 2 sec
  setLight(LOW, HIGH, LOW, "YELLOW");
  for (int i = 0; i < 20; i++) {
    if (digitalRead(buttonPin) == LOW) {
      setLight(HIGH, LOW, LOW, "PEDESTRIAN - RED");
      delay(8000);
      return;
    }
    delay(100);
  }

  // GREEN ON for 4 sec
  setLight(LOW, LOW, HIGH, "GREEN");
  for (int i = 0; i < 40; i++) {
    if (digitalRead(buttonPin) == LOW) {
      setLight(HIGH, LOW, LOW, "PEDESTRIAN - RED");
      delay(8000);
      return;
    }
    delay(100);
  }
}