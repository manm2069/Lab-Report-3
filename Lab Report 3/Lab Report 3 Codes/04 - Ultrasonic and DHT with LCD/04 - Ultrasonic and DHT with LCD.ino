/*
  LCD DHT11 and Ultrasonic

  This program reads the temperature and humidity value sensed by the DHT11 sensor, and the distance value sensed by the Ultrasonic sensor

  This program makes use of #include, Adafruit_Sensor.h, DHT.h, DHT_U.h, LiquidCrystal.h, #define, DHT_Unified, dht, const, int, LiquidCrystal, lcd, unsigned, long, byte, float, Serial.begin, pinMode, dht.begin, lcd.begin, 
  lcd.createChar, digitalRead, lcd.clear, if, else, dht.temperature, getEvent, event.temperature, Serial.print, Serial.prinln, lcd.setCursor, lcd.print, lcd.write, dht.humidity, event.relative_humidity, digitalWrite, 
  delayMicroseconds, and pulseIn.
*/

#include <Adafruit_Sensor.h> // Initialize the Adafruit unified sensor library
#include <DHT.h> // Initialize the DHT sensor library
#include <DHT_U.h> // Initialize the DHT sensor library
#include <LiquidCrystal.h> // Initialize the liquid crystal library

#define trigPin 10 // Defines pin 10 as the Arduino connected to the trigger pin of the ultrasonic sensor
#define echoPin 13 // Defines pin 13 as the Arduino connected to the echo pin of the ultrasonic sensor
#define DHTPIN 6 // Defines pin 6 as the Arduino pin connected to the DHT sensor
#define DHTTYPE    DHT11     // Defines DHT11 as the DHT sensor used in the circuit

// Initializes Arduino pin 6 as the pin connected to the DHT11 sensor
DHT_Unified dht(DHTPIN, DHTTYPE);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // Creates variables to make it easier to identify Liquid Crystal pins by associating them with Arduino Pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Initialize the Arduino pins as LiquidCrystal pins

int tempHumiPB2; // Creates a variable called "tempHumiPB2"
int distPB2; // Creates a variable called "distPB2"

unsigned long previousMillis = 0; // Creates a unsigned long variable called "previousMillis" and give it the value 0
const long interval = 500; // Creates a constant long variable called "interval" and give it the value 500

