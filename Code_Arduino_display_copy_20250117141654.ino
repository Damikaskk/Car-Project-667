#include <LiquidCrystal.h>

// Initialize the library with the shield's pin configuration
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // RS, E, D4, D5, D6, D7

void setup() {
  lcd.begin(16, 2); // Set up the LCD's size (16x2)
  lcd.clear();      // Clear the screen
}

void loop() {
  // First bounce text on row 1
  for (int col = 0; col <= 16; col++) {
    lcd.clear();
    lcd.setCursor(16 - col, 0); // Position text bouncing left to right
    lcd.print("other teams suck coks");
    delay(300); // Adjust speed of bounce
  }

  delay(1000); // Pause for 1 second

  // Then bounce text on row 2
  for (int col = 0; col <= 16; col++) {
    lcd.clear();
    lcd.setCursor(16 - col, 1); // Position text bouncing left to right
    lcd.print("667 team wins");
    delay(300); // Adjust speed of bounce
  }

  delay(1000); // Pause before looping again
}
