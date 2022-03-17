#define btn 38
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(btn, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int Y_Value = analogRead(A7);
  int X_Value = analogRead(A5);
  int button = digitalRead(btn);
  // print out the value you read:
  Serial.print(X_Value);
  Serial.print("\t");
  Serial.print(Y_Value);
  Serial.print("\t");
  Serial.println(button);
  delay(10);        // delay in between reads for stability
}
