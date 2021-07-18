/**
 * Pinouts NodeMCU to...
 * 
 * 1306
 * 3v -> VCC
 * Gd -> GND
 * D1 -> SCL
 * D2 -> SDA
 */
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     LED_BUILTIN // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  Serial.begin(115200);
  Serial.println(""); 

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
 
  Serial.println("WiFi Network Scan Started");
}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);
  
  int n = WiFi.scanNetworks();  
  Serial.println("Scan done");

  if (n == 0) {
    Serial.println("No Networks Found");
    display.print("No Networks Found");
  }
  else
  {
    Serial.print(n);
    Serial.println(" Networks found");
    for (int i = 0; i < n; ++i)
    {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(") MAC:");
      Serial.print(WiFi.BSSIDstr(i));
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" Unsecured":" Secured");
      delay(10);
    }
    
    display.println("****Wifi Scanner****");
    int show = (n > 7) ? 7 : n; 
    for (int i = 0; i < show; ++i)
    {
      display.print(i + 1);
      display.print(": ");
      display.print(WiFi.SSID(i));
      display.print(" (");
      display.print(WiFi.RSSI(i));
      display.print(")");
      display.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" O":" S");
    }  
  }

  
  display.display();
  Serial.println("");
  delay(60000);
}
