#define tempPin A13
int value;


void setup()
{
  Serial.begin(9600);
}
void loop()
{
  value = analogRead(tempPin);
  float mv = ( value / 1024.0) * 5000;
  float cel = mv / 10;
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  delay(1000);
}
