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
#include <OneWire.h>
#include <DallasTemperature.h>

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
#define PIR 25
#define joyX A5
#define joyY A7
#define moisture A0
#define ultrasonic_analog A2
#define tempPin A13
#define ldr_pin A15
#define  MAX_RANG      (520)
#define  ADC_SOLUTION  (1023.0)
#define ONE_WIRE_BUS 40

// ------- Create VIRTUAL OBJECT --------------
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
Adafruit_BME280 bme;
TM1637TinyDisplay display(CLK, DIO);
DHT dht(DHTPIN, DHTTYPE);
OneWire oneWire(ONE_WIRE_BUS);            // създаване на обект oneWire за комуникация със сезора DS18B20 чрез пин 2
DallasTemperature sensors(&oneWire);

// ----------- Create VARIABLES -------------
float temp, outputVoltage, uvIntensity;
int hum, pressure, altitude;
const int ledPin =  28;
int ledState = LOW;
unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
const long interval = 2000;                       // --- interval at which to blink (milliseconds)
const long interval1 = 1000;
const long interval2 = 100;
unsigned long currentMillis = 0;
unsigned long currentMillis1 = 0;
unsigned long currentMillis2 = 0;
unsigned long currentMillis3 = 0;
int pot_value, uvLevel, refLevel;
int touch_state = 0;
int dht_t, dht_h, light;
int temp_value, temp2;
float dist_t, sensity_t;
int dht_t1, dht_h1;
float temp_ds18b20;

//----------- temp sensor LM35DZ -------
int temp_lm35() {
  temp_value = analogRead(tempPin);
  float mv = ( temp_value / 1024.0) * 5000;
  float temp_cel = mv / 10;
  //  Serial.print("TEMPRATURE = ");
  //  Serial.print(temp_cel);
  //  Serial.print("*C");
  currentMillis1 = millis();
  if (currentMillis1 - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis1;
    return temp_cel;
  }
}
// ------------ URM09 ultrasonic --------------
float urm09_sens() {
  sensity_t = analogRead(ultrasonic_analog);
  dist_t = sensity_t*MAX_RANG / ADC_SOLUTION;
  //  Serial.print(dist_t, 1);
  //  Serial.println("cm");
  currentMillis2 = millis();
  if (currentMillis2 - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis2;
    return dist_t;
  }
}

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
  pinMode(PIR, INPUT);
  display.setBrightness(BRIGHT_7);
  dht.begin();
  tcaselect(0);
  bme.begin();
  sensors.begin();
}
// ============== LOOP =================
void loop()
{
  int ldr_light = analogRead(ldr_pin);                                            // ----- ldr light sensor
  int moisture_sens = analogRead(moisture);                             // ------ mosture sensor
  moisture_sens = map(moisture_sens, 0, 1024, 100, 0);
  float an_ultra = urm09_sens();                                                   // ------ URM09 ultrasonic
  int x = analogRead(joyX);                                                             // ----- joystick X access
  int y = analogRead(joyY);                                                             // ----- joystick Y access
  int pir_sensor = digitalRead(PIR);                                                // ----- PIR sensor
  temp2 = temp_lm35();                                                                 // -----  temp LM35dz
  int button_state = digitalRead(button_pin);                              // ---- big button state
  sensors.requestTemperatures();
  temp_ds18b20 = sensors.getTempCByIndex(0);

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
  // ----- read from DHT 11
  currentMillis3 = millis();
  if (currentMillis3 - previousMillis3 >= interval1) {
    previousMillis3 = currentMillis3;
    dht_t = dht.readTemperature();                                    // ----- dht11 temp
    dht_h = dht.readHumidity();                                          // -----  dht11 humidity
  }
  light = analogRead(light_pin);                                          // ---- TEMT600 light sensor
  uvLevel = averageAnalogRead(UVOUT);
  refLevel = averageAnalogRead(REF_3V3);
  outputVoltage = 3.3 / refLevel * uvLevel;
  uvIntensity = mapfloat(outputVoltage, 0.79, 2.8, 0.0, 15.0);         // ---- UV sensor
  pot_value = analogRead(pot_pin);                                                    //  ----- potentiometer value
  display.showNumber(pot_value);

  // ----- read from BME 280
  tcaselect(0);
  temp = bme.readTemperature();                                                      // --- temp
  hum = bme.readHumidity();                                                             // ---- humidity
  pressure = bme.readPressure() / 100.0F;                                        // ---- pressure
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);               // ----- altitude

  touch_state = digitalRead(touch_pin);
  if (touch_state == 0) {
    tcaselect(1);
    u8g.firstPage();
    do {
      draw();
    } while (u8g.nextPage() );
  } else {
    tcaselect(1);
    u8g.firstPage();
    do {
      draw1();
    } while (u8g.nextPage() );
  }
  //  Serial.println(pir_sensor);
  //  Serial.print(x);
  //  Serial.print("\t");
  //  Serial.println(y);
  //  Serial.print(moisture_sens);
  //  Serial.print("\t");
  //  Serial.println(an_ultra);
  //  Serial.println(temp2);
  //  Serial.println(ldr_light);
  //  Serial.print(dht_t);
  //  Serial.print("\t");
  //  Serial.println(dht_h);
  //  Serial.print(temp);
  //  Serial.print("\t");
  //  Serial.print(hum);
  //  Serial.print("\t");
  //  Serial.print(pressure);
  //  Serial.print("\t");
  //  Serial.println(altitude);
  String dataNode1 = String(temp) + "/" + String(hum) + "/" + String(pressure) + "/" + String(altitude) + "/" + String(pir_sensor) + "/" + String(x) + "/" + String(y) + "/" + String(moisture_sens) + "/" + String(an_ultra) + "/" + String(temp2) + "/" + String(ldr_light) + "/";
  String dataNode2 = String(dht_t) + "/" + String(dht_h) + "/" + String(pot_value) + "/" + String(light) + "/" + String(temp_ds18b20);
  String dataNode = dataNode1 + dataNode2;
  Serial.println(dataNode);
  delay(150);
}
