#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
  Serial.println(""); 

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
 
  Serial.println("WiFi Netwoek Scan Started");
}

void loop() {
  int n = WiFi.scanNetworks();
   
  Serial.println("Scan done");
  
  if (n == 0)
    Serial.println("No Networks Found");
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
      Serial.print(WiFi.RSSI(i))
      ;
      Serial.print(") MAC:");
      Serial.print(WiFi.BSSIDstr(i));
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" Unsecured":" Secured");
      delay(10);
    }
  }
  Serial.println("");
  delay(60000);
}
