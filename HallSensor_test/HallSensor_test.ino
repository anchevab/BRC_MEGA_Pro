/*
  BRC MEGA 2560 hall sensor test to serial
  Byala Robots Club
  autho:A.Anchev
*/

int hall_sensor = 2;

// ============ SETUP ===============
void setup() {
  Serial.begin(9600);
  pinMode(hall_sensor, INPUT);
}

// ============= LOOP ===============
void loop() {
  int sensorState = digitalRead(hall_sensor);
  Serial.println(sensorState);
  delay(1); 
}
