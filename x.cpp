#include <Adafruit_LiquidCrystal.h>

const int trigPin = 2;
const int echoPin = 3;
const int irPin = 4;  // IR sensor pin

const int motorPin1 = 8;
const int motorPin2 = 9;
const int enablePin = 10;

long duration;
int distance;  // Distance in centimeters
const int motorSpeed = 255;
int seconds = 0;  // Seconds counter for LCD display

// Distance thresholds (converted from inches to centimeters)
const float stopDistanceInch = 2.0;
const float reverseDistanceInch = 8.0;
const float stopDistance = stopDistanceInch * 2.54;   // Convert to cm
const float reverseDistance = reverseDistanceInch * 2.54; // Convert to cm

// Initialize the LCD (address set to 0 by default in Adafruit_LiquidCrystal)
Adafruit_LiquidCrystal lcd_1(0);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irPin, INPUT);  // Set IR sensor as input

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  Serial.begin(9600);

  // Initialize the LCD with 16 columns and 2 rows
  lcd_1.begin(16, 2);
  lcd_1.print("System Initializing");
  delay(1000);
  lcd_1.clear();
}

void loop() {
  distance = getDistance();
  int irValue = digitalRead(irPin);  // Read IR sensor value

  lcd_1.clear();  // Clear LCD before updating new values

  if (irValue == HIGH) {  // If IR sensor detects an obstacle
    stopMotor();          // Stop the motor
    Serial.println("Obstacle detected by IR sensor, stopping motor.");

    // Display obstacle info on the LCD
    lcd_1.setCursor(0, 0);
    lcd_1.print("IR: Obstacle!");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Dist: ");
    lcd_1.print(distance);
    lcd_1.print(" cm");
  } 
  else {  // If no obstacle detected by IR sensor, check distance
    if (distance >= reverseDistance) {
      moveForward(motorSpeed);  // Move forward if distance >= 8 inches
      lcd_1.setCursor(0, 0);
      lcd_1.print("Moving Forward");
    } 
    else if (distance < reverseDistance && distance > stopDistance) {
      moveBackward(motorSpeed);  // Move backward if distance is between 2 and 8 inches
      lcd_1.setCursor(0, 0);
      lcd_1.print("Moving Backward");
    }
    else if (distance <= stopDistance && distance > 0) {
      stopMotor();  // Stop if distance <= 2 inches
      lcd_1.setCursor(0, 0);
      lcd_1.print("Too Close, Stop");
    }

    // Display distance information
    lcd_1.setCursor(0, 1);
    lcd_1.print("Dist: ");
    lcd_1.print(distance);
    lcd_1.print(" cm  ");
  }

  // Display the seconds counter on the LCD
  lcd_1.setCursor(10, 1);
  lcd_1.print("Sec:");
  lcd_1.print(seconds);

  lcd_1.setBacklight(1);  // Turn on backlight
  delay(500);  // Wait for 500 milliseconds
  lcd_1.setBacklight(0);  // Turn off backlight
  delay(500);  // Wait for another 500 milliseconds

  seconds += 1;  // Increment seconds counter
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
  digitalWrite(motorPin1, LOW);  // Change motor direction
  digitalWrite(motorPin2, HIGH);
  analogWrite(enablePin, speed);
}

void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 0);
}
