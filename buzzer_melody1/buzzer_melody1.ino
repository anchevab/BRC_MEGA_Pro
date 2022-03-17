/*
  Melody with buzzer
  8-ohm speaker on digital pin 8
*/
#include "pitches.h"                // файл с нотите

// ---------- ноти в мелодията в масив
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
// ---------- дължина на нотите -> 4 = четвъртина нота, 8 = осмина нота, и т.н.
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

// ========================== SETUP ===============================
void setup() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // ------------- изчисляване на нотите -> четвъртина нота = 1000 / 4, осмина нота = 1000/8 , и т.н..
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(12, melody[thisNote], noteDuration);
    digitalWrite(12, LOW);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(12);                    // спиране на тоновете
  }
  digitalWrite(12, LOW);        //поставяме пина в HIGH,за да спре да свири
}

void loop() {

}
