#include <ESP8266WiFi.h>
#include <PubSubClient.h>
void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

const char* ssid = "VS";
const char* password = "0987654321";

const char* mqtt_server = "mqtt.eclipse.org";
int gpio2_pin = 2;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    pinMode(gpio2_pin, OUTPUT);

    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
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
  }
  
  if((char)payload[0] == '1') { //on
     digitalWrite(gpio2_pin, HIGH);
     Serial.print("pin high");
  }   
  else if((char)payload[0] == '0' ) //off
  {  digitalWrite(gpio2_pin, LOW);
     Serial.print("pin low");
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("helloguys")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("Class/light1", "ok");
      client.print("");
      
      // ... and resubscribe
      client.subscribe("Class/light1");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
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
}
