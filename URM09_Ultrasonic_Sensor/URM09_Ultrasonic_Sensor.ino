/*
   BRC MEGA 2560 URM09 Ultrasonic Sensor(Gravity Analog)(V1.0)
   Byala Robots Club
   author:A.Anchev
*/

#define  MAX_RANG      (520)//the max measurement vaule of the module is 520cm(a little bit longer than  effective max range)
#define  ADC_SOLUTION      (1023.0)//ADC accuracy of Arduino UNO is 10bit

int sensityPin = A0;    // select the input pin
float dist_t, sensity_t;

// =========== SETUP ================
void setup() {
  Serial.begin(9600);
}

// ========== LOOP ================
void loop() {
  sensity_t = analogRead(sensityPin);
  dist_t = sensity_t * MAX_RANG  / ADC_SOLUTION;//
  Serial.print(dist_t, 0);
  Serial.println("cm");
  delay(50);
}
