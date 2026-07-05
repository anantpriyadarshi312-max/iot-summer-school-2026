const int ENA = 9;
const int IN1 = 8;
const int IN2 = 7;

const int potPin = A0;
const int dirButton = 2;
const int runButton = 3;

bool direction = true;     // true = Forward
bool motorRunning = true;

int lastDirState = HIGH;
int lastRunState = HIGH;

void setup()
{
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(dirButton, INPUT_PULLUP);
  pinMode(runButton, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop()
{
  // ---------- Direction Button ----------
  int dirState = digitalRead(dirButton);

  if (dirState == LOW && lastDirState == HIGH)
  {
    direction = !direction;
    delay(200);    // Debounce
  }

  lastDirState = dirState;

  // ---------- Start/Stop Button ----------
  int runState = digitalRead(runButton);

  if (runState == LOW && lastRunState == HIGH)
  {
    motorRunning = !motorRunning;
    delay(200);    // Debounce
  }

  lastRunState = runState;

  // ---------- Read Potentiometer ----------
  int potValue = analogRead(potPin);

  int speedPWM = map(potValue, 0, 1023, 0, 255);

  int speedPercent = map(speedPWM, 0, 255, 0, 100);

  // ---------- Motor Control ----------
  if (motorRunning)
  {
    analogWrite(ENA, speedPWM);

    if (direction)
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
    else
    {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
  }
  else
  {
    analogWrite(ENA, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }

  // ---------- Serial Monitor ----------
  Serial.print("Direction : ");

  if (direction)
    Serial.print("Forward");
  else
    Serial.print("Reverse");

  Serial.print(" | Speed : ");
  Serial.print(speedPercent);
  Serial.print("%");

  Serial.print(" | State : ");

  if (motorRunning)
    Serial.println("Running");
  else
    Serial.println("Stopped");

  delay(200);
}