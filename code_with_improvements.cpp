#include <Wire.h>
#include <LiquidCrystal.h>
#include <Arduino.h>

// LCD display setup
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); // RS, E, D4, D5, D6, D7

// Ultrasonic sensor pins
const int trigPin = 2;   
const int echoPin = 3;  

// IR sensor for line following
const int irLineSensor = 4;  

// OV7670 Camera Module Pins
const int cameraReset = 5;  
const int cameraPower = 6;

// Motor control pins
const int motor1Pin1 = 8;   
const int motor1Pin2 = 9;   
const int enablePin1 = 10;  

const int motor2Pin1 = 7;   
const int motor2Pin2 = 11;  
const int enablePin2 = 12;  

// Motor speed and timing constants
const int motorSpeed = 255;   
const int turnSpeed = 200;    
const int turnTime = 2000;    

// Distance thresholds (in cm)
const float stopDistance = 7 * 2.54;      
const float reverseDistance = 15 * 2.54;  

void setup() {
  // Pin configurations
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irLineSensor, INPUT);
  
  pinMode(cameraReset, OUTPUT);
  pinMode(cameraPower, OUTPUT);

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

  // Power on the camera
  digitalWrite(cameraPower, HIGH);
  digitalWrite(cameraReset, HIGH);
  delay(100);

  randomSeed(analogRead(A6));
}

void loop() {
  static String lastMessage = "";

  int distance = getDistance();
  int lineDetected = digitalRead(irLineSensor);

  String currentMessage;

  // Detect parcel color
  String detectedColor = detectColor();

  // If an obstacle is detected, stop
  if (distance <= stopDistance && distance > 0) {
    stopMotors();
    currentMessage = "Standing still ";
  } 
  // If the IR sensor detects the line, follow it
  else if (lineDetected == HIGH) {
    moveForward(motorSpeed);
    currentMessage = "Following Line ";
  } 
  // If the IR sensor loses the line, adjust direction
  else if (lineDetected == LOW) {
    adjustToFindLine();
    currentMessage = "Searching Line ";
  } 
  // If no obstacles and no line loss, continue normal movement
  else if (distance >= reverseDistance) {
    moveForward(motorSpeed);
    currentMessage = "Moving Forward ";
  } 
  // If within turn range, stop and turn randomly
  else {  
    stopMotors();
    delay(500);
    int turnDirection = random(0, 2);
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
    lcd.print("Color: " + detectedColor);

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
  return duration * 0.034 / 2;
}

// Detect parcel color using OV7670
String detectColor() {
  int red = analogRead(A7);   // Simulated camera color reading
  int green = analogRead(A8);
  int blue = analogRead(A9);

  if (red > green && red > blue) return "Red";
  if (green > red && green > blue) return "Green";
  if (blue > red && blue > green) return "Blue";
  return "Unknown";
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

// Adjust direction to find the line again
void adjustToFindLine() {
  stopMotors();
  delay(500);

  int turnDirection = random(0, 2);
  if (turnDirection == 0) {
    turnLeft();
  } else {
    turnRight();
  }
}
