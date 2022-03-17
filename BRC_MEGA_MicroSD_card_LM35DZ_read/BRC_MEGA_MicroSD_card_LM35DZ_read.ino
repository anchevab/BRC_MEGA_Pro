/*
  SD card basic file example write temperature from LM35DZ
  Byala Robots Club
  author: eng.A.Anchev
*/
#include <SD.h>
#define touch_pin 23
#define lm35_pin A13

File sdcard_file;
const int chipSelect = 53;
float temp = 0;

// ============= SETUP ============
void setup()
{
  Serial.begin(9600);
  pinMode(chipSelect, OUTPUT);
  pinMode(touch_pin, INPUT);
  SD.begin();
}

// =========== LOOP ==================
void loop()
{
  int touch_value = digitalRead(touch_pin);
  float val = analogRead(lm35_pin);
  float temp = val * 0.48828125;
  if (touch_value == 1) {
    sdcard_file = SD.open("data.txt", FILE_WRITE);                      // --- Looking for the data.txt in SD card
    if (sdcard_file) {                                                                               // --- If the file is found
      Serial.println("Writing temp to file is under process ....");
      sdcard_file.println(temp);                                                            // --- Writing to file
      sdcard_file.close();                                                                       // --- Closing the file
      Serial.println("Done");
      delay(1000);
    }
    else {
      Serial.println("Failed to open the file");
    }
  }

}
