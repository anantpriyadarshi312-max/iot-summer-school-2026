# Project 1: Smart Room Climate Monitor

## ⭐ Project Overview

The Smart Room Climate Monitor is an ESP32-based IoT project that continuously monitors room temperature and humidity using a DHT11 sensor.

The readings are displayed on a 0.96-inch SSD1306 OLED display. If the temperature becomes too high or the humidity exceeds the defined limit, the system activates a red LED and buzzer as an alert. Under normal conditions, the green LED remains ON.

---

## 🎯 Problem Statement

During summer, a hostel room can become uncomfortable due to high temperature and humidity.

This project provides a simple climate monitoring system that:

* Measures temperature and humidity
* Displays live readings on an OLED
* Shows a comfort status
* Alerts the user when conditions become dangerous
* Logs sensor readings in CSV format through the Serial Monitor

---

## 🔧 Components Used

* ESP32 Development Board
* DHT11 Temperature and Humidity Sensor
* 0.96-inch SSD1306 OLED Display
* Active Buzzer
* Red LED
* Green LED
* 2 × 220Ω Resistors
* 10kΩ Pull-up Resistor
* Breadboard
* Jumper Wires
* USB Cable

---

## 🔌 Wiring Connections

### DHT11 Sensor

| DHT11 Pin | ESP32  |
| --------- | ------ |
| VCC       | 3.3V   |
| GND       | GND    |
| DATA      | GPIO 4 |

A **10kΩ pull-up resistor** is connected between the DHT11 DATA pin and 3.3V.

---

### SSD1306 OLED Display

| OLED Pin | ESP32   |
| -------- | ------- |
| VCC      | 3.3V    |
| GND      | GND     |
| SDA      | GPIO 21 |
| SCL      | GPIO 22 |

OLED I2C Address:

```text
0x3C
```

---

### Red LED

```text
ESP32 GPIO25 → 220Ω Resistor → Red LED Anode
Red LED Cathode → GND
```

---

### Green LED

```text
ESP32 GPIO26 → 220Ω Resistor → Green LED Anode
Green LED Cathode → GND
```

---

### Active Buzzer

```text
Buzzer (+) → ESP32 GPIO27
Buzzer (–) → GND
```

---

## 📚 Libraries Used

The following libraries are required:

### 1. DHTesp

Used to read temperature and humidity from the DHT11 sensor.

```cpp
#include <DHTesp.h>
```

### 2. Adafruit SSD1306

Used to control the OLED display.

```cpp
#include <Adafruit_SSD1306.h>
```

### 3. Adafruit GFX Library

Required by the Adafruit SSD1306 library for graphics and text display.

```cpp
#include <Adafruit_GFX.h>
```

### 4. Wire Library

Used for I2C communication with the OLED display.

```cpp
#include <Wire.h>
```

---

## 📊 Comfort Index Logic

The system determines the room status based on temperature and humidity.

| Condition                                    | Status  |
| -------------------------------------------- | ------- |
| Temperature below 20°C or humidity below 40% | COOL    |
| Temperature 20–31°C and humidity 40–69%      | COMFORT |
| Temperature ≥ 32°C or humidity ≥ 70%         | HOT     |
| Temperature > 38°C or humidity > 80%         | DANGER  |

The **DANGER** condition has the highest priority.

---

## 🚨 Alert Logic

The system activates the alert when:

```text
Temperature > 38°C
OR
Humidity > 80%
```

During the alert:

* 🔴 Red LED → ON
* 🟢 Green LED → OFF
* 🔊 Buzzer → ON for 1 second

During normal conditions:

* 🔴 Red LED → OFF
* 🟢 Green LED → ON
* 🔊 Buzzer → OFF

---

## 🖥️ OLED Display

The OLED displays:

```text
Temp: 28.3 C
Hum:  65 %

Status:
COMFORT
```

The sensor is read every **2 seconds**.

---

## 📈 Serial Monitor CSV Logging

The system logs readings every **5 seconds** in the following format:

```text
millis,temp,humidity,status
```

Example:

```text
5000,28.3,65.0,COMFORT
10000,28.5,64.0,COMFORT
15000,29.1,66.0,COMFORT
20000,39.2,82.0,DANGER
25000,39.0,81.0,DANGER
```

---

## ⚙️ Working Principle

1. The ESP32 reads temperature and humidity from the DHT11 sensor.
2. The readings are updated every 2 seconds.
3. The current values are displayed on the OLED.
4. The comfort status is calculated.
5. If the temperature or humidity crosses the danger threshold:

   * The red LED turns ON.
   * The green LED turns OFF.
   * The buzzer sounds for 1 second.
6. Otherwise, the green LED remains ON.
7. Sensor readings are logged in CSV format every 5 seconds through the Serial Monitor.

---

## 📁 Project Files

```text
p1-climate-monitor/
│
├── p1-climate-monitor.ino
├── README.md
└── serial-output.png
```

---

## 📸 Serial Monitor Screenshot

A screenshot showing at least five CSV output rows is included with the project.

Example:

```text
5000,28.3,65.0,COMFORT
10000,28.5,64.0,COMFORT
15000,29.1,66.0,COMFORT
20000,39.2,82.0,DANGER
25000,39.0,81.0,DANGER
```

---

## 🎥 Demo Video

The demo video demonstrates:

* Live temperature and humidity readings on the OLED
* Green LED during comfortable conditions
* Red LED and buzzer activation during high temperature/humidity conditions
* Alert response when the sensor readings cross the threshold

**Demo Video Link:**
*Add your Google Drive or YouTube link here.*

---

## ✅ Conclusion

The Smart Room Climate Monitor successfully monitors temperature and humidity using an ESP32 and DHT11 sensor. It provides real-time visual feedback through an OLED display and alerts the user through an LED and buzzer when the room conditions become excessively hot or humid. The project demonstrates sensor interfacing, I2C communication, OLED display control, threshold-based decision-making, and serial data logging.
