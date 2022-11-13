/*
  LCD DHT11

  This program reads the temperature and humidity value sensed by the DHT11 sensor

  This program makes use of #include, Adafruit_Sensor.h, DHT.h, DHT_U.h, LiquidCrystal.h, #define, DHT_Unified, dht, uint32_t, const, int, LiquidCrystal, lcd, byte, Serial.begin, dht.begin, Serial.printl, dht.temperature, 
  dht.humidity, getSensor, sensor.min_delay, lcd.begin, lcd.createChar, delay, sensors_event_t, getEvent, if, else, lcd.setCursor, lcd.print, and lcd.write.
*/

#include <Adafruit_Sensor.h> // Initialize the Adafruit unified sensor library
#include <DHT.h> // Initialize the DHT sensor library
#include <DHT_U.h> // Initialize the DHT sensor library

#include <LiquidCrystal.h> // Initialize the liquid crystal library

#define DHTPIN 7 // Defines pin 7 as the Arduino pin connected to the DHT sensor

#define DHTTYPE    DHT11     // Defines DHT11 as the DHT sensor used in the circuit

// Initializes Arduino pin 7 as the pin connected to the DHT11 sensor
DHT_Unified dht(DHTPIN, DHTTYPE);

// Creates an unisgned 32 bit integer variable called "delayMS"
uint32_t delayMS;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // Creates variables to make it easier to identify Liquid Crystal pins by associating them with Arduino Pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Initialize the Arduino pins as LiquidCrystal pins

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

void setup() {
  Serial.begin(9600); // Sets the data rate in bits per second (baud) for serial data transmission
  dht.begin(); // Begins the DHT11 sensor
  
  // Print temperature sensor details
  Serial.println(F("DHTxx Unified Sensor Example"));
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
 
  // Print humidity sensor details.=
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
 
  delayMS = sensor.min_delay / 1000; // Set delay between sensor readings based on sensor details
  
  lcd.begin(16, 2); // Set up the LCD's number of columns and rows
  lcd.createChar(0, degreesChar); // Creates character 0 and gives it the pixel data of the byte called "degreesChar"
}

void loop() {
  delay(delayMS); // Delay between measurements
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