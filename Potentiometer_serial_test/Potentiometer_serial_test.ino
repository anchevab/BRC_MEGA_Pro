/*
  BRC MEGA 2560 shield potentiometer to serial
  Byala Robots Club
  author: A.Anchev
*/

#define pot_pin A9

// =============== SETUP =============
void setup() {
  Serial.begin(9600);
}

// ============== LOOP ==============
void loop() {
  int sensorValue = analogRead(pot_pin);
  Serial.println(sensorValue);
  delay(7);
}
