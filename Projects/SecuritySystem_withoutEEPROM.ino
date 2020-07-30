#include<LiquidCrystal.h>
const int rs=5, en=3, d4=6, d5=7, d6=8, d7=9;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
int r1=10 , r2=11, r3=12, r4=13;
int c1=A1, c2=A2, c3=A3, c4=A4;

/*
* 1 2 3 A
* 4 5 6 B
* 7 8 9 C
* * 0 # D
*/
int n;
int pass = 231;
void setup()
{
  Serial.begin(9600);
 lcd.begin(16,2);
 lcd.setCursor(3,0);
 lcd.print("LCD Keypad");
 pinMode(r1,OUTPUT); pinMode(r2,OUTPUT); pinMode(r3,OUTPUT); pinMode(r4,OUTPUT);
 pinMode(c1,INPUT); pinMode(c2,INPUT); pinMode(c3,INPUT); pinMode(c4,INPUT);
 digitalWrite(c1,HIGH); digitalWrite(c2,HIGH); digitalWrite(c3,HIGH); digitalWrite(c4,HIGH);
  lcd.setCursor(0,1);
}
void loop()
{
  Serial.println(n);
  Serial.println(pass);
digitalWrite(r1,LOW); digitalWrite(r2,HIGH); digitalWrite(r3,HIGH); 
digitalWrite(r4,HIGH);
  if(digitalRead(c1)==LOW){ n=n*10 +1; lcd.print("1"); delay(300);}
  if(digitalRead(c2)==LOW) {n=n*10 +2; lcd.print("2"); delay(300); }
  if(digitalRead(c3)==LOW) {n=n*10 +3; lcd.print("3"); delay(300); }
  if(digitalRead(c4)==LOW) { lcd.print("A"); n=0; delay(300); }
  
  digitalWrite(r1,HIGH); digitalWrite(r2,LOW); digitalWrite(r3,HIGH); 
digitalWrite(r4,HIGH);
 if(digitalRead(c1)==LOW){ lcd.print("4"); delay(300);}
  if(digitalRead(c2)==LOW) {
     digitalWrite(r1,LOW); digitalWrite(r2,HIGH); digitalWrite(r3,HIGH); 
     digitalWrite(r4,HIGH);
  if(digitalRead(c1)==LOW){ n=n*10 +1; lcd.print("1"); delay(300);}
  if(digitalRead(c2)==LOW) {n=n*10 +2; lcd.print("2"); delay(300); }
  if(digitalRead(c3)==LOW) {n=n*10 +3; lcd.print("3"); delay(300); }
    pass=n;  
    lcd.print("Pass change"); delay(300); }
  if(digitalRead(c3)==LOW) { lcd.clear(); delay(300); }
  if(digitalRead(c4)==LOW) { 
    if(n==pass)
    {lcd.clear();
     lcd.print("pass correct");
    }
    else
    {
      lcd.clear();
      lcd.print("pass Incorrect");
                }
  }
 digitalWrite(r1,HIGH); digitalWrite(r2,HIGH); digitalWrite(r3,LOW); 
digitalWrite(r4,HIGH);
  if(digitalRead(c1)==LOW){ pass=n; lcd.print("pass saved");
        lcd.clear(); delay(300);}
  
  }
