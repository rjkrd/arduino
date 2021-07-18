#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1029)

Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(100);
  
  Serial.println("BME280 test");
  bool status;
  // default settings
  status = bme.begin();
  if (!status) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      while (1);
  }
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  
  float Temp = bme.readTemperature();
  float Humid = bme.readHumidity();
  float mbPress = bme.readPressure()/100;
  float Alti = bme.readAltitude(SEALEVELPRESSURE_HPA);
  
  Serial.print("Temperature: ");
  Serial.print(Temp);
  Serial.println("c");
    
  Serial.print("Humidity: ");
  Serial.print(Humid);
  Serial.println("%");
  
  Serial.print("Pressure: ");
  Serial.print(mbPress);
  Serial.println("mB");
//  Serial.print("Altitude:");
//  Serial.println(Alti);
  delay(1000); 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(29000);                       // wait for a second
}
