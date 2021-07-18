/**
 * Pinouts NodeMCU to...
 * 
 * RC522 (changed from 'default')
 * 3v -> Vin
 * D3 -> RST
 * Gd -> GND
 * -- -> IRQ
 * D6 -> MISO
 * D7 -> MOSI
 * D5 -> SCK
 * D4 -> SDA
 * 
 * 1306
 * 3v -> VCC
 * Gd -> GND
 * D1 -> SCL
 * D2 -> SDA
 */

#define SS_PIN 2  //D4 was 4 //D2
#define RST_PIN 0 //D3 was 5 //D1

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 //    LED_BUILTIN // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int buzzer = 16;//the pin of the active buzzer
int melody[] = { 523, 587, 659, 698, 784, 880, 988, 1047 };
//  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6 
int duration = 500;  // 500 miliseconds

void setup() 
{
  Serial.begin(115200);   // Initiate a serial communication

  Serial.println("Initialising");

  pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
//  display.display();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  
  delay(500);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("");
  display.println("");
  display.println("Scanning...");
  display.display();
  display.display();
}

void loop() 
{
  // Look for new cards
  if ( mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() ) 
  {
    //get tag
    bool access = false;
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
       content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    

    //Show Details on screen
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("UID tag:");
    display.println(content);
    if (content.substring(1) == "09 AE 3A 5A" || content.substring(1) == "C5 4C 76 8A" ) //change UID of the card that you want to give access
    {
      display.println(" Access Granted ");
      delay(1000);
      display.println(" Have FUN ");
      access = true;
    } else {
      display.println(" Access Denied ");
      delay(1000);
      display.println(" Try again ");
    }
    display.display();
  
    //Show UID on serial monitor
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
    Serial.print("UID tag:");
    Serial.print(content);
    Serial.println();
    if (content.substring(1) == "09 AE 3A 5A" || content.substring(1) == "C5 4C 76 8A" ) //change UID of the card that you want to give access
    {
      Serial.println(" Access Granted ");
      Serial.println(" Have FUN ");
      Serial.println();
    } else {
      Serial.println(" Access Denied ");
    }

//    unsigned char i;
//    if(access){
//      for (int thisNote = 0; thisNote < 8; thisNote++) 
//      {
//        tone(buzzer, melody[thisNote], duration);
//        delay(200);
//      }
//    } else {
//      for (int thisNote = 7; thisNote >= 0; thisNote--) 
//      {
//        tone(buzzer, melody[0], duration);
//        delay(200);
//      }
//    }
    
    delay(2000);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("");
    display.println("");
    display.println("Scanning...");
    display.display();
  }
} 
