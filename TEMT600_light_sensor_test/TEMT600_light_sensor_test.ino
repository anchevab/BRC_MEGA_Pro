/*
  BRC MEGA 2560 shield TEMT600 light sensor serial
  Byala Robots Club
  author: A.Anchev
*/

#define lightsensor_pin A11

// =============== SETUP =============
void setup() {
  Serial.begin(9600);
}

// ============== LOOP ==============
void loop() {
  int sensorValue = analogRead(lightsensor_pin);
  Serial.println(sensorValue);
  delay(7);
}
