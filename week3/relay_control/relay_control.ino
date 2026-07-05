#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define RELAY_PIN 8
#define BUTTON_PIN 3

DHT dht(DHTPIN, DHTTYPE);

bool relayState = false;
bool manualOverride = false;

int lastButtonState = HIGH;

void setup()
{
  Serial.begin(9600);

  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(RELAY_PIN, LOW);
}

void loop()
{
  // ---------- Read Button ----------
  int buttonState = digitalRead(BUTTON_PIN);

  if(buttonState == LOW && lastButtonState == HIGH)
  {
    manualOverride = !manualOverride;

    if(manualOverride)
      relayState = !relayState;

    Serial.println("------------------------");

    if(manualOverride)
      Serial.println("Manual Override ENABLED");
    else
      Serial.println("Manual Override DISABLED");

    delay(250);
  }

  lastButtonState = buttonState;

  // ---------- Read Temperature ----------
  float temp = dht.readTemperature();

  if(isnan(temp))
  {
    Serial.println("DHT Error");
    delay(1000);
    return;
  }

  bool previousState = relayState;

  // ---------- Automatic Control ----------
  if(!manualOverride)
  {
    if(temp > 32)
      relayState = true;

    else if(temp < 28)
      relayState = false;
  }

  digitalWrite(RELAY_PIN, relayState);

  // ---------- Log only when state changes ----------
  if(previousState != relayState)
  {
    Serial.println("------------------------");
    Serial.print("Temperature : ");
    Serial.print(temp);
    Serial.println(" C");

    Serial.print("Relay : ");

    if(relayState)
      Serial.println("ON (AC ON)");
    else
      Serial.println("OFF (AC OFF)");
  }

  delay(1000);
}