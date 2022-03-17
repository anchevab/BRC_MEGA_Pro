/*
  Arduino MEGA 2560 shield testI2C multiplexer
  Byala Robots Club

  U8glib functions https://github.com/olikraus/u8glib/wiki/userreference

*/

#include <Wire.h>
#include <LM75A.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "U8glib.h"

#define TCAADDR 0x70
#define POT A9
// ---------- Create I2C BME 280 instance
#define SEALEVELPRESSURE_HPA (1031)    // задаване на атмосферното налягане на морското равнище (Варна) в деня, когато включваме сензора
Adafruit_BME280 bme;

// ------ Create I2C LM75A instance
LM75A lm75a_sensor(false,  //A0 LM75A pin state
                   false,  //A1 LM75A pin state
                   false); //A2 LM75A pin state

//------- Create OLED display instance
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);   // I2C comunication

float temp, pressure, humidity, altitude, value;
// ------------ TCA9548 select -------
void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

// ---------------- DRAW --------------------
void draw() {
  char t[8];
  itoa(temp, t, 10);
  char h[8];
  itoa(humidity, h, 10);
  char analog_pot[8];
  itoa(value, analog_pot, 10);
  u8g.drawStr( 10, 20, "Temp=");           // първи ред
  u8g.drawStr( 52, 20, t);
  u8g.drawStr( 10, 35, "Hum =");           // втори ред
  u8g.drawStr( 52, 35, h);
  u8g.drawStr( 10, 50, "Pot =");           // втори ред
  u8g.drawStr( 52, 50, analog_pot);
}

// ================ SETUP =================
void setup(void)
{
  Serial.begin(9600);
  tcaselect(0);//--- for start BME280
  bme.begin();
  u8g.setFont(u8g_font_unifont);
  u8g.setColorIndex(1);
}

// ================ LOOP ===================
void loop(void)
{
  value = analogRead(POT);

  tcaselect(0);
  temp = bme.readTemperature();
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println(" *C");

  pressure = bme.readPressure() / 100.0F;
  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");

  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  Serial.print("Altitude = ");
  Serial.print(altitude);
  Serial.println(" m");

  humidity = bme.readHumidity();
  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.println("------------------------");

  tcaselect(1);
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
  // --------------

  tcaselect(2);
  float temperature = lm75a_sensor.getTemperatureInDegrees();
  if (temperature == INVALID_LM75A_TEMPERATURE) {
    Serial.println("Error while getting temperature");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" degrees");
  }
  Serial.println("------------------------");

  tcaselect(3);
  // put the code for I2C3
  // ......
  // ---------------
  tcaselect(4);
  // put the code for I2C4
  // .........
  // ----------------
  tcaselect(5);
  // put the code for I2C5
  // ............
  // --------------
  tcaselect(6);
  // put the code for I2C6
  // ...........
  // ----------------
  tcaselect(7);
  // put the code for I2C7
  // ......
  // ---------------

  delay(500);
}
