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
  if (digitalRead(BUT1) == HIGH)  {
    if (count<4) count++; 
    while(digitalRead(BUT1) == HIGH); 
  }
  //dec
   if (digitalRead(BUT2) == HIGH)  {
    if (count>0)count--; 
    while(digitalRead(BUT2) == HIGH); 
  }

  
   
}
