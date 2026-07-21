#include <DHTesp.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// -------------------- Pin Definitions --------------------
#define DHT_PIN 4
#define RED_LED 25
#define GREEN_LED 26
#define BUZZER 27

// -------------------- OLED Configuration --------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHTesp dht;

// -------------------- Timing --------------------
unsigned long lastSensorRead = 0;
unsigned long lastCSVLog = 0;
unsigned long buzzerStartTime = 0;

const unsigned long sensorInterval = 2000;
const unsigned long csvInterval = 5000;
const unsigned long buzzerDuration = 1000;

bool buzzerActive = false;

// -------------------- Variables --------------------
float temperature;
float humidity;
String status;

void setup() {
  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BUZZER, LOW);

  // Initialize DHT11
  dht.setup(DHT_PIN, DHTesp::DHT11);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("OLED initialization failed!");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("Climate Monitor");

  display.setCursor(0, 20);
  display.println("Starting...");

  display.display();

  delay(2000);

  Serial.println("millis,temp,humidity,status");
}

void loop() {
  unsigned long currentTime = millis();

  // Read sensor every 2 seconds
  if (currentTime - lastSensorRead >= sensorInterval) {
    lastSensorRead = currentTime;

    TempAndHumidity data = dht.getTempAndHumidity();

    temperature = data.temperature;
    humidity = data.humidity;

    // Check if sensor reading is valid
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT11");
      return;
    }

    // Determine comfort status
    if (temperature > 38 || humidity > 80) {
      status = "DANGER";
    }
    else if (temperature >= 32 || humidity >= 70) {
      status = "HOT";
    }
    else if (temperature >= 20 && humidity >= 40) {
      status = "COMFORT";
    }
    else {
      status = "COOL";
    }

    // Serial raw values
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" C, Humidity: ");
    Serial.print(humidity);
    Serial.print(" %, Status: ");
    Serial.println(status);

    // Update OLED
    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0, 0);
    display.print("Temp: ");
    display.print(temperature, 1);
    display.println(" C");

    display.setCursor(0, 16);
    display.print("Hum:  ");
    display.print(humidity, 0);
    display.println(" %");

    display.setCursor(0, 34);
    display.print("Status: ");

    display.setTextSize(2);
    display.setCursor(0, 47);
    display.println(status);

    display.display();

    // Threshold alert
    if (temperature > 38 || humidity > 80) {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);

      // Start buzzer for 1 second
      if (!buzzerActive) {
        digitalWrite(BUZZER, HIGH);
        buzzerStartTime = currentTime;
        buzzerActive = true;
      }
    }
    else {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
    }
  }

  // Turn buzzer off after 1 second
  if (buzzerActive && currentTime - buzzerStartTime >= buzzerDuration) {
    digitalWrite(BUZZER, LOW);
    buzzerActive = false;
  }

  // CSV logging every 5 seconds
  if (currentTime - lastCSVLog >= csvInterval) {
    lastCSVLog = currentTime;

    Serial.print(currentTime);
    Serial.print(",");
    Serial.print(temperature, 1);
    Serial.print(",");
    Serial.print(humidity, 1);
    Serial.print(",");
    Serial.println(status);
  }
}