#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define RED_LED 8
#define GREEN_LED 9

DHT dht(DHTPIN, DHTTYPE);

void setup() {

  Serial.begin(9600);

  dht.begin();

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // CSV Header
  Serial.println("timestamp,temp_C,temp_F,humidity");
}

void loop() {

  float tempC = dht.readTemperature();
  float humidity = dht.readHumidity();
  float tempF = dht.readTemperature(true);

  if (isnan(tempC) || isnan(tempF) || isnan(humidity)) {
    Serial.println("Sensor Read Error");
    delay(2000);
    return;
  }

  // Print CSV format
  Serial.print(millis());
  Serial.print(",");

  Serial.print(tempC);
  Serial.print(",");

  Serial.print(tempF);
  Serial.print(",");

  Serial.println(humidity);

  // LED Status
  if (tempC > 35 || humidity > 80) {

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

  } else {

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

  }

  delay(2000);
}