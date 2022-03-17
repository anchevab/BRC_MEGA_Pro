/*
   Arduino UNO with sensor shield v5 and DHT11
   Byala Robots Club
   eng.A.Anchev , 2015
*/
#include "DHT.h"
#define DHTPIN 22                                           // пин 22 свързан към сензора
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  dht.begin();
}

void loop() {
  int h = dht.readHumidity();                               // прочитане на данни за влажността
  int t = dht.readTemperature();                            // прочитане на данни за температурата

  if (isnan(t) || isnan(h)) {                               //проверка дали прочетените стойности са числови стойности, ако не са значи има някакъв проблем
    Serial.println("Greshka pri chetene ot DHT senzora");
  } else {
    Serial.print("Vlajnost: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
  }
  delay(1000);
}
