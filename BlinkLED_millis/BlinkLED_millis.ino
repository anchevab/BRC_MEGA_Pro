/*
  Blink without Delay
*/

const int ledPin =  28;
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 2000;                 // --- interval at which to blink (milliseconds)
unsigned long currentMillis = 0;

// =========== SETUP ===========
void setup() {
  pinMode(ledPin, OUTPUT);
}

// =========== LOOP ===========
void loop() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
  }
}
