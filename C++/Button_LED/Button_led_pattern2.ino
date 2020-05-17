int buttonPin1=7 , buttonPin2 = 8;  
int LED[4]= {13,12,11,10};

void setup() {
  for( int cnt=0 ; cnt<4; cnt++){
    pinMode (LED[cnt], OUTPUT);  
  }
}
int count = 0; 
void loop() {
  // inc button
  if (digitalRead(buttonPin1) == HIGH)  {
    if (count<4) count++; 
    while(digitalRead(butttonPin1) == HIGH); 
  }
  //dec
   if (digitalRead(buttonPin2) == HIGH)  {
    if (count>0)count--; 
    while(digitalRead(buttonPin2) == HIGH); 
  }
 
  // switch on only required LEDs
   for(int i=0 ; i<count; i++) digitalWrite(LED[i],HIGH);
     // switch off rest of  LEDs
     for(int i= count ; i<4; i++) digitalWrite(LED[i],LOW);
   
}
  
   

