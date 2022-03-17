/*
  Arduino MEGA 2560 shield and LM35 and 1.3" OLED
  Byala Robots Club

  U8glib functions https://github.com/olikraus/u8glib/wiki/userreference

*/

#include <Wire.h>
#include <SPI.h>
#include "U8glib.h"

#define TCAADDR 0x70
#define tempPin A13

int value;
float cel, mv;

//------- Create OLED display instance
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);   // I2C comunication

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
  dtostrf(cel, 6, 2, t);            // convert float to char array
  //  itoa(cel, t, 10);               // convert integer to char array
  u8g.drawStr( 10, 20, "Temperature is:");           // first row
  u8g.drawStr( 40, 45, t);                           // second row
}

// ================ SETUP =================
void setup(void)
{
  Serial.begin(9600);
  tcaselect(0);//--- for start BME280
  u8g.setFont(u8g_font_unifont);
  u8g.setColorIndex(1);
}

// ================ LOOP ===================
void loop(void)
{
  value = analogRead(tempPin);
  mv = ( value / 1024.0) * 5000;
  cel = mv / 10;
  //  Serial.print("TEMPRATURE = ");
  //  Serial.print(cel);
  //  Serial.print("*C");
  //  Serial.println();

  tcaselect(1);
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
  delay(1000);
}
