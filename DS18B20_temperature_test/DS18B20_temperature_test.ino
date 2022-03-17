/*
 * DS18B20 sensor with Arduino NANO
 * BYala Robots Club
 * eng.Anton Anchev , may 2015
 */

#include <OneWire.h>                      // библиотека, която ни дава възможност да комуникираме със сензори чрез 1 връзка (проводник)
#include <DallasTemperature.h>            // библиотека за управление на сензора DS18B20

#define ONE_WIRE_BUS 40                    // дефиниране на сензора към пин 40 на Arduino MEGA 

OneWire oneWire(ONE_WIRE_BUS);            // създаване на обект oneWire за комуникация със сезора DS18B20 чрез пин 2
DallasTemperature sensors(&oneWire);      // свързване на обектът oneWire с библиотеката.

// ================= SETUP ======================
void setup(void)
{
  Serial.begin(9600);
  Serial.println("Read temperature from DS18B20");
  sensors.begin();                        // резолюцията по подразбиране е 9 бита.Ако е малка, можем да я вдигнем до 12 бита.
}

// ================= LOOP =======================
void loop(void)
{ 
  sensors.requestTemperatures();                   // изпращане на команда за получаване на стойностт на температурата
  Serial.print("Temperature is: ");
  float temp = sensors.getTempCByIndex(0);
  Serial.println(temp);     // използваме getTempCByIndex(0)защото може да имаме закачен повече от един сензор ,
                                                  //така че искаме данни от първия сензор (IC - интергрална схема)
}
