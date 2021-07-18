#include <SPI.h>
#include <Wire.h>

#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11

uint8_t DHTPin = 13;
DHT dht(DHTPin, DHTTYPE);

float Temperature = 0;
float Humidity = 0;

void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(DHTPin, INPUT);

  dht.begin();
  Serial.println("...");
  Serial.println("Set Up");
}

void loop() {
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  Serial.print("Temperature = ");
  Serial.println(Temperature);
  Serial.print("Humidity = ");
  Serial.println(Humidity);
  delay(30000);                       // wait for a second
}
