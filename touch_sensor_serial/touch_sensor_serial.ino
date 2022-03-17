/*
  Touch sensor MEGA 2560 Pro shield
  Byala Robots Club
  Author: A.Anchev
*/

#define touch_sensor 23

// ============= SETUP =============
void setup() {
  Serial.begin(9600);
  pinMode(touch_sensor, INPUT);
}

// ============ LOOP ==============
void loop() {
  int sensorState = digitalRead(touch_sensor);
  Serial.println(sensorState);
  delay(10);
}
