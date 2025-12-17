#include <LiquidCrystal.h>
#include <Servo.h>

// LCD Pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Test Inputs
int IR1 = 8;   // Test pin for entrance
int IR2 = 9;   // Test pin for exit

// Servo
Servo gate;
int OPEN_POS = 90;
int CLOSE_POS = 0;

// Parking Logic
int currentCars = 0;
int maxCars = 4;

// Flags to prevent duplicate triggers
bool gateOpen = false;
bool carEntering = false;
bool carExiting = false;

// To ensure single press trigger
bool pressedIR1 = false;
bool pressedIR2 = false;

void setup() {
  pinMode(IR1, INPUT_PULLUP);  // Controlled manually by toggle
  pinMode(IR2, INPUT_PULLUP);

  gate.attach(10);
  gate.write(CLOSE_POS);

  lcd.begin(16, 2);
  lcd.print("Parking Ready");
  delay(1200);
  lcd.clear();
}

void loop() {
  int r1 = digitalRead(IR1);
  int r2 = digitalRead(IR2);

  // ================= MANUAL ENTRANCE TRIGGER ================
  if (r1 == LOW && !pressedIR1 && currentCars < maxCars) {
    pressedIR1 = true; // avoid repeated triggering
    if (!gateOpen) {
      gate.write(OPEN_POS);
      gateOpen = true;
      carEntering = true;
      lcdMsg("Gate Open", "Car Entering");
    }
  }
  if (r1 == HIGH && pressedIR1) pressedIR1 = false; // reset trigger

  // ================= COMPLETE ENTRANCE STEP =================
  if (r2 == LOW && carEntering && !pressedIR2) {
    pressedIR2 = true;
    gate.write(CLOSE_POS);
    gateOpen = false;
    carEntering = false;
    currentCars++;
    showParkingSpaces();
  }
  if (r2 == HIGH && pressedIR2) pressedIR2 = false;

  // ================= MANUAL EXIT TRIGGER ====================
  if (r2 == LOW && !pressedIR2 && currentCars > 0) {
    pressedIR2 = true;
    if (!gateOpen) {
      gate.write(OPEN_POS);
      gateOpen = true;
      carExiting = true;
      lcdMsg("Gate Open", "Car Exiting");
    }
  }
  if (r2 == HIGH && pressedIR2 && !carEntering) pressedIR2 = false;

  // ================= COMPLETE EXIT STEP =====================
  if (r1 == LOW && carExiting && !pressedIR1) {
    pressedIR1 = true;
    gate.write(CLOSE_POS);
    gateOpen  = false;
    carExiting = false;
    currentCars--;
    showParkingSpaces();
  }

  // ============== FULL PARKING MESSAGE ======================
  if (currentCars >= maxCars) {
    lcd.clear();
    lcd.print("Parking Full!");
    lcd.setCursor(0,1);
    lcd.print("No Spaces Left");
    delay(400);
  }
}

// ===== Display Functions =====
void showParkingSpaces() {
  lcd.clear();
  lcd.print("Cars: ");
  lcd.print(currentCars);
  lcd.setCursor(0,1);
  lcd.print("Free: ");
  lcd.print(maxCars - currentCars);
  delay(800);
}

void lcdMsg(String l1, String l2) {
  lcd.clear();
  lcd.print(l1);
  lcd.setCursor(0,1);
  lcd.print(l2);
  delay(700);
}
