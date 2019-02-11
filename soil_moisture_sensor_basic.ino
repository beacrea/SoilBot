/*  Soil Moisture Device
    Written by Coty Beasley
    https://coty.design

    Project started: Feb 2019
    Project repo: https://github.com/beacrea/SoilMoistureManager
*/

// Libraries to include
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

// Rather than powering the sensor through the 3.3V or 5V pins,
// we'll use a digital pin to power the sensor. This will
// prevent corrosion of the sensor as it sits in the soil.

/********************************************************
   Change these values based on your calibration values
 *******************************************************/
int thresholdUp = 400;
int thresholdDown = 250;

// Declare a variable for the soil moisture sensor
int soilPin = A0;

// Variable for Soil moisture Power
int soilPower = 7;

// Set initial moisture value
int moistureVal = 0;

// Initialise the LCD
LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

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

byte flower[] = {
  B01010,
  B01110,
  B11111,
  B01110,
  B00100,
  B00100,
  B01110,
  B01110
};

byte sun[] = {
  B10101,
  B01110,
  B11011,
  B01110,
  B10101,
  B00000,
  B00000,
  B00000
};


void setup()
{
  Serial.begin(9600); // Open serial over USB
  delay(500); // Wait for display to boot up

  pinMode(soilPower, OUTPUT); // Set D7 as an OUTPUT
  digitalWrite(soilPower, LOW); // Set to LOW so no power is flowing through the sensor

  // Define the LCD as 16 column by 2 rows
  lcd.begin (20, 4);

  // Create custom character
  lcd.createChar(1, heart);
  lcd.createChar(2, degree);
  lcd.createChar(3, flower);
  lcd.createChar(4, sun);

  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);

  // First line
  lcd.setCursor(0, 0);
  for (int i = 1; i <= 20; i++) {
    lcd.write(4);
  }

  // Goto first column (column 0) and second line (Line 0)
  lcd.setCursor(0, 1);
  lcd.print("SoilBot is online ");
  lcd.write(1);
  lcd.print("!");

  // Third line
  lcd.setCursor(0, 2);
  for (int i = 1; i <= 10; i++) {
    lcd.print("-.");
  }

  // Last line
  lcd.setCursor(0, 3);
  for (int i = 1; i <= 20; i++) {
    lcd.write(3);
  }

  // Hold before running
  delay(10000);
}

void loop()
{
  // Here we are declaring a string, which are lines of words,
  // and we want DisplayWords to be the words displayed on
  // the LCD screen, which will change based on whether the soil
  // wet or dry based on our threshold values above.
  String DisplayWords;

  // We need to set up a pin to get the value that the soil
  // moisture sensor is outputting, so sensorValue will get the
  // analog value from the sensor pin A0 on the redboard that we
  // set up earlier.

  int sensorValue;

  // Animation
  runAnimation();
  delay(2000);

  // Run Measurement
  readSoil();
  
  // Display value
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Soil Moisture: ");
  lcd.setCursor(0, 2);
  lcd.print(moistureVal);

  // Serial output
  Serial.print("Soil Moisture: ");
  Serial.println(moistureVal);
  
  // Hold for readability
  delay(5000);
}

void runAnimation() {
  // First frame
  lcd.setCursor(0, 0);
  for (int i = 1; i <= 10; i++) {
    lcd.print("* ");
  }
  lcd.setCursor(0, 1);
  for (int i = 1; i <= 10; i++) {
    lcd.print(" *");
  }
  lcd.setCursor(0, 2);
  for (int i = 1; i <= 10; i++) {
    lcd.print("* ");
  }
  lcd.setCursor(0, 3);
  for (int i = 1; i <= 10; i++) {
    lcd.print(" *");
  }

  // Delay
  delay(1000);

  // Second Frame
  lcd.setCursor(0, 0);
  for (int i = 1; i <= 10; i++) {
    lcd.print(" *");
  }
  lcd.setCursor(0, 1);
  for (int i = 1; i <= 10; i++) {
    lcd.print("* ");
  }
  lcd.setCursor(0, 2);
  for (int i = 1; i <= 10; i++) {
    lcd.print(" *");
  }
  lcd.setCursor(0, 3);
  for (int i = 1; i <= 10; i++) {
    lcd.print("* ");
  }
}

// This is a function used to get the soil moisture content
int readSoil()
{
  // Reset moisture
  moistureVal = 0;
  
  // Turn D7 "On"
  digitalWrite(soilPower, HIGH);

  // Wait 10 milliseconds
  delay(10);

  // Read the SIG value form sensor
  moistureVal = analogRead(soilPin);

  // Turn D7 "Off"
  digitalWrite(soilPower, LOW);

  // Send current moisture value
  return moistureVal;
}
