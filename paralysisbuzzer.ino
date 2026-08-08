#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define buzzerPin 8

#define btn1 2
#define btn2 3
#define btn3 4
#define btn4 5
#define btn5 6

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Store previous button states
bool lastBtn1;
bool lastBtn2;
bool lastBtn3;
bool lastBtn4;
bool lastBtn5;

void setup() {
  lcd.init();         
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");

  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
  pinMode(btn5, INPUT_PULLUP);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  delay(500); // Allow system to stabilize
  // Read initial states after delay
  lastBtn1 = digitalRead(btn1);
  lastBtn2 = digitalRead(btn2);
  lastBtn3 = digitalRead(btn3);
  lastBtn4 = digitalRead(btn4);
  lastBtn5 = digitalRead(btn5);
}

void loop() {
  checkButton(btn1, lastBtn1, "I want food");
  checkButton(btn2, lastBtn2, "I want water");
  checkButton(btn3, lastBtn3, "Go for walk");
  checkButton(btn4, lastBtn4, "Call doctor");
  checkButton(btn5, lastBtn5, "Emergency help");
}

void checkButton(int pin, bool &lastState, String msg) {
  bool currentState = digitalRead(pin);

  if (lastState == HIGH && currentState == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(msg);

    digitalWrite(buzzerPin, HIGH);
    delay(2000);
    digitalWrite(buzzerPin, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Message sent");

    delay(2000); // Wait before returning to "System Ready"

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System Ready");
  }

  lastState = currentState;
}
