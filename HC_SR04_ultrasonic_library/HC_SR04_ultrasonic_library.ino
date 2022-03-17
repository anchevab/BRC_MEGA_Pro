/*
    Arduino MEGA 2560 Pro with HC-SR04 ultrasonic
    Byala Robots Club

    ---------------------    ---------------------
   | HC-SR04 | Arduino |    | 3 pins  | Arduino |
   ---------------------    ---------------------
   |   Vcc   |   5V    |    |   Vcc   |   5V    |
   |   Trig  |   49    | OR |   SIG   |   13    |
   |   Echo  |   45    |    |   Gnd   |   GND   |
   |   Gnd   |   GND   |    ---------------------
   ---------------------
*/
#include <Ultrasonic.h>
Ultrasonic ultrasonic(49, 45);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int distance = ultrasonic.distanceRead();
  Serial.println(distance);
  delay(100);
}
