/*
  DigitalReadSerial DIP 4 switch
*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
#define pushButton1 35
#define pushButton2 37
#define pushButton3 39
#define pushButton4 41

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton1, INPUT);
  pinMode(pushButton2, INPUT);
  pinMode(pushButton3, INPUT);
  pinMode(pushButton4, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState1 = digitalRead(pushButton1);
  int buttonState2 = digitalRead(pushButton2);
  int buttonState3 = digitalRead(pushButton3);
  int buttonState4 = digitalRead(pushButton4);
  // print out the state of the button:
  Serial.print(buttonState1);
  Serial.print("\t");
  Serial.print(buttonState2);
  Serial.print("\t");
  Serial.print(buttonState3);
  Serial.print("\t");
  Serial.println(buttonState4);
  delay(10);        // delay in between reads for stability
}
