/*
  Blink without Delay with button
*/
#define button_pin 26
#define GREEN_LED 30

const int ledPin =  28;
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 2000;                 // --- interval at which to blink (milliseconds)
unsigned long currentMillis = 0;

// =========== SETUP ===========
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

// =========== LOOP ===========
void loop() {
  int button_state = digitalRead(button_pin);
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
  if (button_state == 1) {
    digitalWrite(GREEN_LED, HIGH);
  } else {
    digitalWrite(GREEN_LED, LOW);
  }
}
