#include <Wire.h>
#include <LiquidCrystal.h>
#include <Arduino.h>

// LCD display setup (Analogue pin connections)
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); // RS, E, D4, D5, D6, D7

// Ultrasonic sensor pins
const int trigPin = 2;   
const int echoPin = 3;  

// Motor control pins
const int motor1Pin1 = 8;   // Left motor IN1
const int motor1Pin2 = 9;   // Left motor IN2
const int enablePin1 = 10;  // Left motor speed control

const int motor2Pin1 = 7;   // Right motor IN3
const int motor2Pin2 = 11;  // Right motor IN4
const int enablePin2 = 12;  // Right motor speed control

// Motor speed and timing constants
const int motorSpeed = 255;   // Speed for forward movement
const int turnSpeed = 200;    // Speed for turning
const int turnTime = 2000;    // Turning duration (ms)

// Distance thresholds (in cm)
const float stopDistance = 7 * 2.54;      // 7 inches converted to cm
const float reverseDistance = 15 * 2.54;  // 15 inches converted to cm

void setup() {
  // Pin configurations
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enablePin2, OUTPUT);

  Serial.begin(9600);  // Initialize serial monitor

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Init...");
  delay(1000);
  lcd.clear();

  // Seed the random function for turn direction
  randomSeed(analogRead(A6));
}

void loop() {
  static String lastMessage = "";  // Store last message to avoid unnecessary LCD updates

  int distance = getDistance();
  String currentMessage;

  // Check distance and determine movement
  if (distance <= stopDistance && distance > 0) {
    stopMotors();
    currentMessage = "Standing still ";
  } 
  else if (distance >= reverseDistance) {
    moveForward(motorSpeed);
    currentMessage = "Moving Forward ";
  } 
  else {  
    stopMotors();
    delay(500);

    int turnDirection = random(0, 2);  // Randomly select left (0) or right (1)

    if (turnDirection == 0) {
      turnLeft();
      currentMessage = "Turning Left ";
    } else {
      turnRight();
      currentMessage = "Turning Right ";
    }
  }

  // Update LCD only if message has changed
  if (currentMessage != lastMessage) { 
    lcd.setCursor(0, 0);
    lcd.print("667 team wins! ");

    lcd.setCursor(0, 1);
    lcd.print("                "); // Clear the line
    lcd.setCursor(0, 1);
    lcd.print(currentMessage);

    lastMessage = currentMessage;
  }

  delay(500);
}

// Function to measure distance using ultrasonic sensor
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;  // Convert time to distance (cm)
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
