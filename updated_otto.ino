// Pin setup
const int pinPaddle = 2;     // D2
const int pinSwitch = 3;     // D3
const int pinSonoff = 4;     // D4

const int relayD10 = 10;     // Relay A (always first)
const int relayD11 = 11;     // Relay B (switch-only)
const int relayD12 = 12;     // Relay C (after delay)

// Adjustable timing
unsigned long relay_first = 800;  // delay between relays
unsigned long duration = 0;       // global variable for full relay cycle

// Internal state tracking
bool lastPaddleState = HIGH;
bool lastSwitchState = HIGH;
bool lastSonoffState = HIGH;

// Sequence control
unsigned long triggerStartTime = 0;
bool relaySequenceActive = false;
int relaySequenceType = 0;  // 1 = paddle, 2 = sonoff

void setup() {
  pinMode(pinPaddle, INPUT_PULLUP);
  pinMode(pinSwitch, INPUT_PULLUP);
  pinMode(pinSonoff, INPUT_PULLUP);

  pinMode(relayD10, OUTPUT);
  pinMode(relayD11, OUTPUT);
  pinMode(relayD12, OUTPUT);

  digitalWrite(relayD10, HIGH);
  digitalWrite(relayD11, HIGH);
  digitalWrite(relayD12, HIGH);
}

void loop() {
  unsigned long now = millis();

  // --- Input D2: Paddle switch (any change) ---
  bool currentPaddle = digitalRead(pinPaddle);
  if (currentPaddle != lastPaddleState) {
    startRelaySequence(1);  // paddle
    lastPaddleState = currentPaddle;
  }

  // --- Input D4: Sonoff — only falling edge (HIGH -> LOW) ---
  bool currentSonoff = digitalRead(pinSonoff);
  if (lastSonoffState == HIGH && currentSonoff == LOW) {
    startRelaySequence(2);  // sonoff
  }
  lastSonoffState = currentSonoff;

  // --- Input D3: Switch press/release ---
  bool currentSwitch = digitalRead(pinSwitch);
  if (currentSwitch != lastSwitchState) {
    delay(10);  // crude debounce
    if (digitalRead(pinSwitch) == currentSwitch) {
      if (currentSwitch == LOW) {
        // Pressed
        digitalWrite(relayD10, LOW);
        delay(relay_first);
        digitalWrite(relayD11, LOW);
      } else {
        // Released
        digitalWrite(relayD10, HIGH);
        digitalWrite(relayD11, HIGH);
      }
    }
    lastSwitchState = currentSwitch;
  }

  // --- Handle delayed relay logic (D10 then D12) ---
  if (relaySequenceActive) {
    unsigned long elapsed = now - triggerStartTime;

    if (elapsed >= relay_first && digitalRead(relayD12) == HIGH) {
      digitalWrite(relayD12, LOW);  // ON
    }

    if (elapsed >= duration) {
      digitalWrite(relayD10, HIGH);  // OFF
      digitalWrite(relayD12, HIGH);  // OFF
      relaySequenceActive = false;
    }
  }
}

void startRelaySequence(int type) {
  relaySequenceActive = true;
  relaySequenceType = type;
  triggerStartTime = millis();
  digitalWrite(relayD10, LOW); // Relay A ON first

  if (type == 1) {
    duration = 3000;  // paddle
  } else if (type == 2) {
    duration = 2000;  // sonoff
  }
}
