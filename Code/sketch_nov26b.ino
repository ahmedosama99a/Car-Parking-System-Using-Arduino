// Parking System for Arduino with Blue I2C LCD (NewLiquidCrystal Library)

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD I2C address 0x27, 16x2
LiquidCrystal_I2C lcd(0x27,16,2);

Servo myservo;

int IR1 = 2;          // Sensor for car entering
int IR2 = 3;          // Sensor for car leaving
int Slot = 4;         // Total number of parking slots
int flag1 = 0;
int flag2 = 0;

void setup() {
  Wire.begin();       
  lcd.init();          // Initialize LCD
  lcd.backlight();     // Turn backlight ON

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  myservo.attach(4);
  myservo.write(100);  // Servo initial position

  // Initial welcome message
  lcd.setCursor(0,0);
  lcd.print("     ARDUINO    ");
  lcd.setCursor(0,1);
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
        myservo.write(0);   // Open gate
        Slot = Slot - 1;
      }
    } else {
      lcd.setCursor(0,0);
      lcd.print("    SORRY :(    ");
      lcd.setCursor(0,1);
      lcd.print("  Parking Full  ");
      delay(3000);
      lcd.clear();
    }
  }

  // Car leaving
  if (digitalRead(IR2) == LOW && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo.write(0);     // Open gate
      Slot = Slot + 1;
    }
  }

  // Reset servo after both sensors triggered
  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    myservo.write(100);     // Close gate
    flag1 = 0;
    flag2 = 0;
  }

  // Display current status
  lcd.setCursor(0,0);
  lcd.print("WELCOME!       ");   // Overwrite old text
  lcd.setCursor(0,1);
  lcd.print("Slot Left: ");
  lcd.print(Slot);
  lcd.print("   ");              // Clear remaining chars
}
