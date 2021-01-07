#include <ESP8266WiFi.h>
#include <PubSubClient.h>
void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
String num="";
const char* ssid = "le tu bhi le";
const char* password = "hotspotn";
const char* mqtt_username = "gaurav.oytechnology@gmail.com";
const char* mqtt_password = "06cf03f7";
int input=0;
const char* mqtt_server = "mqtt.dioty.co";
int gpio2_pin = 2;
int gpio16_pin =16;
WiFiClient espClient;
PubSubClient client(espClient);
/////////
unsigned long previousTime =0;
unsigned long timeCount =0;
unsigned long currentTime= millis();
unsigned long timer;
bool timerStart =false;
void setup() {
    pinMode(gpio2_pin, INPUT);
    delay(2000);
     pinMode(gpio2_pin, OUTPUT);
    pinMode(gpio16_pin, OUTPUT);
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
     
    reconnect();
}

void setup_wifi(){

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    num += (String((char)payload[i]));
  }
  Serial.println("num");
  Serial.println(num);
  int datanum=num.toInt();
  Serial.println(datanum);
  
  num="";
  input = datanum;

   if(datanum>0) {
    pinMode(gpio2_pin,INPUT);
    pinMode(D3,OUTPUT);
    digitalWrite(D3,HIGH);
    delay(1000);
    digitalWrite(D3,LOW);
    delay(20);
    pinMode(D3,INPUT);
    pinMode(gpio2_pin,OUTPUT);
     timerStart=true;
     digitalWrite(gpio2_pin, HIGH);
   
     Serial.print("start");
     if(timerStart==true)
  {
  unsigned long timer = ((millis()/1000) - previousTime);   
  Serial.println(timer);   
  delay(200);
  previousTime = millis()/1000;
  }
  } 
    Serial.println();
  }
 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(("OYT1"),mqtt_username, mqtt_password)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("oxymora", "1");
      // ... and resubscribe
      client.subscribe("/gaurav.oytechnology@gmail.com/out");
      client.subscribe("/gaurav.oytechnology@gmail.com/out");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
 
  if (!client.connected()) {
    reconnect();
  }
  
  client.loop();
  client.setCallback(callback);
  unsigned long timer = ((millis()/1000) -previousTime);   
  
  Serial.println(timer);   
  delay(200);
  //previousTime = millis()/1000;
  if(input==timer)
  {
    
    digitalWrite(gpio2_pin, LOW);
    Serial.println("off");
    delay(50); 
    timerStart=false;
  }
  if(timerStart==false)
  {
    digitalWrite(gpio2_pin,LOW);
  }
  
  }
  
