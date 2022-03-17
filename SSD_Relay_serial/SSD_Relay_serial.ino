/*
   Arduino MEGA 2560 Pro with 1 rellay (low level trigger)
   Byala Robots Club
   Author eng.A.Anchev
*/
#define rellay 31

void setup() {
  Serial.begin(9600);
  pinMode(rellay, OUTPUT);

}

void loop() {
  digitalWrite(rellay, HIGH);      // включване на релето
  Serial.println("Realy ON");
  delay(1000);
  digitalWrite(rellay, LOW);     // изключване на релето
  Serial.println("Realy OFF");
  delay(1000);
}
