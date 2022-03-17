/*
   BRC-MEGA2560 DEMO test
   Byala Robots Club
   author: A.Anchev
*/
#include <Wire.h>
#include "U8glib.h"
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Arduino.h>
#include <TM1637TinyDisplay.h>
#include "DHT.h"

#define SEALEVELPRESSURE_HPA (1015)                   // задаване на атмосферното налягане на морското равнище (Варна) в деня, когато включваме сензора
#define TCAADDR 0x70
#define button_pin 26
#define GREEN_LED 30
#define CLK 44
#define DIO 46
#define pot_pin A9
#define touch_pin 23
#define DHTPIN 22
#define DHTTYPE DHT11
#define light_pin A11
#define UVOUT A1
#define REF_3V3 A3

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
Adafruit_BME280 bme;
TM1637TinyDisplay display(CLK, DIO);
DHT dht(DHTPIN, DHTTYPE);

float temp, outputVoltage, uvIntensity;
int hum, pressure, altitude;
const int ledPin =  28;
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 2000;                 // --- interval at which to blink (milliseconds)
unsigned long currentMillis = 0;
int pot_value, uvLevel, refLevel;
int touch_state = 0;
int dht_t, dht_h, light;

// ------------------ draw ---------
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

// ------------------ draw1 ---------
void draw1(void) {
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 10);
  u8g.print("Temperature =");
  u8g.setPrintPos(82, 10);
  u8g.print(dht_t);
  u8g.setPrintPos(0, 25);
  u8g.print("Humidity =");
  u8g.setPrintPos(62, 25);
  u8g.print(dht_h);
  u8g.setPrintPos(0, 40);
  u8g.print("Light =");
  u8g.setPrintPos(55, 40);
  u8g.print(light);
  u8g.setPrintPos(0, 55);
  u8g.print("UV level =");
  u8g.setPrintPos(65, 55);
  u8g.print(uvIntensity);
}

// -----------------------------------
void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}
// ------------- averageAnalogRead ---------
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0;
  for (int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
  return (runningValue);
}
// ------------- MapFloat -----------------
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// =============  SETUP ==================
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(touch_pin, INPUT);
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
  display.setBrightness(BRIGHT_7);
  dht.begin();
  tcaselect(0);
  bme.begin();
}
// ============== LOOP =================
void loop()
{
  int button_state = digitalRead(button_pin);
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
  }
  if (button_state == 1) {
    digitalWrite(GREEN_LED, HIGH);
  } else {
    digitalWrite(GREEN_LED, LOW);
  }

  pot_value = analogRead(pot_pin);
  display.showNumber(pot_value);

  touch_state = digitalRead(touch_pin);
  if (touch_state == 0) {
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
  } else {
    dht_t = dht.readTemperature();
    dht_h = dht.readHumidity();
    light = analogRead(light_pin);
    uvLevel = averageAnalogRead(UVOUT);
    refLevel = averageAnalogRead(REF_3V3);
    outputVoltage = 3.3 / refLevel * uvLevel;
    uvIntensity = mapfloat(outputVoltage, 0.79, 2.8, 0.0, 15.0);
    tcaselect(1);
    u8g.firstPage();
    do {
      draw1();
    } while (u8g.nextPage() );
  }
  delay(50);
}
