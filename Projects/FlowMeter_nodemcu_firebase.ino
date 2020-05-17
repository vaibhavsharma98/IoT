#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
//#include <WiFiClient.h>
//#include "JSON.h"
#define LED_BUILTIN 2
#define SENSOR 4

long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
boolean ledState = LOW;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
#define FIREBASE_HOST "https://water-usage-90c72.firebaseio.com"
#define FIREBASE_AUTH "K2XxJvaB3L1MYSn4ZPbEdfaSuOFMDL1B5Nf4CT95"
const char* ssid     = "VS";
const char* password = "0987654321";

//String username="vaibhavsharma101098@gmail.com";
////String Device_No="tap1" ; 
//int CELSIUS=15, HUM =30;

void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

void setup()
{
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SENSOR, INPUT_PULLUP);

  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;

  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, FALLING);
  //////////////////////
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  /////////////////
}
//String getJSON(){
 // String data ;
 //  data += "{\"username\":\"" + String(username)  + "\",\"name\":\"";
//   data += String(Device_No);
//   data += "\",\"sample1\":\"";
//   data += String( CELSIUS); //(unsigned char)
//   data += "\",\"sample2\":\"";
//   data += String(HUM); 
//   data += "\",\"sample5\":\"";
//   int nosample=-1;
//   data += String(nosample); 
//   data += "\"}";
 //  return data;
//}
void loop()
{
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {

    pulse1Sec = pulseCount;
    pulseCount = 0;

    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();

    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flowMilliLitres = (flowRate / 60) * 1000;

    // Add the millilitres passed in this second to the cumulative total
    totalMilliLitres += flowMilliLitres;

    Firebase.setFloat("Flow rate: ");
      Firebase.setFloat ("L/min");
      Firebase.setFloat ("Output Liquid Quantity: ");
      Firebase.setFloat ("mL / ");

    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");       // Print tab space

    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);
    Serial.print("mL / ");
    Serial.print(totalMilliLitres / 1000);
    Serial.println("L");
    
//    String content =  getJSON() ;
//    Serial.println(content);
//    jsonPOST( content);
//    //delay(5000) ;

  }
}
