#include <Servo.h>

Servo myServo;

const int servoPin = 9;
const int potPin = A0;
const int buttonPin = 2;

int potValue;
int angle;

void setup()
{
  Serial.begin(9600);

  myServo.attach(servoPin);

  pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
  // If button is pressed
  if (digitalRead(buttonPin) == LOW)
  {
    // Sweep from 0 to 180
    for(int pos = 0; pos <= 180; pos++)
    {
      myServo.write(pos);
      Serial.print("Sweep Angle: ");
      Serial.println(pos);
      delay(15);
    }

    // Sweep back from 180 to 0
    for(int pos = 180; pos >= 0; pos--)
    {
      myServo.write(pos);
      Serial.print("Sweep Angle: ");
      Serial.println(pos);
      delay(15);
    }

    delay(300);
  }

  // Manual control using potentiometer
  else
  {
    potValue = analogRead(potPin);

    angle = map(potValue,0,1023,0,180);

    myServo.write(angle);

    Serial.print("Pot Value: ");
    Serial.print(potValue);

    Serial.print("    Servo Angle: ");
    Serial.println(angle);

    delay(100);
  }
}