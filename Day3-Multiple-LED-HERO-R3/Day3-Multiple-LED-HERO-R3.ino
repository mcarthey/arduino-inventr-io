const int photoPin = A0;    // the pin where the photoresistor is connected
const int ledPin = 13;      // the pin where the LED is connected
const int buzzerPin = 12;   // the pin where the buzzer is connected (optional)
 
int lightLevel = 0;         // variable to store the light level
int threshold = 100;        // threshold for light change detection
 
void setup() {
  pinMode(ledPin, OUTPUT);      // initialize the LED pin as an output
  pinMode(buzzerPin, OUTPUT);   // initialize the buzzer pin as an output (optional)
  Serial.begin(9600);           // begin serial communication for debugging
}
 
void loop() {
  lightLevel = analogRead(photoPin);  // read the light level from the photoresistor
  Serial.println(lightLevel);         // print the light level to the serial monitor for debugging
 
  if (lightLevel < threshold) {       // if the light level is below the threshold
    digitalWrite(ledPin, HIGH);       // turn on the LED
    digitalWrite(buzzerPin, HIGH);    // turn on the buzzer (optional)
  } else {
    digitalWrite(ledPin, LOW);        // turn off the LED
    digitalWrite(buzzerPin, LOW);     // turn off the buzzer (optional)
  }
  delay(100);                         // small delay to stabilize the readings
}