#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <EEPROM.h>
#include "RTClib.h"
RTC_DS1307 rtc;
const int RELAY_ENABLE1 = 13;
const int RELAY_ENABLE2 = 12;
#define SS_PIN 10    //Arduino Uno
#define RST_PIN 9
int EEPROMaddr=1 , totalRec=0,lightFlag=0;
int cardNo=0;

MFRC522 mfrc522(SS_PIN, RST_PIN);        // Create MFRC522 instance.
const int rs = 5, en = 3, d4 = 2, d5 = 16, d6 = 15, d7 = 14;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

MFRC522::MIFARE_Key key;
 
void setup()
{       
  pinMode(RELAY_ENABLE1, OUTPUT);
   pinMode(RELAY_ENABLE2, OUTPUT);
        Serial.begin(9600);        // Initialize serial communications with the PC
        SPI.begin();                // Init SPI bus
        mfrc522.PCD_Init();        // Init MFRC522 card
         lcd.begin(16, 2);
        lcd.print("Scan Your Card");
         if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);}
      totalRec =  EEPROM.read(0) ; 
      EEPROMaddr = totalRec*4+1;
}
void loop()
{
 
   //Look for new cards
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
  Serial.print("UID tag :");
  String content= "";
  byte letter; int pcardNo =0; int hh,mm,ss; 
 
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     Serial.println(" " );
     cardNo=mfrc522.uid.uidByte[i] ;
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  if ((cardNo !=pcardNo) && (cardNo != 115) ){
    if (lightFlag == 1) lightFlag = 0;
    else lightFlag = 1;
    
    if ( lightFlag == 1) {
        digitalWrite(RELAY_ENABLE1,LOW);
     }else 
        digitalWrite(RELAY_ENABLE1,HIGH);
      pcardNo = cardNo; 
   delay(1000);
    
 }
}
