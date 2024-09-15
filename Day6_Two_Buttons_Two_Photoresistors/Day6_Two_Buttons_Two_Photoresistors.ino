const int buttonPin1 = 3;  // Pin for button 1
const int buttonPin2 = 2;  // Pin for button 2
const int ledPin1 = 9;     // Pin for LED 1
const int ledPin2 = 8;     // Pin for LED 2
const int photoPin1 = A0;
const int photoPin2 = A1;
const int lightThreshold = 190;

// initial states
int buttonState1 = 0;
int buttonState2 = 0;
int lightLevel1 = 0;
int lightLevel2 = 0;

// debounce variables
unsigned long lastUpdatedTime = 0;
unsigned long delayTime = 200;

void setup() {
  pinMode(buttonPin1, INPUT);  // Button 1 configured as input
  pinMode(buttonPin2, INPUT);  // Button 2 configured as input
  pinMode(ledPin1, OUTPUT);    // LED 1 configured as output
  pinMode(ledPin2, OUTPUT);    // LED 2 configured as output

  Serial.begin(9600);
}

void loop() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

  if (millis() - lastUpdatedTime > delayTime) {

    lightLevel1 = analogRead(photoPin1);
    lightLevel2 = analogRead(photoPin2);

    Serial.print("Light levels: ");
    Serial.print(lightLevel1);
    Serial.print(" ");
    Serial.println(lightLevel2);

    if (buttonState1 == HIGH || lightLevel1 < lightThreshold) {
      digitalWrite(ledPin1, HIGH);
    } else {
      digitalWrite(ledPin1, LOW);
    }

    if (buttonState2 == HIGH || lightLevel2 < lightThreshold) {
      digitalWrite(ledPin2, HIGH);
    } else {
      digitalWrite(ledPin2, LOW);
    }

    lastUpdatedTime = millis();
  }
}
