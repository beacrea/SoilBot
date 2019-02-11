// Load libraries
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

// Define variables 

#define I2C_ADDR          0x27 // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7

// Initialise the LCD
LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

// Custom Characters
byte heart[] = {
  B00000,
  B00000,
  B01010,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

byte degree[] = {
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup()
 {
    // Open serial over USB
    Serial.begin(9600); 
    
    // Define the LCD as 16 column by 2 rows 
    lcd.begin (20,4);

    // Create custom character
    lcd.createChar(1, heart);
    lcd.createChar(2, degree);
    
    // Switch on the backlight
    lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
    lcd.setBacklight(HIGH);
    
    // Goto first column (column 0) and first line (Line 0)
    lcd.setCursor(0,0);
    
    // Print at cursor Location
    lcd.print("Plant");
    
    // Goto first column (column 0) and second line (line 1)
    lcd.setCursor(0,1);
    lcd.write(1);

    // Goto first column (column 0) and third line (line 2)
    lcd.setCursor(0,2);
    lcd.print("30");
    lcd.write(2);
    lcd.print("F");
    

    // Goto first column (column 0) and fourth line (line 3)
    lcd.setCursor(0,3);
    lcd.print("D");
 }

void loop() {
//  // scroll 13 positions (string length) to the left
//  // to move it offscreen left:
//  for (int positionCounter = 0; positionCounter < 20; positionCounter++) {
//    // scroll one position left:
//    lcd.scrollDisplayLeft();
//    // wait a bit:
//    delay(500);
//  }
//
//  // delay at the end of the full loop:
//  delay(1000);
}
