#include <Wire.h>
#include <LiquidCrystal.h>
#include <Arduino.h>

// Analogue pin connections for LCD display
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); // RS, E, D4, D5, D6, D7

// Connecting sensors
const int trigPin = 2;   // Ultrasonic sensor trigger pin
const int echoPin = 3;   // Ultrasonic sensor echo pin
const int irPin = 4;     // IR sensor

// === Motor Pins ===
const int motor1Pin1 = 8;   // Left side motor IN1
const int motor1Pin2 = 9;   // Left side motor IN2
const int enablePin1 = 10;  // Power for left side motors

const int motor2Pin1 = 7;   // Right side motor IN3
const int motor2Pin2 = 11;  // Right side motor IN4
const int enablePin2 = 12;  // Power for right side motors

long duration;
int distance;
const int motorSpeed = 255;   // Forward movement speed
const int turnSpeed = 200;    // Turning speed
const int turnTime = 2000;    // Turning duration (ms)

// Distance thresholds
const float stopDistance = 7 * 2.54;      // 7 inches (converted into cm)
const float reverseDistance = 15 * 2.54;  // 15 inches (converted into cm)

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irPin, INPUT);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enablePin2, OUTPUT);

  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Init...");
  delay(1000);
  lcd.clear();

  randomSeed(analogRead(A6));  // Initialize random number generator
}

void loop() {
  static String lastMessage = "";
  distance = getDistance();
  int irValue = digitalRead(irPin);
  
  String currentMessage;

  // Stop the motors if the IR sensor detects an object or if the ultrasonic sensor detects an obstacle too close
  if (irValue == HIGH || (distance <= stopDistance && distance > 0)) {
    stopMotors();
    currentMessage = "Standing still ";
  } 
  // Move forward if the path is clear
  else if (distance >= reverseDistance) {
    moveForward(motorSpeed);
    currentMessage = "Moving Forward ";
  } 
  // If the distance is within the turning range, stop and turn randomly
  else if (distance < reverseDistance && distance > stopDistance) {  
    stopMotors();
    delay(500);
    
    int turnDirection = random(0, 2);  // 0 = left, 1 = right

    if (turnDirection == 0) {
      turnLeft();
      currentMessage = "Turning Left ";
    } else {
      turnRight();
      currentMessage = "Turning Right ";
    }
  }

  // Update the LCD display only if the message has changed to reduce flickering and unnecessary updates
  if (currentMessage != lastMessage) { 
    lcd.setCursor(0, 0);
    lcd.print("667 team wins! ");

    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(currentMessage);

    lastMessage = currentMessage;
  }

  delay(500);
}

// Function to get distance using the ultrasonic sensor
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  // Convert time (microseconds) to distance (cm)
  // Speed of sound = 343 m/s = 0.0343 cm/μs, but we use 0.034 for simplicity.
  // Divide by 2 because the pulse travels to the object and back.
  distance = duration * 0.034 / 2;

  return distance;
}

// Move the robot forward
void moveForward(int speed) {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  
  analogWrite(enablePin1, speed);
  analogWrite(enablePin2, speed);
}

// Stop the motors
void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  
  analogWrite(enablePin1, 0);
  analogWrite(enablePin2, 0);
}

// Turn the robot left
void turnLeft() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  
  analogWrite(enablePin1, turnSpeed);
  analogWrite(enablePin2, turnSpeed);
  delay(turnTime);
  
  stopMotors();
}

// Turn the robot right
void turnRight() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  
  analogWrite(enablePin1, turnSpeed);
  analogWrite(enablePin2, turnSpeed);
  delay(turnTime);
  
  stopMotors();
}
