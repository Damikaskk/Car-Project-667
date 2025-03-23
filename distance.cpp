int distance = getDistance(); // Get ultrasonic sensor reading

lcd.setCursor(0, 0);
lcd.print("Color: " + detectedColor); // Display detected color

lcd.setCursor(0, 1);
lcd.print("Dist: ");
lcd.print(distance);  // Display distance
lcd.print(" cm   ");  // Extra spaces to clear old text if needed

