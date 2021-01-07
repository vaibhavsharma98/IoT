long duration1; 
long duration2; 
 
//int distance_cm1,distance_cm2;
int ledPin = 8; // Out for light 
//int currentState =-1;
//int previousState = 0;
int timer1=0,timer2=0;
int pin_t1=13, pin_e1=12;
int pin_t2=11, pin_e2=10;
long ultra_time;
int cnt=0;
long dis_a=0,dis_b=0;
int flag1=0, flag2=0;
int person = 0; 
bool entry_flag2=0,entry_flag1=0;
unsigned long previousTime =0;
unsigned long timeInterval =5000;
unsigned long currentTime= millis();
void setup(){
Serial.begin(9600);
pinMode(5,OUTPUT);
pinMode(ledPin, OUTPUT);
////////////////////////////////
  pinMode(pin_t1,OUTPUT);
  pinMode(pin_e1,INPUT);
  pinMode(pin_t2,OUTPUT);
  pinMode(pin_e2,INPUT);

Serial.print("     Welcome    ");
}

bool dis1_flag=0;
bool dis2_flag=0;
int count=0;
void loop(){ 
  int dis1=distance1();
  int dis2=distance2();
  Serial.print(dis1);
  Serial.print("\t");
  Serial.print(dis2);
  Serial.print("\t");
  
  Serial.print(dis1_flag);
  Serial.print("\t");
  Serial.print(dis2_flag);
  Serial.print("\t");
  Serial.println(count);
  
  Serial.println("");
  delay(10);

  if(dis1<70){dis1_flag=1;}
  if(dis2<70){dis2_flag=1;}
  if((dis1_flag==1)&&(entry_flag1==0)){
    entry_flag2=1;
        Serial.println("step1");   
        
    if(dis2_flag==1)
    {
      
        Serial.println("step2"); 
      if(distance2()>50)
      {
      Serial.println("step3"); 
      count++;
      dis1_flag=0;
      dis2_flag=0;
      entry_flag2=0;
      delay(10);
      }
    
    }
    if(millis() - previousTime > timeInterval) 
    {
      dis1_flag=0;
      dis2_flag=0;
      Serial.print("out");
      delay(500);
      previousTime=millis(); 
    }
   
  }
  
  if((dis2_flag==1)&&(entry_flag2==0)){
    entry_flag1=1;
        Serial.println("step4"); 
    if(dis1_flag==1)
    {
      
        Serial.println("step5"); 
      if(distance1()>50)
      {
        
        Serial.println("step6"); 
      count--;
      dis1_flag=0;
      dis2_flag=0;
      delay(10);
        entry_flag1=0;
      }
    }
    if(millis() - previousTime > timeInterval)
    {
      dis1_flag=0;
      dis2_flag=0;
      Serial.print("in");
      delay(500);
      previousTime=millis(); 
    }
  }
}
int distance1()
{
    digitalWrite(pin_t1,LOW);
    delayMicroseconds(2);
   //trigPin HIGH for 10 u sec
   digitalWrite(pin_t1,HIGH);
   delayMicroseconds(10);
   digitalWrite(pin_t1,LOW);
   
   duration1=pulseIn(pin_e1,HIGH);//reads echoPin
  int distance_cm1=duration1*0.034/2; //calculate distance
  return distance_cm1;
}


int distance2()
{
   digitalWrite(pin_t2,LOW);
   delayMicroseconds(2);
   //trigPin HIGH for 10 u sec
   digitalWrite(pin_t2,HIGH);
   delayMicroseconds(10);
   digitalWrite(pin_t2,LOW);
   
   duration2=pulseIn(pin_e2,HIGH);//reads echoPin
   int distance_cm2=duration2*0.034/2; //calculate distance
  return distance_cm2;
}
