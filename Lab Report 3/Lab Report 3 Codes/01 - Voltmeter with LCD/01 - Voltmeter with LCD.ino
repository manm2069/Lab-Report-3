/*
  LCD Voltmeter

  This program reads the bit value recieved on pin A0 and converts it to a voltage value. These two values are then displayed on the Serial Monitor and the LCD.

  This program makes use of #include, LiquidCrystal.h, const, int, lcd, Serial.begin, lcd.begin, analogRead, Serial.print, float, lcd.setCursor, and lcd.print.
*/

// Initialize the liquid crystal library
#include <LiquidCrystal.h>

// Variables
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // Creates variables to make it easier to identify Liquid Crystal pins by associating them with Arduino Pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Initialize the Arduino pins as LiquidCrystal pins

void setup() {
  Serial.begin(9600); // Sets the data rate in bits per second (baud) for serial data transmission
  lcd.begin(16, 2); // Set up the LCD's number of columns and rows
}

void loop() {
  int val = analogRead(A0); // Creates a variable called "val" and have it gain the value of the analog read value of pin A0
  Serial.print("Bit Value: "); // Print in the serial monitor the text "Bit Value: "
  Serial.print(val); // Prints in the serial monitor the value of the variable "val"

  float volt = val/204.6; // Creates a variable called "volt" and have it gain the quotient of the variable "val" and 204.6

  Serial.print(" Voltage: "); // Print in the serial monitor the text " Voltage: "
  Serial.println(volt); // Prints in the serial monitor the value of the variable "volt"

  lcd.setCursor(0, 0); // Sets the LCD's cursor to the first row of the LCD
  lcd.print("Bit Value: "); // Prints in the LCD the text "Bit Value: "
  lcd.print(val); // Prints in the LCD the value of the variable "val"
  lcd.print("    "); // Prints in the LCD the text "    "

  lcd.setCursor(0, 1); // Sets the LCD's cursor to the second row of the LCD
  lcd.print("Voltage: "); // Prints in the LCD the text "Voltage: "
  lcd.print(volt); // Prints in the LCD the value of the variable "volt"
  lcd.print(" V"); // Print in the LCD the text " V"
}