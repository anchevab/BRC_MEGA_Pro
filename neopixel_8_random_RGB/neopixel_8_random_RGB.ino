/* NeoPixel 8 for Arduino MEGA 2560 Pro shield
   Byala Robots Club
   create by ing.A.Anchev
*/

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#define PIN         24            // pin on Arduino
#define NUMPIXELS   8             //How many NeoPixels are attached to the Arduino
#define BRIGHTNESS  64

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
long randRED;
long randGREEN;
long randBLUE;
int delayval = 50;
// ================== SETUP ====================
void setup() {
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
}

// ================== LOOP ===================
void loop() {
  for (int i = 0; i < NUMPIXELS; i++) {
    randRED = random(255);                    // generate random color
    randGREEN = random(255);
    randBLUE = random(255);
    pixels.setPixelColor(i, pixels.Color(randRED, randGREEN, randBLUE));     // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.show();                                                           // This sends the updated pixel color to the hardware.
    delay(delayval);
  }
}
