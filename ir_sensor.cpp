const int irLineSensor = 4;  // IR sensor at the bottom for line detection

int lineDetected = digitalRead(irLineSensor);  // Read IR sensor value (HIGH = line detected)


if (lineDetected == HIGH) {
  moveForward(motorSpeed); // If the line is detected, move forward
  currentMessage = "Following Line ";
} 


else if (lineDetected == LOW) {
  adjustToFindLine(); // If the line is lost, adjust direction
  currentMessage = "Searching Line ";
} 


// New function
// Turns left or right randomly to find the line again if it is lost
void adjustToFindLine() {
  stopMotors();
  delay(500);

  int turnDirection = random(0, 2);  // Randomly select left or right turn

  if (turnDirection == 0) {
    turnLeft();
  } else {
    turnRight();
  }
}
