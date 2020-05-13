int buttonPin1 = 7;
int buttonPin2 = 8;
int LED[4] = {13,12,11,10}

void setup()
{
pinMode(buttonPin1, INPUT);
pinMode(buttonPin2, INPUT);
for( int cnt=0 ; cnt<4; cnt++){
    pinMode (LED[cnt], OUTPUT);  
  }
}

void loop()
{
if digitalRead(buttonPin1==HIGH)
{
for( int cnt=0 ; cnt<4; cnt++)
{
digitalWrite(LED[cnt],HIGH)
delay(1000);
digitalWrite(LED[cnt],LOW)
}
}
}
