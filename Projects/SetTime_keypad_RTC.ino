#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>
int r1 = 13, r2 = 12, r3 = 11, r4 = 10 ;
int c1 = 9, c2 = 8, c3 = 7 , c4 = 6 ;
const int rs = 5, en = 3, d4 = 2, d5 = 16, d6 = 15, d7 = 14;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
RTC_DS1307 rtc;
int sec = 0;
int currTime = 0;
int currentSec = 0;
int buzzer = 4 ;
bool activate = false, firstTime = true;

/* change this
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
  }

  // run the below line of code once , in order to adjust the Date and time
  //rtc.adjust(DateTime(2019,12, 2, 12, 21,00));
  pinMode(buzzer, OUTPUT);
  //Serial.println("Serial Keypad ex" ) ;
  // all rows as OUTPUT, columns as INPUT, make all Columns HIGH
  pinMode(r1, OUTPUT);  pinMode(r2, OUTPUT);  pinMode(r3, OUTPUT);   pinMode(r4, OUTPUT);
  pinMode(c1, INPUT);   pinMode(c2, INPUT);   pinMode(c3, INPUT);    pinMode(c4, INPUT);
  digitalWrite(c1, HIGH);  digitalWrite(c2, HIGH);  digitalWrite(c3, HIGH);  digitalWrite(c4, HIGH);

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
  lcd.print(' ');
  delay(200);
}

void keypad()
//make ROW1 as LOW, rest all rows HIGH and check all the corresponding columns
{
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
    DateTime t1 = rtc.now();
    currentSec = (t1.second());
    lcd.print(sec);
    lcd.print('=');
    lcd.print(currentSec, DEC);
    activate = true;
  }

  //make ROW2 as LOW, rest all rows HIGH and check all the corresponding columns
  digitalWrite(r1, HIGH);   digitalWrite(r2, LOW);  digitalWrite(r3, HIGH); digitalWrite(r4, HIGH);
  if (digitalRead(c1) == LOW) {
    sec = sec * 10 + 3;
    if ( sec<9){
      lcd.print("3");
    }else {
      lcd.print(sec);
    }
   
  }
  if (digitalRead(c2) == LOW) {
    
    sec = sec * 10 +  6;
    if ( sec<9){
      lcd.print("6");
    }else {
      lcd.print(sec);
    }
  }
  if (digitalRead(c3) == LOW) {
    sec =  sec * 10 + 9;
    if ( sec<9){
      lcd.print("9");
    }else {
      lcd.print(sec);
    }
    
  }
  if (digitalRead(c4) == LOW) {
    lcd.print("-");

  }

  //make ROW3 as LOW, rest all rows HIGH and check all the corresponding columns
  digitalWrite(r1, HIGH);   digitalWrite(r2, HIGH);  digitalWrite(r3, LOW); digitalWrite(r4, HIGH);
  if (digitalRead(c1) == LOW) {
    sec =  sec * 10 + 2;
    if ( sec<2){
      lcd.print("2");
    }else {
      lcd.print(sec);
  }
  if (digitalRead(c2) == LOW) {
    sec =  sec * 10 + 5;
    if ( sec<5){
      lcd.print("5");
    }else {
      lcd.print(sec);
  }
  if (digitalRead(c3) == LOW) {
    sec =  sec * 10 + 8;
    if ( sec<8){
      lcd.print("8");
    }else {
      lcd.print(sec);
  }
  if (digitalRead(c4) == LOW) {
    lcd.print("0");

  }

  //make ROW4 as LOW, rest all rows HIGH and check all the corresponding columns
  digitalWrite(r1, HIGH);   digitalWrite(r2, HIGH);  digitalWrite(r3, HIGH); digitalWrite(r4, LOW);
  if (digitalRead(c1) == LOW) {
    sec =  sec * 10 + 1;
    if ( sec<1){
      lcd.print("1");
    }else {
      lcd.print(sec);

  }
  if (digitalRead(c2) == LOW) {
    sec =  sec * 10 + 4;
    if ( sec<4){
      lcd.print("4");
    }else {
      lcd.print(sec);
  }
  if (digitalRead(c3) == LOW) {
    sec =  sec * 10 + 7;
    if ( sec<7){
      lcd.print("7");
    }else {
      lcd.print(sec);
  }
  if (digitalRead(c4) == LOW) {
    lcd.print("C");

  }
  delay(500);
}
void loop()
{
  showTime();
  
    lcd.setCursor(0, 1);
    lcd.print("Set Time:");
  
  keypad();
  DateTime t2 = rtc.now();
  currTimeS = (t2.second());
  currTimeM = (t2.minute());

  if ((activate == true ) && ( currTimeS > (currentSec + sec) ) )
  {
    lcd.print("over");
    //digitalWrite ( buzzer , 1) ; delay(1000); digitalWrite ( buzzer , 0) ; delay(1000);
    activate = false;
    lcd.clear();
   
  }

}
