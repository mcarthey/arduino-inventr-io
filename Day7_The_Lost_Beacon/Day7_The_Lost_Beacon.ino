const int buttonPin1 = 3;  
const int buttonPin2 = 2;  
const int buttonPin3 = 4;  
const int ledPin1 = 11;     
const int ledPin2 = 10;     
const int ledPin3 = 9;     
const int photoPin1 = A0;
const int lightThreshold = 190;

// initial states
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int lightLevel = 0;
int ledBrightness = 0;
int ledState1 = 0;
int ledState2 = 0;
int ledState3 = 0;

// debounce variables
unsigned long lastUpdatedTime = 0;
unsigned long delayTime = 200;

void setup() {
  pinMode(buttonPin1, INPUT);  
  pinMode(buttonPin2, INPUT); 
  pinMode(buttonPin3, INPUT);  
  pinMode(ledPin1, OUTPUT);   
  pinMode(ledPin2, OUTPUT);   
  pinMode(ledPin3, OUTPUT);  

  Serial.begin(9600);
}

void loop() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);

  if (millis() - lastUpdatedTime > delayTime) {

    lightLevel = analogRead(photoPin1);
    // ledBrightness = map(lightLevel, 0, 1023, 255, 0);
    ledBrightness = map(lightLevel, 200, 800, 255, 0);

    // Constrain the brightness to ensure it stays within 0-255
    ledBrightness = constrain(ledBrightness, 0, 255);

    // set LED state based on button state
    if (buttonState1 == HIGH) {
      ledState1 = !ledState1;
    }

    if (buttonState2 == HIGH) {
      ledState2 = !ledState2;
    }

    if (buttonState3 == HIGH) {
      ledState3 = !ledState3;
    }

    // turn on LED based on LED state
    if (ledState1 == 1) {
      analogWrite(ledPin1, ledBrightness);
    } else {
      analogWrite(ledPin1, 0);
    }

    if (ledState2 == 1) {
      analogWrite(ledPin2, ledBrightness);
    } else {
      analogWrite(ledPin2, 0);
    }
    if (ledState3 == 1) {
      analogWrite(ledPin3, ledBrightness);
    } else {
      analogWrite(ledPin3, 0);
    }

    lastUpdatedTime = millis();

    // DEBUG
    Serial.print("buttonState1: ");
    Serial.println(buttonState1);

    Serial.print("ledState1: ");
    Serial.println(ledState1);

    Serial.print("lightLevel: ");
    Serial.println(lightLevel);

    Serial.print("ledBrightness: ");
    Serial.println(ledBrightness);
  }
}
