const int buttonPin1 = 2;  // Pin for button 1
const int buttonPin2 = 3;  // Pin for button 2
const int ledPin1 = 8;     // Pin for LED 1
const int ledPin2 = 9;     // Pin for LED 2

void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);  // Enable internal pull-up resistor for button 1
  pinMode(buttonPin2, INPUT_PULLUP);  // Enable internal pull-up resistor for button 2
  pinMode(ledPin1, OUTPUT);           // Set pin for LED 1 as output
  pinMode(ledPin2, OUTPUT);           // Set pin for LED 2 as output
  
  digitalWrite(ledPin1, LOW);         // Initially, both LEDs are off
  digitalWrite(ledPin2, LOW);
}

void loop() {
  int buttonState1 = digitalRead(buttonPin1);  // Read the state of button 1
  int buttonState2 = digitalRead(buttonPin2);  // Read the state of button 2
  
  // If button 1 is pressed and LED 2 is off, turn on LED 1
  if (buttonState1 == LOW && digitalRead(ledPin2) == LOW) {
    digitalWrite(ledPin1, HIGH);   // Turn on LED 1
    digitalWrite(ledPin2, LOW);    // Ensure LED 2 is off
  }

  // If button 2 is pressed and LED 1 is off, turn on LED 2
  if (buttonState2 == LOW && digitalRead(ledPin1) == LOW) {
    digitalWrite(ledPin2, HIGH);   // Turn on LED 2
    digitalWrite(ledPin1, LOW);    // Ensure LED 1 is off
  }
}
