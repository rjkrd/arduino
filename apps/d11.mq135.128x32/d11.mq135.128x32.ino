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
 * 
 * MQ135
 * 3v -> VCC
 * Gd -> GND
 * A0 -> A0
 */

 /*
  * Set up Screen
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


/*
 * Set up temp
 */
#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11

uint8_t DHTPin = D7;
DHT dht(DHTPin, DHTTYPE);

float Temperature = 0;
float Humidity = 0;

/*
 * Set up air quality 
 */
#include <MQUnifiedsensor.h>

#define board  "ESP8266"
#define Voltage_Resolution 3.3
#define ADC_Bit_Resolution 10 
#define type "MQ-135"
#define pin A0
#define RatioMQ135CleanAir 3.6


MQUnifiedsensor MQ135(board, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

float CO = 0;
float Alcohol = 0;
float CO2 = 0;
float Tolueno = 0;
float NH4 = 0;
float Acetona = 0;


void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setRotation(2);      // rotated 180
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  delay(1000);
  
  pinMode(DHTPin, INPUT);
  dht.begin();

  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ135.init(); 
  Serial.print("Calibrating air quality please wait.");
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ135.update(); // Update data, the arduino will be read the voltage on the analog pin
    calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    Serial.print(".");
  }
  MQ135.setR0(calcR0/10);
  if(isinf(calcR0)) {Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your wiring and supply"); while(1);}
  if(calcR0 == 0){Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please check your wiring and supply"); while(1);}

  Serial.println("Set Up");
}

void loop() {
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 

  MQ135.update();

  MQ135.setA(605.18); MQ135.setB(-3.937); // Configurate the ecuation values to get CO concentration
  CO = MQ135.readSensor();
  MQ135.setA(77.255); MQ135.setB(-3.18); // Configurate the ecuation values to get Alcohol concentration
  Alcohol = MQ135.readSensor();
  MQ135.setA(110.47); MQ135.setB(-2.862); // Configurate the ecuation values to get CO2 concentration
  CO2 = MQ135.readSensor();
  MQ135.setA(44.947); MQ135.setB(-3.445); // Configurate the ecuation values to get Tolueno concentration
  Tolueno = MQ135.readSensor();
  MQ135.setA(102.2 ); MQ135.setB(-2.473); // Configurate the ecuation values to get NH4 concentration
  NH4 = MQ135.readSensor();
  MQ135.setA(34.668); MQ135.setB(-3.369); // Configurate the ecuation values to get Acetona concentration
  Acetona = MQ135.readSensor();
  
  Serial.print("Temperature = ");
  Serial.println(Temperature);
  Serial.print("Humidity = ");
  Serial.println(Humidity);
  Serial.print("|CO "); Serial.print(CO); 
  Serial.print("|Alc "); Serial.print(Alcohol); 
  Serial.print("|CO2 "); Serial.print(CO2); 
  Serial.print("|Tol"); Serial.print(Tolueno); 
  Serial.print("|NH4 "); Serial.print(NH4); 
  Serial.print("|Ace "); Serial.print(Acetona);
  Serial.println("|"); 
  
  int sensorValue = analogRead(0); // Read analog input pin A0
  Serial.print("|Val "); Serial.print(sensorValue); 
  Serial.println("|"); 

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temperature: ");
  display.print(Temperature);
  display.println("c");
  display.print("Humidity:    ");
  display.print(Humidity);
  display.println("%");
  display.print("Air Quality: ");
  display.print(sensorValue);
  display.println("PPM");

  display.print("C02: ");
  display.print(CO2);
  display.print(" NH4: ");
  display.print(NH4);
  display.display();
  
  delay(30000);                       // wait 30 seconds
}
