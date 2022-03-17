/*
  AnalogReadSerial moisture sensor
  Byala Robots Club
  author: A.Anchev
*/

#define moisture_sensor A0

// =========== SETUP ============
void setup() {
  Serial.begin(9600);
}

// ============= LOOP ===========
void loop() {
  int sensorValue = analogRead(moisture_sensor);
  Serial.println(sensorValue);
  delay(10);
}
