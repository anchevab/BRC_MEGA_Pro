/*
  BRC MEGA 2560 shield Button
  Byala Robots Club
*/

const int buttonPin = 26;     // the number of the pushbutton pin
const int ledPin =  28;      // the number of the LED pin

int buttonState = 0;         // variable for reading the pushbutton status

// ============ SETUP ==========
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

// ============ LOOP ==========
void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ON");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("LED OFF");
  }
}
