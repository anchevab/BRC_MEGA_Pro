/*
  Product name: URM09 Ultrasonic Sensor(Gravity Analog)(V1.0)
  Product SKU : SEN0307
  Byala Robots Club
  author: A.Anchev
*/

#define  MAX_RANG      (520)                     //the max measurement vaule of the module is 520cm(a little bit longer than  effective max range)
#define  ADC_SOLUTION  (1023.0)           //ADC accuracy of Arduino UNO is 10bit

#define sensityPin A0
float dist_t, sensity_t;

// ======= SETUP ========
void setup() {
  Serial.begin(9600);
}

// ======= LOOP ========
void loop() {
  sensity_t = analogRead(sensityPin);
  dist_t = sensity_t*MAX_RANG / ADC_SOLUTION;                 // --- measure distance
  Serial.print(dist_t, 1);
  Serial.println("cm");
  delay(100);
}
