#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// Keypad
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS]={
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS]={2,3,4,5};
byte colPins[COLS]={6,7,8,9};

Keypad keypad=Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

const int greenLED=10;
const int redLED=11;
const int buzzer=12;

String password="1234";
String input="";

int attempts=0;

void setup()
{
  lcd.init();
  lcd.backlight();

  pinMode(greenLED,OUTPUT);
  pinMode(redLED,OUTPUT);
  pinMode(buzzer,OUTPUT);

  lcd.setCursor(0,0);
  lcd.print("ENTER PIN:");
}

void loop()
{
  char key=keypad.getKey();

  if(key)
  {
    if(key>='0' && key<='9')
    {
      input+=key;

      lcd.setCursor(input.length()-1,1);
      lcd.print("*");
    }

    if(input.length()==4)
    {
      delay(300);

      lcd.clear();

      if(input==password)
      {
        lcd.print("ACCESS");
        lcd.setCursor(0,1);
        lcd.print("GRANTED");

        digitalWrite(greenLED,HIGH);

        delay(3000);

        digitalWrite(greenLED,LOW);

        attempts=0;
      }
      else
      {
        lcd.print("ACCESS");
        lcd.setCursor(0,1);
        lcd.print("DENIED");

        digitalWrite(redLED,HIGH);

        tone(buzzer,1000);

        delay(2000);

        noTone(buzzer);

        digitalWrite(redLED,LOW);

        attempts++;

        if(attempts>=3)
        {
          lcd.clear();
          lcd.print("SYSTEM LOCK");
          lcd.setCursor(0,1);
          lcd.print("WAIT 10 SEC");

          delay(10000);

          attempts=0;
        }
      }

      input="";

      lcd.clear();
      lcd.print("ENTER PIN:");
    }
  }
}