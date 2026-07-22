#define TRIG 9
#define ECHO 10

#define GREEN 2
#define YELLOW 3
#define RED 4

#define BUZZER 6

long duration;
float distance;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);

  pinMode(BUZZER, OUTPUT);
}

void loop() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // SAFE
  if (distance > 60) {
    digitalWrite(GREEN, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, LOW);
    noTone(BUZZER);
  }

  // CAUTION
  else if (distance > 30) {
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(RED, LOW);

    tone(BUZZER, 1000);
    delay(100);
    noTone(BUZZER);
    delay(700);
  }

  // CLOSE
  else if (distance > 15) {
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(RED, HIGH);

    tone(BUZZER, 1000);
    delay(100);
    noTone(BUZZER);
    delay(200);
  }

  // DANGER
  else {
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, HIGH);

    tone(BUZZER, 1000);
  }

  delay(100);
}