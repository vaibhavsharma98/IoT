#include<LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;

int rs = 5 , e = 3, d4 = 2, d5 = 16, d6 = 15, d7 = 14;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
int r1 = 13, r2 = 12, r3 = 11, r4 = 10 ;
int c1 = 9, c2 = 8, c3 = 7 , c4 = 6 ;
/*
   0 1 2 3
   4 5 6 7
   8 9 A B
   C D E F
*/

void setup()
{ lcd.begin(16, 2); 
Serial.begin(9600);
    if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  // all rows as OUTPUT, columns as INPUT, make all Columns HIGH
  pinMode(r1, OUTPUT);  pinMode(r2, OUTPUT);  pinMode(r3, OUTPUT);   pinMode(r4, OUTPUT);
  pinMode(c1, INPUT);   pinMode(c2, INPUT);   pinMode(c3, INPUT);    pinMode(c4, INPUT);
  digitalWrite(c1, HIGH);  digitalWrite(c2, HIGH);  digitalWrite(c3, HIGH);  digitalWrite(c4, HIGH);
  
}
}
//rtc.adjust(DateTime(2019,11, 26, 02, 29,10));

void loop() 
{
  keypad();
  showTime();
}
void showTime()
{
  lcd.setCursor(0, 0);
  DateTime now = rtc.now();
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
   delay(2000);
}
void keypad() {
 lcd.begin(16, 2); 
lcd.setCursor(0, 1);
lcd.print("Set Time:" ) ;
 //make ROW1 as LOW, rest all rows HIGH and check all the corresponding columns
  digitalWrite(r1, LOW);   digitalWrite(r2, HIGH);  digitalWrite(r3, HIGH); digitalWrite(r4, HIGH);
  if (digitalRead(c1) == LOW) {
    lcd.print("H");
    
  }
  if (digitalRead(c2) == LOW) {
    lcd.print("M");
     
  }
  if (digitalRead(c3) == LOW) {
    lcd.print("S");
     
  }
  if (digitalRead(c4) == LOW) {
    lcd.print("E");
     
  }

  //make ROW2 as LOW, rest all rows HIGH and check all the corresponding columns
  digitalWrite(r1, HIGH);   digitalWrite(r2, LOW);  digitalWrite(r3, HIGH); digitalWrite(r4, HIGH);
  if (digitalRead(c1) == LOW) {
    lcd.print("3");
     
  }
  if (digitalRead(c2) == LOW) {
    lcd.print("6");
     
  }
  if (digitalRead(c3) == LOW) {
    lcd.print("9");
     
  }
  if (digitalRead(c4) == LOW) {
    lcd.print("-");
     
  }

  //make ROW3 as LOW, rest all rows HIGH and check all the corresponding columns
  digitalWrite(r1, HIGH);   digitalWrite(r2, HIGH);  digitalWrite(r3, LOW); digitalWrite(r4, HIGH);
  if (digitalRead(c1) == LOW) {
    lcd.print("2");
     
  }
  if (digitalRead(c2) == LOW) {
    lcd.print("5");
     
  }
  if (digitalRead(c3) == LOW) {
    lcd.print("8");
     
  }
  if (digitalRead(c4) == LOW) {
    lcd.print("0");
      
  }

  //make ROW4 as LOW, rest all rows HIGH and check all the corresponding columns
  digitalWrite(r1, HIGH);   digitalWrite(r2, HIGH);  digitalWrite(r3, HIGH); digitalWrite(r4, LOW);
  if (digitalRead(c1) == LOW) {
    lcd.print("1");
      
  }
  if (digitalRead(c2) == LOW) {
    lcd.print("4");
      
  }
  if (digitalRead(c3) == LOW) {
    lcd.print("7");
      
  }
  if (digitalRead(c4) == LOW) {
    lcd.print("C");
      
  }
  delay(1000);
}
