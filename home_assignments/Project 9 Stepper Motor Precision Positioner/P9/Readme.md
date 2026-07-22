# Project 9 - Stepper Motor Precision Positioner

## Components

- Arduino Uno
- 28BYJ-48 Stepper Motor
- ULN2003 Driver Board
- 10k Potentiometer
- 3 Push Buttons

## Connections

### ULN2003 Driver

- IN1 -> D8
- IN2 -> D9
- IN3 -> D10
- IN4 -> D11
- VCC -> 5V
- GND -> GND

### Potentiometer

- Left -> 5V
- Right -> GND
- Middle -> A0

### Buttons

- CW -> D2
- CCW -> D3
- HOME -> D4

## Libraries

- Stepper (built into Arduino IDE)

## Working

- Potentiometer sets the target angle (0°–360°).
- CW button rotates the motor 45° clockwise.
- CCW button rotates the motor 45° counter-clockwise.
- HOME button resets the current position to 0°.
- Current angle and target angle are displayed on the Serial Monitor.