const int trigPin = 2;
const int echoPin = 3;

const int motorPin1 = 8;
const int motorPin2 = 9;
const int enablePin = 10;

long duration;
int distance;
const int motorSpeed = 255;

const float stopDistanceInch = 2.0;
const float reverseDistanceInch = 8.0;
const float stopDistance = stopDistanceInch * 2.54;   // Convert to cm
const float reverseDistance = reverseDistanceInch * 2.54; // Convert to cm

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  distance = getDistance();

  if (distance >= reverseDistance) {
    moveForward(motorSpeed);  // Move forward if distance is 8 inches or more
  } 
  else if (distance < reverseDistance && distance > stopDistance) {
    moveBackward(motorSpeed);  // Reverse if distance is between 2 and 8 inches
  }
  else if (distance <= stopDistance && distance > 0) {
    stopMotor();  // Stop if distance is 2 inches or less
  }

  delay(100);
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Convert time to distance in cm

  return distance;
}

void moveForward(int speed) {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, speed);
}

void moveBackward(int speed) {
  digitalWrite(motorPin1, LOW);  // Reverse motor direction
  digitalWrite(motorPin2, HIGH);
  analogWrite(enablePin, speed);
}

void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 0);
}
