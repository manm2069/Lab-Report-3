/*
  LCD Ohmmeter

  This program reads the bit value recieved on pin A0 and converts it to a resistance value. This resistance value is then displayed on the Serial Monitor and the LCD.

  This program makes use of #include, LiquidCrystal.h, const, int, LiquidCrystal, lcd, byte, Serial.begin, lcd.begin, lcd.createChar, lcd.home, analogRead, Serial.print, float, lcd.setCursor, lcd.print, and lcd.write.
*/

// Initialize the liquid crystal library
#include <LiquidCrystal.h>

// Variables
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // Creates variables to make it easier to identify Liquid Crystal pins by associating them with Arduino Pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Initialize the Arduino pins as LiquidCrystal pins

// Creates a byte called "omega" containing the pixel data of the ohms symbol
byte omega[] = {
  B01110,
  B10001,
  B10001,
  B10001,
  B01010,
  B01010,
  B01010,
  B11011
};

void setup() {
  Serial.begin(9600); // Sets the data rate in bits per second (baud) for serial data transmission
  lcd.begin(16, 2); // Set up the LCD's number of columns and rows
  lcd.createChar(0, omega); // Creates character 0 and gives it the pixel data of the byte called "omega"
  lcd.home(); // Positions the cursor in the upper-left of the LCD
  lcd.setCursor(0, 0); // Sets the LCD's cursor to the first row of the LCD
  lcd.print("Resistance:"); // Prints in the LCD the text "Resistance:"
}

void loop() {
  int val = analogRead(A0); // Creates a variable called "val" and have it gain the value of the analog read value of pin A0
  Serial.print("Bit Value: "); // Print in the serial monitor the text "Bit Value: "
  Serial.print(val); // Prints in the serial monitor the value of the variable "val"

  float volt = val/204.6; // Creates a variable called "volt" and have it gain the quotient of the variable "val" and 204.6
  float resistance = (1000*((5/volt)-1)); // Creates a variable called "resistance" and have it gain the value of the computed resistance

  Serial.print(" Resistance: "); // Print in the serial monitor the text " Resistance: "
  Serial.print(resistance); // Prints in the serial monitor the value of the variable "resistance"

  lcd.setCursor(0, 1); // Sets the LCD's cursor to the first row of the LCD
  lcd.print(resistance); // Prints in the LCD the value of the variable "resistance"
  lcd.print(" "); // Print in the LCD the text " "
  lcd.write(byte(0)); // Prints in the LCD character 0
  lcd.print("     "); // Print in the LCD the text "     "
}