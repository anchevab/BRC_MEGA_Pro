/*
  BRC MEGA 2560 shield LDR light sensor serial
  Byala Robots Club
  author: A.Anchev
*/

#define LDRsensor_pin A15

// =============== SETUP =============
void setup() {
  Serial.begin(9600);
}

// ============== LOOP ==============
void loop() {
  int sensorValue = analogRead(LDRsensor_pin);
  Serial.println(sensorValue);
  delay(7);
}
