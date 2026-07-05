#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define LDR A0

#define TRIG 9
#define ECHO 10

DHT dht(DHTPIN,DHTTYPE);

void setup()
{
  Serial.begin(9600);

  dht.begin();

  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);
}

void loop()
{
  float temp=dht.readTemperature();
  float hum=dht.readHumidity();

  int lightRaw=analogRead(LDR);

  int lightPercent=map(lightRaw,0,1023,0,100);

  String status;

  if(lightPercent>70)
      status="Bright";

  else if(lightPercent>40)
      status="Dim";

  else
      status="Dark";

  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG,LOW);

  long duration=pulseIn(ECHO,HIGH);

  float distance=(duration*0.034)/2;

  Serial.println("=== SENSOR LOG ===");

  Serial.print("Time      : ");
  Serial.print(millis());
  Serial.println(" ms");

  Serial.print("Temp      : ");
  Serial.print(temp);
  Serial.print(" C | Humidity: ");
  Serial.print(hum);
  Serial.println("%");

  Serial.print("Light     : ");
  Serial.print(lightPercent);
  Serial.print("% (");
  Serial.print(status);
  Serial.println(")");

  Serial.print("Distance  : ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.println("==================");

  delay(5000);
}