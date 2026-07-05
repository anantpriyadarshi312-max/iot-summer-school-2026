/*
====================================================
VENDING MACHINE STATE MACHINE
====================================================

States:
1. IDLE
2. COIN_INSERTED
3. ITEM_SELECTED
4. DISPENSING

State Transition Diagram

              Insert Coin
IDLE -------------------------> COIN_INSERTED
 ^                                 |
 | Cancel                          | Select Item
 |                                 v
 +--------------------------- ITEM_SELECTED
                                   |
                                   | Dispense
                                   v
                              DISPENSING
                                   |
                                   | Finished
                                   v
                                 IDLE

Cancel can return to IDLE from
COIN_INSERTED or ITEM_SELECTED.

====================================================
*/

const int coinButton   = 2;
const int selectButton = 3;
const int cancelButton = 4;

const int redLED    = 8;
const int yellowLED = 9;
const int greenLED  = 10;

enum State {
  IDLE,
  COIN_INSERTED,
  ITEM_SELECTED,
  DISPENSING
};

State currentState = IDLE;

void setup() {

  pinMode(coinButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  pinMode(cancelButton, INPUT_PULLUP);

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  Serial.begin(9600);

  updateLEDs();
  Serial.println("Current State : IDLE");
}

void loop() {

  switch (currentState) {

    case IDLE:

      if (digitalRead(coinButton) == LOW) {
        currentState = COIN_INSERTED;
        Serial.println("Transition: IDLE -> COIN_INSERTED");
        updateLEDs();
        delay(300);
      }

      break;

    case COIN_INSERTED:

      if (digitalRead(selectButton) == LOW) {
        currentState = ITEM_SELECTED;
        Serial.println("Transition: COIN_INSERTED -> ITEM_SELECTED");
        updateLEDs();
        delay(300);
      }

      else if (digitalRead(cancelButton) == LOW) {
        currentState = IDLE;
        Serial.println("Transition: COIN_INSERTED -> IDLE (Cancel)");
        updateLEDs();
        delay(300);
      }

      break;

    case ITEM_SELECTED:

      if (digitalRead(cancelButton) == LOW) {
        currentState = IDLE;
        Serial.println("Transition: ITEM_SELECTED -> IDLE (Cancel)");
        updateLEDs();
        delay(300);
      }

      else {

        delay(1000);

        currentState = DISPENSING;
        Serial.println("Transition: ITEM_SELECTED -> DISPENSING");
        updateLEDs();

        delay(3000);

        currentState = IDLE;
        Serial.println("Transition: DISPENSING -> IDLE");
        updateLEDs();
      }

      break;

    case DISPENSING:
      break;
  }
}

void updateLEDs() {

  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);

  switch (currentState) {

    case IDLE:
      digitalWrite(redLED, HIGH);
      break;

    case COIN_INSERTED:
      digitalWrite(yellowLED, HIGH);
      break;

    case ITEM_SELECTED:
      digitalWrite(greenLED, HIGH);
      break;

    case DISPENSING:
      digitalWrite(redLED, HIGH);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(greenLED, HIGH);
      break;
  }
}