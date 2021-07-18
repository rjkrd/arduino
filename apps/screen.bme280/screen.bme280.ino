#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define DHTTYPE DHT11
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
uint8_t DHTPin = D7; 
DHT dht(DHTPin, DHTTYPE);
Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(100);
  
  Serial.println("BME280 Test");
  bool status;
  // default settings
  status = bme.begin();
  if (!status) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      while (1);
  }
  Serial.println("BME280 Set");

  pinMode(DHTPin, INPUT);
  dht.begin();  
    
  Serial.println("SSD1306 Test");
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  Serial.println("SSD1306 Set");
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("Hello World");
  display.display(); 
  delay(100);
 
}

void loop() {
  float Temp = bme.readTemperature();
  float Humid = bme.readHumidity();
  float mbPress = bme.readPressure()/100;
  float Temperature = dht.readTemperature(); // Gets the values of the temperature
  float Humidity = dht.readHumidity(); // Gets the values of the humidity 
  
  
  Serial.print("Temperature: ");
  Serial.print(Temp);
  Serial.println("c");
    
  Serial.print("Humidity: ");
  Serial.print(Humid);
  Serial.println("%");
  
  Serial.print("Pressure: ");
  Serial.print(mbPress);
  Serial.println("mB");

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Hello World");
  display.println("");

  display.print("Temperature: ");
  display.print(Temperature);
  display.println("c");
    
  display.print("Humidity: ");
  display.print(Humidity);
  display.println("%");
  display.println("");
  
  display.print("Temperature: ");
  display.print(Temp);
  display.println("c");
    
  display.print("Humidity: ");
  display.print(Humid);
  display.println("%");
  
  display.print("Pressure: ");
  display.print(mbPress);
  display.println("mB");
        
  display.display(); 
  

  
  delay(15000);
}
