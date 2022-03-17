/*
  Blink
*/
#define LED1 28
#define LED2 30
#define LED3 33

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED1, HIGH);   
  digitalWrite(LED2, HIGH); 
  digitalWrite(LED3, HIGH); 
  delay(1000);                       
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);    
  delay(1000);                
}
