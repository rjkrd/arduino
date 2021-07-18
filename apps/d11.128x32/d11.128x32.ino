/**
 * Pinouts NodeMCU to...
 * 
 * D11 
 * 3v -> +
 * D7 -> OUT 
 * Gd -> -
 * 
 * 1306
 * 3v -> VCC
 * Gd -> GND
 * D1 -> SCL
 * D2 -> SDA
 */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     LED_BUILTIN // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11

uint8_t DHTPin = D7;
DHT dht(DHTPin, DHTTYPE);

float Temperature = 0;
float Humidity = 0;
bool top = true;

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  delay(1000);

  pinMode(DHTPin, INPUT);
  dht.begin();
  
  Serial.println("Set Up");
}

void loop() {
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  
  Serial.print("Temperature = ");
  Serial.println(Temperature);
  Serial.print("Humidity = ");
  Serial.println(Humidity);

  display.clearDisplay();
  display.setCursor(0, 0);
  if(!top){
    display.println("");
  } 
  top = !top;
  display.print("Temperature: ");
  display.print(Temperature);
  display.println("c");
  display.println("");
  display.print("Humidity:    ");
  display.print(Humidity);
  display.println("%");
  display.display();
  
  delay(30000);                       // wait 30 seconds
}
