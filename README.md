Arduino Uno Relay Trigger with Standard Light Switch
This sketch uses a standard Decora-style SPST wall switch to act like a momentary input for triggering an SRD-5VDC-SL-C relay module connected to an Arduino Uno. Each time the switch is flipped (either from ON to OFF or OFF to ON), the relay closes for 1 second, then opens again.

Useful for triggering garage door openers, electric strikes, or any input expecting a momentary contact—using only a simple wall switch.

Parts List
Arduino Uno

SRD-5VDC-SL-C Relay Module (3-pin version: S, +, –)

Decora-style SPST wall switch

Jumper wires

Breadboard or screw terminals

USB cable for power and programming

 How It Works
The wall switch connects between digital pin 3 and GND

The code watches for any change in switch state

When a change is detected:

The Arduino drives the relay pin HIGH (activating the relay)

Waits 1 second (1000 ms)

Drives the relay pin LOW (deactivating the relay)

The result: a consistent 1-second relay pulse on each switch flip

Wiring Diagram
Switch ↔ Arduino
Switch Terminal	Arduino Pin
One side	GND
Other side	D3

Internal pull-up resistor on D2 handles the default HIGH state

Relay Module ↔ Arduino
Relay Pin	Arduino Pin
+	5V
–	GND
S	D10

This assumes the relay is active-low: High turns it on, LOW turns it off
