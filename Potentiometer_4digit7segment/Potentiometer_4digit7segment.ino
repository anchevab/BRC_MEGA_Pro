//  Potentiometer to TM1637TinyDisplay
//  Byala Robots Club
// author: A.Anchev

#include <Arduino.h>
#include <TM1637TinyDisplay.h>

#define CLK 44
#define DIO 46
#define pot_pin A9

TM1637TinyDisplay display(CLK, DIO);

int pot_value;

// =========== SETUP ===========
void setup() {
  display.setBrightness(BRIGHT_7);
  display.showNumber(8888);
  delay(1000);
}

// ========== LOOP ==========
void loop() {
  pot_value = analogRead(pot_pin);
  display.showNumber(pot_value);
  delay(30);
}
