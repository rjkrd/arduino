/**
 * Pinouts NodeMCU to...
 * 
 * RC522
 * 3v -> Vin
 * D1 -> RST
 * Gd -> GND
 * -- -> IRQ
 * D6 -> MISO
 * D7 -> MOSI
 * D5 -> SCK
 * D2 -> SDA
 */

#define SS_PIN 4  //D2
#define RST_PIN 5 //D1

#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;

void setup() 
{
  Serial.begin(115200);   // Initiate a serial communication
  delay(500);
  Serial.println("Initialising");
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  //94 6D B6 13

  if (content.substring(1) == "09 AE 3A 5A") //change UID of the card that you want to give access
  {
    Serial.println(" Access Granted ");
    delay(1000);
    Serial.println(" Have FUN ");
    Serial.println();
    statuss = 1;
  }
  
  else   {
    Serial.println(" Access Denied ");
    delay(3000);
  }
} 
