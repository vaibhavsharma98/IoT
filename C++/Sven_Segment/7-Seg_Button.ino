int count=0;
int but=2;
int ssp0=5;
int ssp1=6;
int ssp2=7;
int ssp3=8;
int ssp4=9;
int ssp5=10;
int ssp6=11;
void no0();
void no1();
void no2();
void no3();
void no4();
void no5();
void no6();
void no7();
void no8();
void no9();
void setup()
{ 
  pinMode(ssp0,OUTPUT);pinMode(ssp1,OUTPUT);
  pinMode(ssp2,OUTPUT);pinMode(ssp3,OUTPUT);
  pinMode(ssp4,OUTPUT);pinMode(ssp5,OUTPUT);
  pinMode(ssp6,OUTPUT);pinMode(but,INPUT);
  
  
}
void loop(){
  if(digitalRead(but)==1){
    count++;
    while(digitalRead(but)==1);}
    if(count==0){
      no0();
  }
  if(count==1){
      no1();
  }
  if(count==2){
      no2();
  }
 if(count==3){
      no3();
  }
 if(count==4){
      no4();
  }
 if(count==5){
      no5();
  }
 if(count==6){
      no6();
  }
 if(count==7){
      no7();
  }
 if(count==8){
      no8();
  }
 if(count==9){
      no9();
      
  }
 
 
}
//FOR NO 0
void no0(){
  digitalWrite(ssp0,LOW);
  digitalWrite(ssp1,LOW);
  digitalWrite(ssp2,LOW);
  digitalWrite(ssp3,LOW);
  digitalWrite(ssp4,LOW);
  digitalWrite(ssp5,LOW);
  digitalWrite(ssp6,HIGH);
}
  //FOR NO 1
void no1(){
  digitalWrite(ssp0,HIGH);
  digitalWrite(ssp1,LOW);
  digitalWrite(ssp2,LOW);
  digitalWrite(ssp3,HIGH);
  digitalWrite(ssp4,HIGH);
  digitalWrite(ssp5,HIGH);
  digitalWrite(ssp6,HIGH);
 
} 
  //FOR NO 2
 void no2(){
  digitalWrite(ssp0,LOW);
  digitalWrite(ssp1,LOW);
  digitalWrite(ssp2,HIGH);
  digitalWrite(ssp3,LOW);
  digitalWrite(ssp4,LOW);
  digitalWrite(ssp5,HIGH);
  digitalWrite(ssp6,LOW);
 
 }
  //FOR NO 3
  void no3(){
  digitalWrite(ssp0,LOW);
  digitalWrite(ssp1,LOW);
  digitalWrite(ssp2,LOW);
  digitalWrite(ssp3,LOW);
  digitalWrite(ssp4,HIGH);
  digitalWrite(ssp5,HIGH);
  digitalWrite(ssp6,LOW);
   }
  //FOR NO 4
  void no4(){
  digitalWrite(ssp0,HIGH);
  digitalWrite(ssp1,LOW);
  digitalWrite(ssp2,LOW);
  digitalWrite(ssp3,HIGH);
  digitalWrite(ssp4,HIGH);
  digitalWrite(ssp5,LOW);
  digitalWrite(ssp6,LOW);
 
  }
  //FOR NO 5
  void no5(){
  digitalWrite(ssp0,LOW);
  digitalWrite(ssp1,HIGH);
  digitalWrite(ssp2,LOW);
  digitalWrite(ssp3,LOW);
  digitalWrite(ssp4,HIGH);
  digitalWrite(ssp5,LOW);
  digitalWrite(ssp6,LOW);
 
  }
  //FOR NO 6
  void no6(){
  digitalWrite(ssp0,LOW);
  digitalWrite(ssp1,HIGH);
  digitalWrite(ssp2,LOW);
  digitalWrite(ssp3,LOW);
  digitalWrite(ssp4,LOW);
  digitalWrite(ssp5,LOW);
  digitalWrite(ssp6,LOW);
 
  }
  //FOR NO 7
  void no7(){
  digitalWrite(ssp0,LOW);
  digitalWrite(ssp1,LOW);
  digitalWrite(ssp2,LOW);
  digitalWrite(ssp3,HIGH);
  digitalWrite(ssp4,HIGH);
  digitalWrite(ssp5,HIGH);
  digitalWrite(ssp6,HIGH);
 
  }
  
  //FOR NO 8
  void no8(){
  digitalWrite(ssp0,LOW);
  digitalWrite(ssp1,LOW);
  digitalWrite(ssp2,LOW);
  digitalWrite(ssp3,LOW);
  digitalWrite(ssp4,LOW);
  digitalWrite(ssp5,LOW);
  digitalWrite(ssp6,LOW);
 
  }
  //FOR NO 9
  void no9(){
  digitalWrite(ssp0,LOW);
  digitalWrite(ssp1,LOW);
  digitalWrite(ssp2,LOW);
  digitalWrite(ssp3,HIGH);
  digitalWrite(ssp4,HIGH);
  digitalWrite(ssp5,LOW);
  digitalWrite(ssp6,LOW);
 
  }
