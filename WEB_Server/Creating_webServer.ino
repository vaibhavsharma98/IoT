#include <ESP8266WiFi.h>
int ledPin=2;
WiFiServer server(80);

void setup() {
  pinMode(ledPin,OUTPUT); 
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to WiFi ");
  
  WiFi.begin("kk" , "8804011047");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) { //client ==NULL
    return;
  }
   
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
   
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  if(request==("GET /R HTTP/1.1"))
  {
    client.print("ok done");
    Serial.print("sent");
  }
  client.flush();
   

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
  
 
}
