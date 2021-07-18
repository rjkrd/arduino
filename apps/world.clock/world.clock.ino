#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/***************************
 * Begin Settings
 **************************/
// WIFI
const char* WIFI_SSID = "ssid";
const char* WIFI_PWD = "password";

/***************************
 * End Settings
 **************************/
String timeZoneIds [] = {"America/New_York", "Europe/London", "Europe/Paris", "Australia/Sydney"};

// flag changed in the ticker function every 10 minutes
bool readyForUpdate = false;

String lastUpdate = "--";


void setup() {
  Serial.begin(115200);
  
  WiFi.begin(WIFI_SSID, WIFI_PWD);

  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("Connected to WiFi");
  display.println(WIFI_SSID);
    display.println("Connected to WiFi");
  display.println(WIFI_SSID);
    display.println("Connected to WiFi");
  display.println(WIFI_SSID);
    display.println("Connected to WiFi");
  display.println(WIFI_SSID);
    display.println("Connected to WiFi");
  display.println(WIFI_SSID);
  display.display(); 
  delay(100);
}

void loop() {


}
