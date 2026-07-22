#define PIR 13
#define RED_LED 2
#define BUZZER 14

bool motion = false;

void setup() {
  Serial.begin(115200);

  pinMode(PIR, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  Serial.println("Motion Security System");
}

void loop() {

  motion = digitalRead(PIR);

  if (motion) {

    Serial.println("Motion Detected!");

    digitalWrite(RED_LED, HIGH);

    tone(BUZZER, 1000);
    delay(500);
    noTone(BUZZER);

  } else {

    Serial.println("No Motion");

    digitalWrite(RED_LED, LOW);
    noTone(BUZZER);
  }

  delay(500);
}