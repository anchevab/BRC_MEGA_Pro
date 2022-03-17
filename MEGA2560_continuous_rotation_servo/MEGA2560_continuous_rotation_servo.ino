/*
   Arduino MEGA 2560 Pro shield with continuous rotation servo
   Byala Robots Club
   Author A.Anchev
*/

#include <Servo.h>
Servo myservo;

// ============== SETUP =================
void setup()
{
  myservo.attach(32);
}

// ============= LOOP =================
void loop()
{
  myservo.write(45);                  // rotate counterclockwise full speed
  delay(2000);
  myservo.write(90);                  // stop
  delay(100);
  myservo.write(135);                 // rotate clockwise full speed
  delay(2000);
  myservo.write(90);                  // stop
  delay(100);
  myservo.write(80);                  // rotate very slowly counterclockwise
  delay(2000);
  myservo.write(90);                  // stop
  delay(100);
  myservo.write(100);                 // rotate very slowly clockwise
  delay(2000);
}
