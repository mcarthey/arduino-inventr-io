const int buttonPin1 = 3;  // Pin for button 1
const int buttonPin2 = 2;  // Pin for button 2
const int ledPin1 = 9;     // Pin for LED 1
const int ledPin2 = 8;     // Pin for LED 2

// initial states
int led1State = 1;
int led2State = 0;

// debounce variables
unsigned long lastUpdatedTime = 0;
unsigned long delayTime = 200;

void setup() {
  pinMode(buttonPin1, INPUT);  // Button 1 configured as input
  pinMode(buttonPin2, INPUT);  // Button 2 configured as input
  pinMode(ledPin1, OUTPUT);    // LED 1 configured as output
  pinMode(ledPin2, OUTPUT);    // LED 2 configured as output
}

void loop() {
  int buttonState1 = digitalRead(buttonPin1);  // Read the state of button 1
  int buttonState2 = digitalRead(buttonPin2);  // Read the state of button 2

  // light LED based on states
  if (led1State == 1) {
    digitalWrite(ledPin1, HIGH);
  }
  else {
    digitalWrite(ledPin1, LOW);
  }

  if (led2State == 1) {
    digitalWrite(ledPin2, HIGH);
  }
  else {
    digitalWrite(ledPin2, LOW);
  }

  // manage states - don't flip LED state on button press if the other light is currently on
  if (millis() - lastUpdatedTime > delayTime) {
    if (buttonState1 == HIGH && led2State != 1) {
      led1State = !led1State;
      lastUpdatedTime = millis();
    }

    if (buttonState2 == HIGH && led1State != 1) {
      led2State = !led2State;
      lastUpdatedTime = millis();
    }
  }

}
