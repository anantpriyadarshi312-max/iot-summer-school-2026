# \# Project 10 - Full IoT Home Automation Hub

# 

# \## Components

# 

# \- ESP32

# \- DHT11 Temperature \& Humidity Sensor

# \- MQ-2 Gas Sensor

# \- PIR Motion Sensor

# \- LDR + 10kΩ Resistor

# \- 2-Channel Relay Module

# \- SSD1306 OLED Display

# \- Active Buzzer

# \- Red and Green LEDs

# \- Push Buttons

# 

# \## Connections

# 

# \### DHT11

# \- DATA → GPIO4

# \- VCC → 3.3V

# \- GND → GND

# 

# \### MQ-2

# \- AOUT → GPIO35

# \- VCC → 5V

# \- GND → GND

# 

# \### PIR Sensor

# \- OUT → GPIO13

# \- VCC → 5V

# \- GND → GND

# 

# \### LDR

# \- Voltage divider output → GPIO34

# 

# \### Relay Module

# \- IN1 → GPIO26 (Fan)

# \- IN2 → GPIO27 (Light)

# \- VCC → 5V

# \- GND → GND

# 

# \### OLED

# \- SDA → GPIO21

# \- SCL → GPIO22

# \- VCC → 3.3V

# \- GND → GND

# 

# \### Other Components

# \- Buzzer → GPIO14

# \- Red LED → GPIO25

# \- Green LED → GPIO2

# \- Fan override button → GPIO0

# \- Light override button → GPIO32

# 

# \## Libraries

# 

# \- WiFi

# \- DHTesp

# \- Adafruit GFX

# \- Adafruit SSD1306

# \- PubSubClient (if MQTT is used)

# 

# \## Working

# 

# The ESP32 monitors temperature, humidity, gas level, motion, and light intensity.

# 

# \### Fan Automation

# 

# \- Temperature > 32°C → Fan ON

# \- Temperature < 28°C → Fan OFF

# 

# Hysteresis is used to prevent rapid relay switching.

# 

# \### Light Automation

# 

# \- Dark room + motion detected → Light ON

# \- Daylight or no motion for a period → Light OFF

# 

# \### Gas Safety

# 

# \- High gas level → Red LED and buzzer ON

# \- Both relays are turned OFF for safety

# 

# \### OLED Display

# 

# The OLED displays:

# 

# 1\. Temperature and humidity

# 2\. Gas, PIR, and LDR readings

# 3\. Relay states and system uptime

# 

# \### Manual Override

# 

# Push buttons can be used to manually override the fan and light controls.

# 

# \## System Architecture

# 

# Sensors

# ↓

# ESP32

# ↓

# Automation Logic

# ↓

# Relays + LEDs + Buzzer + OLED

# 

# The ESP32 acts as the central controller for the complete home automation system.

