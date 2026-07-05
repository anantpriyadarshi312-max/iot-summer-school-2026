/*
Smart Street Light
LDR + PIR Sensor
*/

const int ldrPin = A0;
const int pirPin = 2;
const int ledPin = 9;

const int LDR_THRESHOLD = 500;

unsigned long motionTime = 0;
bool motionDetected = false;

void printTime()
{
  unsigned long seconds = millis() / 1000;

  int hh = seconds / 3600;
  int mm = (seconds % 3600) / 60;
  int ss = seconds % 60;

  if(hh < 10) Serial.print("0");
  Serial.print(hh);
  Serial.print(":");

  if(mm < 10) Serial.print("0");
  Serial.print(mm);
  Serial.print(":");

  if(ss < 10) Serial.print("0");
  Serial.print(ss);
}

void logEvent(String msg)
{
  Serial.print("[");
  printTime();
  Serial.print("] EVENT: ");
  Serial.println(msg);
}

void setup()
{
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);

  logEvent("System Started");
}

void loop()
{
  int ldrValue = analogRead(ldrPin);

  // DAY
  if(ldrValue > LDR_THRESHOLD)
  {
    analogWrite(ledPin,0);

    motionDetected = false;

    logEvent("Daylight - LED OFF");

    delay(1000);

    return;
  }

  // NIGHT

  if(digitalRead(pirPin) == HIGH)
  {
    analogWrite(ledPin,255);

    motionDetected = true;

    motionTime = millis();

    logEvent("Motion Detected - LED FULL BRIGHTNESS");
  }

  if(motionDetected)
  {
    if(millis() - motionTime >= 30000)
    {
      analogWrite(ledPin,51);

      motionDetected = false;

      logEvent("No Motion - LED DIM (20%)");
    }
  }
  else
  {
    analogWrite(ledPin,51);
  }

}