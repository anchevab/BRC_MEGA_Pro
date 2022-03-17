/*
  SD card basic file example shows how to create and destroy
  an SD card file in Arduino Mega over SPI interface
  The circuit -> SD card attached to SPI bus as follows:

  [Arduino Mega]
 ** MOSI - pin 50
 ** MISO - pin 51
 ** CLK - pin 52
 ** CS - pin 53

  Byala Robots Club
  eng.A.Anchev
*/
#include <SD.h>

File myFile;
const int chipSelect = 53;                                        // за Arduino MEGA

// ==================================== SETUP ======================================
void setup()
{
  Serial.begin(9600);
  pinMode(chipSelect, OUTPUT);
  Serial.print("Initializing SD card...");
  
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  }
  else {
    Serial.println("example.txt doesn't exist.");
  }
  String anton ="";
  // -------------------------- отваряне на нов файл и веднага затваряне
  Serial.println("Creating example.txt...");
  myFile = SD.open("example.txt", FILE_WRITE);                    // отваряне на файла example.txt
  anton = "Антон Borisov Anchev";
  myFile.println(anton);
  myFile.println("Това е само тест на запис");
  myFile.close();                                                 // затваряне на файла

  if (SD.exists("example.txt")) {                                 // проверка за съществуване на файла example.txt
    Serial.println("example.txt exists.");
  }
  else {
    Serial.println("example.txt doesn't exist.");
  }

  //Serial.println("Removing example.txt...");
  //SD.remove("example.txt");                                       // изтриване на файла

  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  }
  else {
    Serial.println("example.txt doesn't exist.");
  }
  String dataString = "";                                          // създаване на стринг за записване на данните от сензорите
  // -------------------------------- четене от сензорите и записване на данните в стринг
  for (int analogPin = 0; analogPin < 3; analogPin++) {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 2) {
      dataString += ",";
    }
  }
  // ---------------------- в даден момент може да бъде отворен само един файл
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {                                                  // ако файла съществува, записваме данни в него
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  else {
    Serial.println("error opening datalog.txt");                  // съобщение за грешка при отваряне на файла
  }
}

// ========================================== LOOP ======================================================
void loop()
{

}
