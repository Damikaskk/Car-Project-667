// V7670 Camera Module Pins
const int cameraReset = 5; // Pin to reset the camera
const int cameraPower = 6; // Pin to power the camera

// Power on the Camera Module
digitalWrite(cameraPower, HIGH);  // Turn on camera power
digitalWrite(cameraReset, HIGH);  // Reset the camera to initialize properly
delay(100);  // Short delay for stabilization

// Function to Detect Parcel Color
String detectColor() {
  int red = analogRead(A7);   // Read red component from the camera sensor
  int green = analogRead(A8); // Read green component from the camera sensor
  int blue = analogRead(A9);  // Read blue component from the camera sensor

  // Determine the dominant color based on the highest value
  if (red > green && red > blue) return "Red";      // If red is the highest, return "Red"
  if (green > red && green > blue) return "Green";  // If green is the highest, return "Green"
  if (blue > red && blue > green) return "Blue";    // If blue is the highest, return "Blue"
  
  return "Unknown";  // If no dominant color is detected, return "Unknown"
}

// Call the Color Detection Function and Store Result
String detectedColor = detectColor(); // Get the detected color from the camera

// Display Detected Color on LCD
lcd.setCursor(0, 0);  // Move cursor to the first row
lcd.print("Color: " + detectedColor);  // Print detected color on the LCD screen
