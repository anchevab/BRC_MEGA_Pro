//***********************************************************
// TM1637_4_digit_7_segment_LED_test
// Tested on Arduino NANO
// eng.A.Anchev , Byala Robots Club , 2015
//***********************************************************

#include <Arduino.h>
#include <TM1637Display.h>

// Свързване на 7 сегментния дисплей
#define CLK 44                                        // пин 3
#define DIO 46                                        // пин 2

#define TEST_DELAY   2000
uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };         // равнозначно на 11111111 за тест на дисплея

TM1637Display display(CLK, DIO);                     // създаване на обект display

// ============================== SETUP =========================================

void setup()
{
  display.setBrightness(0x0f);                         // стойности от 0-7
  // ------------ тест на дисплея
  display.setSegments(data);                        // светва всички светодиоди за тест
  delay(TEST_DELAY);
}

// ============================= LOOP ==============================================
void loop()
{
  //------ първи начин на Извеждане на цифри
  display.showNumberDec(99, false, 2, 2);
  delay(TEST_DELAY);
  //----- втори начин на извеждане на цифри
  data[0] = display.encodeDigit(8);                 // преобразува десетично число в 7 сегментна стойност
  data[1] = display.encodeDigit(8);
  data[2] = display.encodeDigit(8);
  data[3] = display.encodeDigit(8);
  display.setSegments(data, 4, 0);                  //функция за извеждане на цифра
  delay(TEST_DELAY);
  //----- втори начин на извеждане на цифри
  data[0] = display.encodeDigit(0);                 // преобразува десетично число в 7 сегментна стойност
  data[1] = display.encodeDigit(0);
  data[2] = display.encodeDigit(0);
  data[3] = display.encodeDigit(0);
  display.setSegments(data, 4, 0);                  //функция за извеждане на цифра
  delay(TEST_DELAY);
  //while(1);                                       // Пауза за рестарт
}
