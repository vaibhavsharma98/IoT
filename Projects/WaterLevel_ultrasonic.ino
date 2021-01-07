#include<EEPROM.h>
#define trigPin  7
#define echoPin 8
const int ultrasonic= 7; //only Read
long duration;
int distance_cm,distance_inch;
int relay1 = 9;
int relay2 = 12;
int st=-1;
void setup() {
  Serial.begin(9600);
   
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
 }
void loop() {
  st = EEPROM.read(10);
   //Serial.print(st);
   delay(1000);
  digitalWrite(trigPin,LOW);
   delayMicroseconds(2);
   //trigPin HIGH for 10 u sec
   digitalWrite(trigPin,HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin,LOW);
   
   duration=pulseIn(echoPin,HIGH);//reads echoPin
   distance_cm=duration*0.034/2; //calculate distance
   distance_inch=duration*0.0133/2;
  
  
  if (((distance_cm)<=30)&&((distance_cm)>=0))
  {
    st=1;
    EEPROM.write(10,1);
    digitalWrite(relay2,LOW);
    delay(2000);
}
 else if((distance_cm)>=30)
 {
  digitalWrite(relay2,HIGH);
    delay(2000);
 }
  else if((distance_cm)>=70)
  {
    st=0;
    EEPROM.write(10,0);
  }
   if(st==1)
  {
    digitalWrite(relay1,LOW);
    Serial.println("low");
  }
  else if(st==0)
  {
    digitalWrite(relay1,HIGH);
    Serial.println("high");
  }
}
