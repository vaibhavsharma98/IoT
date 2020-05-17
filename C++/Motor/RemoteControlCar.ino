const int forward = 4;
const int backward = 5;
const int right = 6;
const int left = 7;
void setup()
{ 
   pinMode(4,INPUT);
   pinMode(5,INPUT);
   pinMode(6,INPUT);
   pinMode(7,INPUT);
  
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  
}

void loop()
{
  if (digitalRead(forward)==HIGH)
  {
  digitalWrite(2, HIGH); //clockwise
  digitalWrite(3,LOW);
  digitalWrite(8, HIGH); //clockwise
  digitalWrite(9,LOW);
  }
  else if (digitalRead(backward)==HIGH)
  {
  digitalWrite(2, LOW); //anti-clockwise
  digitalWrite(3,HIGH);
  digitalWrite(8, LOW); //anti-clockwise
  digitalWrite(9,HIGH); 
  }
    
  else if(digitalRead(right)==HIGH)
  {
  digitalWrite(2, HIGH); //clockwise
  digitalWrite(3,LOW);
   digitalWrite(8, LOW); //anti-clockwise
  digitalWrite(9,HIGH);
  }
  
  else if (digitalRead(left)==HIGH)
  {
  digitalWrite(8, HIGH); //clockwise
  digitalWrite(9,LOW);
  digitalWrite(2, LOW); //anti-clockwise
  digitalWrite(3,HIGH);
  }
}
