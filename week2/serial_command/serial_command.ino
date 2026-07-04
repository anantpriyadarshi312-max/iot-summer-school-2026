int blinkCounter = 0;
bool ledState = false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Serial Command Interface Ready");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "LED_ON") {
      digitalWrite(LED_BUILTIN, HIGH);
      ledState = true;
      Serial.println("LED turned ON");
    }

    else if (command == "LED_OFF") {
      digitalWrite(LED_BUILTIN, LOW);
      ledState = false;
      Serial.println("LED turned OFF");
    }

    else if (command.startsWith("BLINK_")) {
      String numStr = command.substring(6);
      int count = numStr.toInt();

      if (count >= 1 && count <= 9) {
        for (int i = 0; i < count; i++) {
          digitalWrite(LED_BUILTIN, HIGH);
          delay(500);
          digitalWrite(LED_BUILTIN, LOW);
          delay(500);
        }
        blinkCounter += count;
        ledState = false;
        Serial.print("Blinked ");
        Serial.print(count);
        Serial.println(" times");
      } else {
        Serial.println("ERROR: Invalid blink count");
      }
    }

    else if (command == "STATUS") {
      Serial.print("LED State: ");
      Serial.println(ledState ? "ON" : "OFF");

      Serial.print("Blink Counter: ");
      Serial.println(blinkCounter);
    }

    else if (command == "RESET") {
      blinkCounter = 0;
      Serial.println("Blink counter reset");
    }

    else {
      Serial.println("ERROR: Unknown command");
    }
  }
}