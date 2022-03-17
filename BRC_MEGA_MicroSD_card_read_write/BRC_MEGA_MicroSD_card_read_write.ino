/*
  SD card basic file example shows how to read/write
  Byala Robots Club
  author: eng.A.Anchev
*/
#include <SD.h>

File sdcard_file;
const int chipSelect = 53;

// ============= SETUP ============
void setup()
{
  Serial.begin(9600);
  pinMode(chipSelect, OUTPUT);
  SD.begin();

  sdcard_file = SD.open("data.txt", FILE_WRITE);                      // --- Looking for the data.txt in SD card
  if (sdcard_file) {                                                                               // --- If the file is found
    Serial.println("Writing to file is under process ....");
    sdcard_file.println("This data is for test, eng.Anchev");                              // --- Writing to file
    sdcard_file.close();                                                                      // --- Closing the file
    Serial.println("Done");
  }
  else {
    Serial.println("Failed to open the file");
  }

  sdcard_file = SD.open("data.txt");
  if (sdcard_file) {
    Serial.println("Reading from the file ....");
    while (sdcard_file.available()) {
      Serial.write(sdcard_file.read());
    }
    sdcard_file.close();
  }
  else {
    Serial.println("Failed to open the file");
  }
}

// =========== LOOP ==================
void loop()
{

}
