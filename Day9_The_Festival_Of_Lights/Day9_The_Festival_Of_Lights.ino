const int buttonPin1 = 3;  
const int buttonPin2 = 2;  
const int buttonPin3 = 4;  
const int ledPin1 = 11;     
const int ledPin2 = 10;     
const int ledPin3 = 9;     

// initial states
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

int lightingMode1 = 0;
int lightingMode2 = 0;
int lightingMode3 = 0;

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
    // set LED state based on button state
    if (buttonState1 == HIGH) {
      if (lightingMode1 == 1) {
        lightingMode1 = 0;
      } else {
        lightingMode1 = 1;
        lightingMode2 = 0;
        lightingMode3 = 0;
      }
      lastUpdatedTime = millis();
    }

    if (buttonState2 == HIGH) {
      if (lightingMode2 == 1) {
        lightingMode2 = 0;
      } else {
        lightingMode1 = 0;
        lightingMode2 = 1;
        lightingMode3 = 0;
      }
      lastUpdatedTime = millis();
    }

    if (buttonState3 == HIGH) {
      if (lightingMode3 == 1) {
        lightingMode3 = 0;
      } else {
        lightingMode1 = 0;
        lightingMode2 = 0;
        lightingMode3 = 1;
      }
      lastUpdatedTime = millis();
    }

    // turn on LED based on lighting mode
    if (lightingMode1 == 1) {
      fireMode();
    } else if (lightingMode2 == 1) {
      fairyMode();
    } else if (lightingMode3 == 1) {
      steadyMode();
    } else {
      offMode();
    }

    lastUpdatedTime = millis();
  }
}

void fireMode() {
    int brightness1 = random(150, 255);
    int brightness2 = random(100, 200);
    int brightness3 = random(50, 150);
    analogWrite(ledPin1, brightness1);
    analogWrite(ledPin2, brightness2);
    analogWrite(ledPin3, brightness3);
}
 
void fairyMode() {
  unsigned long currentMillis = millis();
  int brightness1 = (sin(currentMillis / 200.0) * 127) + 128;
  int brightness2 = (cos(currentMillis / 200.0) * 127) + 128;
  int brightness3 = (sin((currentMillis + 1000) / 200.0) * 127) + 128;
  analogWrite(ledPin1, brightness1);
  analogWrite(ledPin2, brightness2);
  analogWrite(ledPin3, brightness3);
}
 
void steadyMode() {
  analogWrite(ledPin1, 255);
  analogWrite(ledPin2, 255);
  analogWrite(ledPin3, 255);
}

void offMode() {
  analogWrite(ledPin1, 0);
  analogWrite(ledPin2, 0);
  analogWrite(ledPin3, 0);
}

