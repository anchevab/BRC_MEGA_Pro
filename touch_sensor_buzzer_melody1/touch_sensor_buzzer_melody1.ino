/*
  Melody with buzzer
  8-ohm speaker on digital pin 12
*/
#include "pitches.h"                // файл с нотите
#define touch_sensor 23
#define buzzer_pin 12

// ---------- ноти в мелодията в масив
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
// ---------- дължина на нотите -> 4 = четвъртина нота, 8 = осмина нота, и т.н.
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void melody1() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // ------------- изчисляване на нотите -> четвъртина нота = 1000 / 4, осмина нота = 1000/8 , и т.н..
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer_pin, melody[thisNote], noteDuration);
    digitalWrite(buzzer_pin, LOW);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzer_pin);                    // спиране на тоновете
  }
  digitalWrite(buzzer_pin, LOW);        //поставяме пина в LOW,за да спре да свири
}
// ========================== SETUP ===============================
void setup() {
  pinMode(touch_sensor, INPUT);
}

void loop() {
  int sensorState = digitalRead(touch_sensor);
  if (sensorState == 1) {
    melody1();
  }
  delay(5);
}
