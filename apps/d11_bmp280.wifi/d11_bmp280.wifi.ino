#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
 
#define DHTTYPE DHT11   // DHT 11
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)

/*Put your SSID & Password*/
const char* ssid = "ssid";  // Enter SSID here
const char* password = "password";  //Enter Password here

ESP8266WebServer server(80);

// DHT Sensor
uint8_t DHTPin = D7; 
               
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

Adafruit_BME280 bme;

float Temperature;
float Humidity;
 
void setup() 
{
  Serial.begin(115200);
  delay(100);
  
  pinMode(DHTPin, INPUT);

  dht.begin();  

  Serial.println("BME280 test");
  bool status;
  // default settings
  status = bme.begin();
  if (!status) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
 //     while (1);
  }

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() 
{
  server.handleClient();
}

void handle_OnConnect() 
{

  float Temp = bme.readTemperature();
  float Humid = bme.readHumidity();
  float mbPress = bme.readPressure()/100;
  float Alti = bme.readAltitude(SEALEVELPRESSURE_HPA);
  
  Serial.print("Temperature:");
  Serial.println(Temp);
  Serial.print("Humidity:");
  Serial.println(Humid);
  Serial.print("Pressure:");
  Serial.println(mbPress);
  Serial.print("Altitude:");
  Serial.println(Alti);


  
  
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  
  server.send(200, "text/html", SendHTML(Temperature,Humidity,Temp,Humid,mbPress)); 
  
  Serial.print("Temperature:");
  Serial.println(Temperature);
  Serial.print("Humidity:");
  Serial.println(Humidity);


  
}

void handle_NotFound()
{
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat,float Humiditystat,float Tempstat,float Humidstat,float Pressstat)
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>ESP8266 Weather Report</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>ESP8266 NodeMCU Weather Report</h1>\n";



  ptr +="<h2>BME280</h2>";
  ptr +="<p>Temperature: ";
  ptr +=Tempstat;
  ptr +="&#8451;</p>";
  ptr +="<p>Humidity: ";
  ptr +=Humidstat;
  ptr +="%</p>";
  ptr +="<p>Presure: ";
  ptr +=Pressstat;
  ptr +="mb</p>";
  
  ptr +="<h2>DHT11</h2>";
  ptr +="<p>Temperature: ";
  ptr +=Temperaturestat;
  ptr +="&#8451;</p>";
  ptr +="<p>Humidity: ";
  ptr +=(int)Humiditystat;
  ptr +="%</p>";
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
