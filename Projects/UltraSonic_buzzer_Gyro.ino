
 #define trigPin  13
#define echoPin 12
#include<LiquidCrystal.h>

const int rs = 5, en = 3, d4 = 2, d5 = 16, d6 = 15, d7 = 14;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


#include <Wire.h>
#include <MPU6050.h>

long duration;
int distance_cm,distance_inch;

//////////////// GYRO
MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;

//////////////////
void setup(){
    lcd.begin(16,2);
    lcd.print("Ultrasonic Sensor" );
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin,INPUT);
    delay(2000);
    pinMode(4, OUTPUT); //buzzer
    /////////////////GYRO
    Serial.begin(115200);

    // Initialize MPU6050
    while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
    {
      Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
      delay(500);
    }
    
    // Calibrate gyroscope. The calibration must be at rest.
    // If you don't want calibrate, comment this line.
    mpu.calibrateGyro();
  
    // Set threshold sensivty. Default 3.
    // If you don't want use threshold, comment this line or set 0.
    mpu.setThreshold(3);
    /////////////GYRO ends
}

void loop(){
    lcd.clear();
     //clear trigPin
   digitalWrite(trigPin,LOW);
   delayMicroseconds(2);
   //trigPin HIGH for 10 u sec
   digitalWrite(trigPin,HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin,LOW);
   
   duration=pulseIn(echoPin,HIGH);//reads echoPin
   distance_cm=duration*0.034/2; //calculate distance
   distance_inch=duration*0.0133/2;
   lcd.setCursor(0,0);
   lcd.print("Distance: ");
   lcd.print(distance_cm);
   lcd.print(" cm");
   delay(10);
//   lcd.setCursor(0,1);
//   lcd.print("Distance: ");
//   lcd.print(distance_inch);
//   lcd.print(" inch");
   
   
   if (((distance_cm)<=30)&&((distance_cm)>=14))
   {
   digitalWrite(4, HIGH); delay(500);
   digitalWrite(4, LOW); delay(100);
   }  
   else  
   {
    digitalWrite(4, LOW);
   }
  
   if (((distance_cm)<=15)&&((distance_cm)>=6))
   {
   digitalWrite(4, HIGH); delay(150);
    digitalWrite(4, LOW);delay(50);
   }
   else 
   {
    digitalWrite(4, LOW);
   }
  
   if (((distance_cm)<=5)&&((distance_cm)>=2))
   {
   digitalWrite(4, HIGH); delay(100);
   digitalWrite(4, LOW);delay(5);
   }
    else
    {
    digitalWrite(4, LOW);
    }
    delay(200);
   // ultrasonic work over 
   lcd.clear();
   lcd.print("GYRO-" ) ;
   
   timer = millis();

  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;

  // Output raw
  Serial.print(" Pitch = ");   Serial.print(pitch);
  Serial.print(" Roll = ");  Serial.print(roll);  
  Serial.print(" Yaw = ");  Serial.println(yaw);

  lcd.print(" X=");   lcd.print(pitch);
  lcd.setCursor(0,1);
  lcd.print("X=");   
     lcd.print(pitch);
  lcd.print("Y="); 
    lcd.print(roll);  
  lcd.print("Z=");  lcd.print(yaw);
  //z moving left right no tilting
  //x going down or up 
  //y
  // Wait to full timeStep period
  //delay((timeStep*1000) - (millis() - timer));
   
   delay(200);
    
}
