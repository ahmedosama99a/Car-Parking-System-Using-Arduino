# 🚗 Car Parking System Using Arduino

This project is a smart **Car Parking System** built using **Arduino UNO**, IR sensors, an LCD display, and a servo motor.  
The system automatically counts cars entering and exiting the parking area and displays the number of available slots on the LCD screen.  
It also opens and closes the gate using a servo motor.

---

## 📌 Project Overview
The system uses two IR sensors:
- **Entrance sensor:** detects cars entering the parking.
- **Exit sensor:** detects cars leaving the parking.

Each time a car enters, the system increments the counter.  
Each time a car exits, the counter decrements.  
The LCD shows:
- Number of cars inside.
- Number of free slots.

A servo motor acts as the main gate and automatically opens and closes when a car passes.

---

## 🧰 Components Used
- Arduino UNO  
- IR Sensor Module × 2  
- SG90 Servo Motor  
- LCD 16x2 with I2C module  
- Breadboard  
- Jumper wires  

---

## 🔌 Circuit Description
- IR Entrance Sensor → Arduino digital pin **2**  
- IR Exit Sensor → Arduino digital pin **3**  
- Servo Motor → Arduino digital pin **9**  
- LCD I2C SDA → Arduino **A4**  
- LCD I2C SCL → Arduino **A5**  
- All modules share **5V** and **GND**  

---

## ▶️ How the System Works
1. Power the Arduino and start the system.  
2. When a car passes the entrance IR sensor → counter increases, gate opens, then closes.  
3. When a car passes the exit IR sensor → counter decreases, gate opens, then closes.  
4. The LCD continuously displays the number of cars inside and available spaces.  
5. If the parking is full, the system will not allow additional cars to enter.

---

## 🧾 Arduino Code
The complete Arduino code for the system is included in the repository inside the code file:
`car_parking_system.ino`

---

## 📸 Images & Videos

### Wiring Diagram / Simulation
![Proteus Simulation](Image%20%26%20Video/Screenshot%202025-12-10%20172003.png)

### Real Prototype
![Real Prototype](Image%20%26%20Video/WhatsApp%20Image%202025-12-17%20at%2013.56.30_d17bfb91.jpg)

### Hardware in Action
[Watch Video](Image%20%26%20Video/WhatsApp%20Video%202025-12-17%20at%2013.56.43_016b80e4.mp4)


---

## 🙌 Author
Ahmed Osama Salah


