int buttonPin1=7 , buttonPin2 = 8;  
int LED[4]= {13,12,11,10};

void setup() {
  Serial.begin(9600);
  pinMode (buttonPin1, INPUT);
  pinMode (buttonPin2, INPUT);
  for( int cnt=0 ; cnt<4; cnt++){
    pinMode (LED[cnt], OUTPUT);  
  }
}
int count = 0; 
int go = 0;
int come = 0 ;
void loop() {
  // inc button
  if (digitalRead(buttonPin1) == HIGH)  {
     count++;
    if (count<5) 
    {
      go = count;
   Serial.print("go=");
    Serial.print(go);
      
    }
    else if (count<9) 
      { come = count;
       Serial.print("come=");
    Serial.print(come);
       go=0;
      }
    else if (count>8)
    {count = go;
    }
    while(digitalRead(buttonPin1) == HIGH); 
  }
  
 
   for(int i=0 ; i<go; i++) 
   {
   digitalWrite(LED[i],HIGH);
     
   }
   
     for(int i= come ; i<=8; i++)
     {
      digitalWrite(LED[8-come],LOW);
            }
}
