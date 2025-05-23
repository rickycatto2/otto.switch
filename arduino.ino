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