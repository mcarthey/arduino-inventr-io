// ==============================
// Joystick-Controlled LED Grid
// ==============================

// Array holding the digital pins connected to the LEDs.
// The order corresponds to the physical layout:
// Index | LED Pin | Position
// ------+---------+---------
//   0   |    2    | Top-Left
//   1   |    5    | Top-Center
//   2   |    8    | Top-Right
//   3   |    3    | Middle-Left
//   4   |    6    | Center
//   5   |    9    | Middle-Right
//   6   |    4    | Bottom-Left
//   7   |    7    | Bottom-Center
//   8   |   10    | Bottom-Right
const int LED_PINS[9] = {2, 5, 8, 3, 6, 9, 4, 7, 10};

// Analog pins connected to the joystick axes
const int JOYSTICK_X = A0; // X-Axis: Left/Right
const int JOYSTICK_Y = A1; // Y-Axis: Up/Down

// Variable to keep track of the current LED position (0-8)
int currentPosition = 4; // Start at the center (Index 4 -> Pin 6)

// Debounce settings to prevent rapid unintended movements
const unsigned long DEBOUNCE_DELAY = 200; // Delay in milliseconds
unsigned long lastMoveTime = 0; // Timestamp of the last movement

// Calibration thresholds for joystick readings
// Adjust these values based on your specific joystick's behavior
const int LEFT_THRESHOLD = 300;   // Below this value is considered "Left"
const int RIGHT_THRESHOLD = 700;  // Above this value is considered "Right"
const int UP_THRESHOLD = 300;     // Below this value is considered "Up"
const int DOWN_THRESHOLD = 700;   // Above this value is considered "Down"

void setup() {
  // Initialize all LED pins as OUTPUT
  for (int i = 0; i < 9; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }

  // Initialize joystick pins as INPUT (optional, as analogRead defaults to INPUT)
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);

  // Initialize Serial Monitor for debugging purposes
  Serial.begin(9600);

  // Initialize LEDs to center position by lighting up the center LED
  updateLED();
}

void loop() {
  unsigned long currentTime = millis(); // Get the current time

  // Check if enough time has passed since the last movement to allow a new input
  if (currentTime - lastMoveTime > DEBOUNCE_DELAY) {
    // Read the analog values from the joystick
    int xValue = analogRead(JOYSTICK_X);
    int yValue = analogRead(JOYSTICK_Y);

    bool moved = false; // Flag to indicate if a movement has occurred

    // Debugging: Print joystick values and current position to Serial Monitor
    Serial.print("X: ");
    Serial.print(xValue);
    Serial.print(" | Y: ");
    Serial.print(yValue);
    Serial.print(" | Position: ");
    Serial.println(currentPosition);

    // ----- X-Axis Handling: Left and Right Movement -----

    // Check if joystick is pushed to the right beyond the RIGHT_THRESHOLD
    if (xValue > RIGHT_THRESHOLD && (currentPosition % 3 != 2)) {
      currentPosition++; // Move right by incrementing the position index
      moved = true;      // Set the movement flag
      Serial.println("Moved Right"); // Debugging message
    }
    // Check if joystick is pushed to the left beyond the LEFT_THRESHOLD
    else if (xValue < LEFT_THRESHOLD && (currentPosition % 3 != 0)) {
      currentPosition--; // Move left by decrementing the position index
      moved = true;      // Set the movement flag
      Serial.println("Moved Left"); // Debugging message
    }

    // ----- Y-Axis Handling: Up and Down Movement -----

    // Check if joystick is pushed upwards beyond the UP_THRESHOLD
    if (yValue < UP_THRESHOLD && (currentPosition > 2)) {
      currentPosition -= 3; // Move up by subtracting 3 from the position index
      moved = true;         // Set the movement flag
      Serial.println("Moved Up"); // Debugging message
    }
    // Check if joystick is pushed downwards beyond the DOWN_THRESHOLD
    else if (yValue > DOWN_THRESHOLD && (currentPosition < 6)) {
      currentPosition += 3; // Move down by adding 3 to the position index
      moved = true;         // Set the movement flag
      Serial.println("Moved Down"); // Debugging message
    }

    // If any movement has occurred, update the LEDs and reset the debounce timer
    if (moved) {
      // Ensure the currentPosition stays within the valid range [0, 8]
      currentPosition = constrain(currentPosition, 0, 8);

      // Update the LEDs to reflect the new position
      updateLED();

      // Update the timestamp of the last movement
      lastMoveTime = currentTime;
    }
  }

  // Short delay to prevent the loop from running too quickly
  delay(10);
}

// ==============================
// Function: updateLED
// ------------------------------
// Turns off all LEDs and then lights up the LED at the currentPosition.
// ==============================
void updateLED() {
  // Turn off all LEDs to ensure only one is lit
  for (int i = 0; i < 9; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }

  // Turn on the LED corresponding to the currentPosition
  digitalWrite(LED_PINS[currentPosition], HIGH);
}
