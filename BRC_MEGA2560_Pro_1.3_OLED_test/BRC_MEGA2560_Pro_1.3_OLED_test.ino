#include <Wire.h>
#include "U8glib.h"

#define TCAADDR 0x70
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);

// ---------------------------
void draw(void) {
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 10);
  u8g.print("This is the 1.3\"");
  u8g.setPrintPos(0, 25);
  u8g.print("White i2c OLED from");
  u8g.setPrintPos(0, 40);
  u8g.print("ICStation.com.");
}
// ----------------------------------------
void draw2(void) {
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 10);
  u8g.print("Check out the project");
  u8g.setPrintPos(0, 25);
  u8g.print("and review on");
  u8g.setPrintPos(0, 40);
  u8g.setFont(u8g_font_profont10);
  u8g.print("www.brc.soupvolov.com");
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

}
// ============== LOOP =================
void loop(void)
{
  tcaselect(1);
  u8g.firstPage();
  do {
    draw();
  } while (u8g.nextPage() );
  delay(3500);
  u8g.firstPage();
  do {
    draw2();
  } while (u8g.nextPage());
  delay(3500);
}
