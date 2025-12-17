// Parking System for Arduino with 16x2 LCD (parallel interface)

#include <LiquidCrystal.h>
#include <Servo.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

Servo myservo;

int IR1 = 8;          // Sensor for car entering
int IR2 = 9;          // Sensor for car leaving
int Slot = 4;         // Total number of parking slots
int flag1 = 0;
int flag2 = 0;

void setup() {
  lcd.begin(16, 2);       // Initialize LCD 16x2
  lcd.clear();

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  myservo.attach(10);     // Servo on pin 10 (غيّر التوصيلة في البروتيوس)
  myservo.write(100);     // Servo initial position

  // Initial welcome message
  lcd.setCursor(0, 0);
  lcd.print("     ARDUINO    ");
  lcd.setCursor(0, 1);
  lcd.print(" PARKING SYSTEM ");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Car entering
  if (digitalRead(IR1) == LOW && flag1 == 0) {
    if (Slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo.write(0);     // Open gate
        Slot = Slot - 1;
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print("    SORRY :(    ");
      lcd.setCursor(0, 1);
      lcd.print("  Parking Full  ");
      delay(3000);
      lcd.clear();
    }
  }

  // Car leaving
  if (digitalRead(IR2) == LOW && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo.write(0);       // Open gate
      Slot = Slot + 1;
    }
  }

  // Reset servo after both sensors triggered
  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    myservo.write(100);       // Close gate
    flag1 = 0;
    flag2 = 0;
  }

  // Display current status
  lcd.setCursor(0, 0);
  lcd.print("WELCOME!       ");
  lcd.setCursor(0, 1);
  lcd.print("Slot Left: ");
  lcd.print(Slot);
  lcd.print("   ");
}
