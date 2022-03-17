#include <Wire.h>
#include "U8glib.h"
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1015)                   // задаване на атмосферното налягане на морското равнище (Варна) в деня, когато включваме сензора
#define TCAADDR 0x70

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
Adafruit_BME280 bme;

float temp;
int hum, pressure, altitude;
// ---------------------------
void draw(void) {
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 10);
  u8g.print("Temperature =");
  u8g.setPrintPos(82, 10);
  u8g.print(temp);
  u8g.setPrintPos(0, 25);
  u8g.print("Humidity =");
  u8g.setPrintPos(62, 25);
  u8g.print(hum);
  u8g.setPrintPos(0, 40);
  u8g.print("Pressure =");
  u8g.setPrintPos(62, 40);
  u8g.print(pressure);
  u8g.setPrintPos(0, 55);
  u8g.print("Altitude =");
  u8g.setPrintPos(65, 55);
  u8g.print(altitude);
}

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
  temp = bme.readTemperature();
  hum = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  tcaselect(1);
  u8g.firstPage();
  do {
    draw();
  } while (u8g.nextPage() );
  delay(70);
}
