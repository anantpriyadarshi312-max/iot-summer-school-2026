\# LED Blink Project



\## Project Title

LED Blink using Arduino UNO



\## Hardware Required

\- Arduino UNO

\- USB Cable

\- LED

\- 220Ω Resistor

\- Breadboard

\- Jumper Wires

\- Potentiometer (for variable blink speed)



\## Circuit Diagram Description

1\. Connect LED positive terminal (anode) to Arduino pin 13 through a 220Ω resistor.

2\. Connect LED negative terminal (cathode) to GND.

3\. Connect potentiometer:

&#x20;  - Left pin → 5V

&#x20;  - Right pin → GND

&#x20;  - Middle pin → A0



\## How to Upload Code

1\. Connect Arduino UNO to PC using USB cable.

2\. Open Arduino IDE.

3\. Open the file `led\_blink.ino`.

4\. Select board: Arduino UNO.

5\. Select correct COM port.

6\. Click Verify to compile code.

7\. Click Upload to transfer code to Arduino.



\## Expected Output

\- LED blinks continuously.

\- Blink speed changes based on potentiometer position.

\- Serial Monitor displays blink count.



Example:

Blink count: 1

Blink count: 2

Blink count: 3



\## Troubleshooting Tips

1\. Check if correct COM port is selected in Arduino IDE.

2\. Ensure LED polarity is correct (anode/cathode).

3\. Verify all wiring connections properly.

4\. Make sure Arduino board is powered through USB.

5\. Check if potentiometer is connected to A0 correctly.

