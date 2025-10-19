#include <Servo.h>

// Servo motor objects
Servo horizontalServo;
Servo verticalServo;

// Servo position variables
int hPosition = 180;
int vPosition = 45;

// Servo movement limits
const int H_MAX = 175;
const int H_MIN = 5;
const int V_MAX = 100;
const int V_MIN = 1;

// LDR sensor pins
const int LDR_TOP_LEFT = A0;
const int LDR_BOTTOM_LEFT = A1;
const int LDR_BOTTOM_RIGHT = A2;
const int LDR_TOP_RIGHT = A3;

// Configuration constants
const int DELAY_TIME = 10;
const int TOLERANCE = 90;

void setup() {
  // Attach servos to their pins
  horizontalServo.attach(2);
  verticalServo.attach(13);
  
  // Set initial positions
  horizontalServo.write(hPosition);
  verticalServo.write(vPosition);
  
  // Startup delay
  delay(2500);
}

void loop() {
  // Read LDR sensor values
  int topLeft = analogRead(LDR_TOP_LEFT);
  int topRight = analogRead(LDR_TOP_RIGHT);
  int bottomLeft = analogRead(LDR_BOTTOM_LEFT);
  int bottomRight = analogRead(LDR_BOTTOM_RIGHT);

  // Calculate average values for each direction
  int avgTop = (topLeft + topRight) / 2;
  int avgBottom = (bottomLeft + bottomRight) / 2;
  int avgLeft = (topLeft + bottomLeft) / 2;
  int avgRight = (topRight + bottomRight) / 2;

  // Calculate differences
  int verticalDiff = avgTop - avgBottom;
  int horizontalDiff = avgLeft - avgRight;

  // Adjust vertical servo if difference exceeds tolerance
  if (abs(verticalDiff) > TOLERANCE) {
    if (avgTop > avgBottom) {
      vPosition++;
      if (vPosition > V_MAX) vPosition = V_MAX;
    } else {
      vPosition--;
      if (vPosition < V_MIN) vPosition = V_MIN;
    }
    verticalServo.write(vPosition);
  }

  // Adjust horizontal servo if difference exceeds tolerance
  if (abs(horizontalDiff) > TOLERANCE) {
    if (avgLeft > avgRight) {
      hPosition--;
      if (hPosition < H_MIN) hPosition = H_MIN;
    } else {
      hPosition++;
      if (hPosition > H_MAX) hPosition = H_MAX;
    }
    horizontalServo.write(hPosition);
  }

  delay(DELAY_TIME);
}