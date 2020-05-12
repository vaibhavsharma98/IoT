int ledPin1 = 13;
int ledPin2 = 12;
int ledPin3 = 11;
int ledPin4 = 10;

void setup() {
  pinMode(ledPin1 , OUTPUT);
  pinMode(ledPin2 , OUTPUT);
  pinMode(ledPin3 , OUTPUT);
  pinMode(ledPin4 , OUTPUT);
}

void loop() {
    //// ascending pattern/////
    digitalWrite(ledPin1, HIGH); 
    delay(1000);
    digitalWrite(ledPin1,LOW) ; 
    //////////
     digitalWrite(ledPin2, HIGH); 
    delay(1000);
    digitalWrite(ledPin2,LOW) ;
    //////////
     digitalWrite(ledPin3, HIGH); 
    delay(1000);
    digitalWrite(ledPin3,LOW) ;
    //////////
     digitalWrite(ledPin4, HIGH); 
    delay(1000);
    digitalWrite(ledPin4,LOW) ; 
    //////descending pattern///////
    digitalWrite(ledPin4, HIGH); 
    delay(1000);
    digitalWrite(ledPin4,LOW) ; 
    ////////
    digitalWrite(ledPin3, HIGH); 
    delay(1000);
    digitalWrite(ledPin3,LOW) ;
    ////////
    digitalWrite(ledPin2, HIGH); 
    delay(1000);
    digitalWrite(ledPin2,LOW) ;
    //////////
    digitalWrite(ledPin1, HIGH); 
    delay(1000);
    digitalWrite(ledPin1,LOW) ; 
}
