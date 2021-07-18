#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
 
const char *ssid = "ssid";
const char *password = "password";
 
//Web address to read from
const char *host = "api.thingspeak.com";
String apiKey = "apikey";
//=======================================================================
//                    Power on setup
//=======================================================================
 
void setup() {
  delay(1000);
  Serial.begin(115200);
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); 
  Serial.println("");
 
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}
 
void loop() {
  WiFiClient client;          
  const int httpPort = 80;

 if(!client.connect(host, httpPort)){
   Serial.println("Connection Failed");
   delay(300);
   return;
 }
 
  String ADCData;
  int adcvalue=random(0, 20);
  ADCData = String(adcvalue);
  Serial.println(ADCData);
  String Link="GET /update?api_key="+apiKey+"&field1=";
  Link = Link + ADCData;
  Link = Link + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n";                
  client.print(Link);
  delay(100);

 int timeout=0;
 while((!client.available()) && (timeout < 1000))     //Wait 5 seconds for data
 {
   delay(10); 
   timeout++;
 }

 if(timeout < 500)
 {
     while(client.available()){
        Serial.println(client.readString()); //Response from ThingSpeak       
     }
 }
 else
 {
     Serial.println("Request timeout..");
 }
 
 delay(5000);  //Read Web Page every 5 seconds
}
