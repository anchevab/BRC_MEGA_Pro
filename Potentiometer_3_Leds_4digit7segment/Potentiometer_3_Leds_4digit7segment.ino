//  Potentiometer to TM1637TinyDisplay
//  Byala Robots Club
// author: A.Anchev

#include <Arduino.h>
#include <TM1637TinyDisplay.h>

#define CLK 44
#define DIO 46
#define pot_pin A9
#define RED 28
#define GREEN 30
#define BLUE 33

TM1637TinyDisplay display(CLK, DIO);

int pot_value;

// =========== SETUP ===========
void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  display.setBrightness(BRIGHT_7);
  display.showNumber(8888);
  delay(1000);
}

// ========== LOOP ==========
void loop() {
  pot_value = analogRead(pot_pin);
  display.showNumber(pot_value);
  if (pot_value <= 400) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
  } else if (pot_value > 400 and pot_value <= 800) {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
  } else {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, HIGH);
  }
  delay(30);
}
