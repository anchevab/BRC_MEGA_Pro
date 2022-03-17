/*
   BRC MEGA 2560 shield Bluetooth test
   Byala Robots Club
   author: A.Anchev
*/
void setup()
{
  Serial.begin(9600); //pc
  Serial1.begin(9600); //BT
}
void loop()
{
  char ser_char;

  if (Serial.available() > 0)
  {
    Serial1.write(Serial.read());
  }
  if (Serial1.available() > 0)
  { ser_char = Serial1.read();
    Serial.write(ser_char);
  }
}