// Creates a byte called "degreesChar" containing the pixel data of the degrees symbol
byte degreesChar[8] = {
  B00111,
  B00101,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

float duration, distance; // Creates two float variables called "duration" and "distance"

void setup() {
  Serial.begin(9600); // Sets the data rate in bits per second (baud) for serial data transmission
  
  // Push Buttons
  pinMode(9, INPUT_PULLUP); // Initializes pin 9 as an input pullup. This pin is connected to the push button that shows the temperature and humidity value
  pinMode(8, INPUT_PULLUP); // Initializes pin 8 as an input pullup. This pin is connected to the push button that shows the distance value

  // Temperature and Humidity
  dht.begin(); // Begins the DHT11 sensor

  // Ultrasonic
  pinMode(trigPin, OUTPUT); // Initializes pin 10 as an output. This pin is connected to the trigger pin of the Ultrasonic sensor
  pinMode(echoPin, INPUT); // Initializes pin 13 as an output. This pin is connected to the echo pin of the Ultrasonic sensor

  // LCD
  lcd.begin(16, 2); // Set up the LCD's number of columns and rows
  lcd.createChar(0, degreesChar); // Creates character 0 and gives it the pixel data of the byte called "degreesChar"
}

void loop() {
  // Push Buttons
  int tempHumiPB = digitalRead(9); // Creates a variable called "tempHumiPB" and give it the read value of Arduino pin 9
  int distPB = digitalRead(8); // Creates a variable called "distPB" and give it the read value of Arduino pin 8

  if (tempHumiPB == 0) { // Checks if the variable "tempHumiPB" is equal to 0
    tempHumiPB2 = 1; // Gives the variable "tempHumiPB2" the value of 1
    distPB2 = 0; // Gives the variable "distPB2" the value of 0
    lcd.clear(); // Clears the text in the LCD
  }

  if(distPB == 0) { // Checks if the variable "distPB" is equal to 0
    tempHumiPB2 = 0; // Gives the variable "tempHumiPB2" the value of 0
    distPB2 = 1; // Gives the variable "distPB2" the value of 1
    lcd.clear(); // Clears the text in the LCD
  }
  
  unsigned long currentMillis = millis(); // Creates an unsigned long variable called "currentMillis" and give it the value of the amounts of milliseconds since the Arduino has started

  // Temperature and Humidity
  if (tempHumiPB2 == 1) { // Checks if the variable "tempHumiPB2" is equal to 1
    if (currentMillis - previousMillis >= interval) { // Checks if the difference of variables "currentMillis" and "previousMillis" is greater than or equal the variable "interval"
      previousMillis = currentMillis; // Gives the variable "previousMillis" the value of the variable "currentMillis"

      sensors_event_t event; // Obtains the details of the sensor in a specific moment in time

      // Get temperature event and print its value
      dht.temperature().getEvent(&event); // Obtains the temperature value
      if (isnan(event.temperature)) { // Checks if the temperature value is an error
        Serial.println(F("Error reading temperature!")); // Print in the serial monitor the text "Error reading temperature!"
      }
      else { // Checks if the temperature value is not an error
        Serial.print(F("Temperature: ")); // Print in the serial monitor the text "Temperature: "
        Serial.print(event.temperature); // Prints in the serial monitor the temperature value
        Serial.println(F("°C")); // Print in the serial monitor the text "°C"

        lcd.setCursor(0, 0); // Sets the LCD's cursor to the first row of the LCD
        lcd.print("Temp: "); // Print in the LCD the text "Temp: "
        lcd.print(event.temperature); // Prints in the LCD the temperature value
        lcd.write(byte(0)); // Prints in the LCD character 0
        lcd.print("C"); // Print in the LCD the text "C"
        lcd.print("     "); // Print in the LCD the text "     "
      }

      // Get humidity event and print its value.
      dht.humidity().getEvent(&event); // Obtains the humidity value
      if (isnan(event.relative_humidity)) { // Checks if the humidity value is an error
        Serial.println(F("Error reading humidity!")); // Print in the serial monitor the text "Error reading humidity!"
      }
      else { // Checks if the humidity value is not an error
        Serial.print(F("Humidity: ")); // Print in the serial monitor the text "Humidity: "
        Serial.print(event.relative_humidity); // Prints in the serial monitor the humidity value
        Serial.println(F("%")); // Print in the serial monitor the text "%"

        lcd.setCursor(0, 1); // Sets the LCD's cursor to the second row of the LCD
        lcd.print("Humid: "); // Print in the LCD the text "Humid: "
        lcd.print(event.relative_humidity); // Prints in the LCD the humidity value
        lcd.print("%"); // Print in the LCD the text "%"
        lcd.print("     "); // Print in the LCD the text "     "
      }
    }
  }
  // Ultrasonic
  if (distPB2 == 1) { // Checks if the variable "distPB2" is equal to 1
    digitalWrite(trigPin, LOW); // Gives low voltage to pin 10
    delayMicroseconds(2); // Delays the program for 2 microseconds
    digitalWrite(trigPin, HIGH); // Give high voltage to pin 10
    delayMicroseconds(10); // Delays the program for 10 microseconds
    digitalWrite(trigPin, LOW); // Gives low voltage to pin 10

    duration = pulseIn(echoPin, HIGH); // Gives the variable "duration" the value of the length of time a high pulse is recieved by pin 13

    distance = (duration/2)*0.0343; // Gives the variable "distance" the product of the number 0.0343, and the quotient of the variable "duration" and 2

    Serial.print("Distance = "); // Print in the serial monitor the text "Distance = "
    
    if (distance >=400 || distance <= 2) { // Checks if the distance is greater than or equal 400 or less than or equal to 2
      Serial.println("Out of range"); // Prints in the serial monitor the text "Out of range"
      lcd.setCursor(0,0); // Sets the LCD's cursor to the first row of the LCD
      lcd.print("Out of range"); // Print in the LCD the text "Out of range"
      lcd.setCursor(0,1); // Sets the LCD's cursor to the second row of the LCD
      lcd.print("       "); // Print in the LCD the text "       "
    } else { // Checks if the distance is not greater than or equal 400 nor less than or equal to 2
      Serial.print(distance); // Prints in the serial monitor the distance value
      Serial.println(" cm"); // Prints in the serial monitor the text " cm"
      if (currentMillis - previousMillis >= interval) { // Checks if the difference of variables "currentMillis" and "previousMillis" is greater than or equal the variable "interval"
        previousMillis = currentMillis; // Gives the variable "previousMillis" the value of the variable "currentMillis"
        lcd.setCursor(0,0); // Sets the LCD's cursor to the first row of the LCD
        lcd.print("Distance:    "); // Prints in the LCD the text "Distance:    "
        lcd.setCursor(0,1); // Sets the LCD's cursor to the second row of the LCD
        lcd.print(distance); // Prints in the LCD the value of the variable "distance"
        lcd.print(" cm"); // Prints in the LCD the text " cm"
        lcd.print("     "); // Prints in the LCD the text "     "
      }
    }
  }
}
