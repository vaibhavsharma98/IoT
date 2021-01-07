#include<Wire.h>
#include <MPU6050_tockn.h>
MPU6050 mpu6050(Wire);
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
float ax=0, ay=0, az=0, gx=0, gy=0, gz=0, rx=0, ry=0, rz=0;

//int data[STORE_SIZE][5]; //array for saving past data
//byte currentIndex=0; //stores current data array index (0-255)
boolean fall = false; //stores if a fall has occurred
boolean trigger1=false; //stores if first trigger (lower threshold) has occurred
boolean trigger2=false; //stores if second trigger (upper threshold) has occurred
boolean trigger3=false; //stores if third trigger (orientation change) has occurred
void mpu_read();
byte trigger1count=0; //stores the counts past since trigger 1 was set true
byte trigger2count=0; //stores the counts past since trigger 2 was set true
byte trigger3count=0; //stores the counts past since trigger 3 was set true
int angleChange=0;
int ch = 0;

void setup(){
  
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050) 
  Wire.endTransmission(true);
  
  Serial.begin(115200);
  pinMode(10,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5, OUTPUT);
 
}
void loop(){
  mpu6050.update();
  mpu_read();

  // values may be different for you
  ax = (mpu6050.getAccX());
  ay = (mpu6050.getAccY());
  az = (mpu6050.getAccZ());
  
  //270, 351, 136 for gyroscope
  gx = (mpu6050.getGyroAngleX());
  gy = (mpu6050.getGyroAngleY());
  gz = (mpu6050.getGyroAngleZ());
  
  /////////////////////////////
  
  rx = (mpu6050.getGyroX());
  ry = (mpu6050.getGyroY());
  rz = (mpu6050.getGyroZ()); 
  
  int xx = ax*10;
  int yy = ay*10;
  int zz = az*10;

  Serial.print(xx);
  Serial.print("\t");
  Serial.print(yy);
  Serial.print("\t");
  Serial.print(zz);
  Serial.print("\t");
  float Raw_AM = pow(pow(ax,2)+pow(ay,2)+pow(az,4),0.5);
  int AM = Raw_AM*10 ;  // as values are within 0 to 1, I multiplied 
                         // it by for using if else conditions   
// Serial.print("AM = ");
 Serial.println(AM);
digitalWrite(3,HIGH);
digitalWrite(4,HIGH);
digitalWrite(5,HIGH);
delay(100);
digitalWrite(3,LOW);
digitalWrite(4,LOW);
digitalWrite(5,LOW);
delay(1000);

 
   /*  
    Serial.print("xx = ");
    Serial.println(rx);
    Serial.print("yy = ");
    Serial.println(ry);
    Serial.print("zz = ");
    Serial.println(rz);

//   calculating Amplitute vactor for 3 axis
  float Raw_AM = pow(pow(ax,2)+pow(ay,2)+pow(az,4),0.5);
  int AM = Raw_AM * 10;  // as values are within 0 to 1, I multiplied 
                         // it by for using if else conditions   
 Serial.print("AM = ");
 Serial.println(AM);

   float Raw_RM = pow(pow(rx,2)+pow(ry,2)+pow(rz,4),0.5);
   int RM = Raw_RM * 10;
   Serial.print("RM = ");
 Serial.println(RM);

  if (trigger3==true){
     trigger3count++;
    trigger2=false;
     Serial.println(trigger3count);
     if (trigger3count>=7){ 
        angleChange = pow(pow(gx,2)+pow(gy,2)+pow(gz,2),0.5);
        delay(10);
        Serial.println(angleChange); 
        if ((angleChange>=1000) && (angleChange<=4000)){ //if orientation changes remains between 0-10 degrees
            fall=true; trigger3=false; trigger3count=0;
            Serial.print("lower angle =");
            Serial.println(angleChange);
              }
        else{ //user regained normal orientation
           trigger3=false; trigger3count=0;
           Serial.println("failed");
           digitalWrite(13,LOW);
        }
      }
   }
  if (fall==true){ //in event of a fall detection
    Serial.println("FALL DETECTED");
   digitalWrite(10,HIGH);
   delay(3000);
   digitalWrite(10,LOW);
    fall=false;
    exit(1);
    }
  if (trigger2count>=6){ //allow 0.5s for orientation change
    trigger2=false; trigger2count=0; 
    Serial.println("trying");
    digitalWrite(11,LOW);
    }
   
  if (trigger2==true){
    trigger2count++;
    Serial.print("tik tik - ");
    Serial.println(trigger2count);

    angleChange = pow(pow(gx,2)+pow(gy,2)+pow(gz,2),0.5);
    Serial.println(angleChange); 
  
    if (angleChange>=200 && angleChange<=400){ //if orientation changes by between 80-100 degrees
      trigger3=true; trigger2=false; trigger2count=0;
      Serial.print("starting angle =");
      Serial.println(angleChange);
      digitalWrite(13,HIGH);
        }
  }  
    
  if (((RM>=1000) || (RM<=-1000)) && ((AM<9) || (AM>10))  && trigger2==false && trigger3==false)
  {   
    trigger2=true;
    //Serial.println("Got accerlation");
    digitalWrite(12,HIGH);
    }
  */
//It appears that delay is needed in order not to clog the port  
   
  
  }
  

void mpu_read(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}
