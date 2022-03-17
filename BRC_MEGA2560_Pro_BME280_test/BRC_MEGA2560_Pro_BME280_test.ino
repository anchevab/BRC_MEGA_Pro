#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define TCAADDR 0x70
#define SEALEVELPRESSURE_HPA (1015)                   // задаване на атмосферното налягане на морското равнище (Варна) в деня, когато включваме сензора

Adafruit_BME280 bme;

// -----------------------------------
void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

// =============  SETUP ==================
void setup(void)
{
  Serial.begin(9600);
  tcaselect(0);
  bme.begin();

}
// ============== LOOP =================
void loop(void)
{
  tcaselect(0);
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
  Serial.println("==================================");
  delay(2000);
}
