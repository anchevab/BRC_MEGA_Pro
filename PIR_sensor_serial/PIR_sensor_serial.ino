/*
  PIR sensor MEGA 2560 Pro shield
  Byala Robots Club
  Author: A.Anchev
*/

#define pir_sensor 25

// ============= SETUP =============
void setup() {
  Serial.begin(9600);
  pinMode(pir_sensor, INPUT);
}

// ============ LOOP ==============
void loop() {
  int sensorState = digitalRead(pir_sensor);
  Serial.println(sensorState);
  delay(10);
}
