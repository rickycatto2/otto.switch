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
![2025-05-21 12_48_37-Photo - Google Photos](https://github.com/user-attachments/assets/84c00394-0e55-435e-b75d-827f1b41d3b0)

![otto switch](https://github.com/user-attachments/assets/6e34ff90-c178-4c73-ac22-abe1afbb6105)

```
const int switchPin = 3;
const int relayPin = 10;
bool lastSwitchState = LOW;

void setup() {
  pinMode(switchPin, INPUT_PULLUP);  // Pull-up resistor, so open = HIGH
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);  // Relay OFF (active-low logic)
}

void loop() {
  bool currentSwitchState = digitalRead(switchPin);

  // Detect any change in switch position (on → off or off → on)
  if (currentSwitchState != lastSwitchState) {
    delay(10);  // crude debounce
    if (digitalRead(switchPin) == currentSwitchState) {
      // Pulse the relay ON (active-low)
      digitalWrite(relayPin, HIGH);   // Relay ON
      delay(1000);                   // Wait 1000 ms
      digitalWrite(relayPin, LOW);  // Relay OFF

      lastSwitchState = currentSwitchState;
    }
  }
}
```


