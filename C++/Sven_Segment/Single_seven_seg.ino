int a=7; int b=6; int c=10; int d=9; int e=8; int f=5; int g=4;
void setup() {
 pinMode(a, OUTPUT);
 pinMode(b,OUTPUT); 
 pinMode(c,OUTPUT); 
 pinMode(d, OUTPUT);
 pinMode(e,OUTPUT); 
 pinMode(f,OUTPUT);
 pinMode(g,OUTPUT);

}

void loop() {
 digitalWrite(a,HIGH);digitalWrite(d,HIGH);digitalWrite(e,HIGH);digitalWrite(f,HIGH);digitalWrite(g,HIGH);
digitalWrite(b,LOW);digitalWrite(c,LOW); //ONE
delay(1000);
digitalWrite(c,HIGH);digitalWrite(f,HIGH);
digitalWrite(a,LOW);digitalWrite(b,LOW);digitalWrite(g,LOW);digitalWrite(e,LOW);digitalWrite(d,LOW); //TWO
delay(1000);
digitalWrite(e,HIGH);digitalWrite(f,HIGH);
digitalWrite(a,LOW);digitalWrite(b,LOW);digitalWrite(g,LOW);digitalWrite(c,LOW);digitalWrite(d,LOW); //THREE
delay(1000);
digitalWrite(a,HIGH);digitalWrite(d,HIGH);digitalWrite(e,HIGH);
digitalWrite(f,LOW);digitalWrite(g,LOW);digitalWrite(c,LOW);digitalWrite(b,LOW); //FOUR
delay(1000);
digitalWrite(b,HIGH);digitalWrite(e,HIGH);
digitalWrite(a,LOW);digitalWrite(f,LOW);digitalWrite(g,LOW);digitalWrite(c,LOW);digitalWrite(d,LOW); //FIVE
delay(1000);
digitalWrite(a,HIGH);digitalWrite(b,HIGH);
digitalWrite(f,LOW);digitalWrite(e,LOW);digitalWrite(g,LOW);digitalWrite(c,LOW);digitalWrite(d,LOW); //SIX
delay(1000);
digitalWrite(d,HIGH);digitalWrite(e,HIGH);digitalWrite(f,HIGH);digitalWrite(g,HIGH);
digitalWrite(a,LOW);digitalWrite(b,LOW);digitalWrite(c,LOW); //SEVEN
delay(1000);

digitalWrite(a,LOW);digitalWrite(b,LOW);digitalWrite(g,LOW);digitalWrite(e,LOW);digitalWrite(d,LOW);digitalWrite(c,LOW);digitalWrite(f,LOW); //EIGHT
delay(1000);
digitalWrite(d,HIGH);digitalWrite(e,HIGH);
digitalWrite(a,LOW);digitalWrite(b,LOW);digitalWrite(g,LOW);digitalWrite(f,LOW);digitalWrite(c,LOW); //NINE
delay(1000);
digitalWrite(g,HIGH);
digitalWrite(a,LOW);digitalWrite(b,LOW);digitalWrite(e,LOW);digitalWrite(d,LOW);digitalWrite(c,LOW);digitalWrite(f,LOW); //ZERO
delay(1000);

}
