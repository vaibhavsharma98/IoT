#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 

const char* ssid = "OxYmora Technology"; 
const char* password = "AGPoyt@8285"; 
const char* host = "www.innovativeupshot.in"; //edit the host adress, ip address etc. 
String url1 = "http://innovativeupshot.in//harshit/userverify.php";
int adcvalue=0; 

void setup() 
{ 
Serial.begin(115200); 
delay(10); // We start by connecting to a WiFi network 
Serial.println(); 
Serial.println(); 
Serial.print("Connecting to "); 
Serial.println(ssid); 
/* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default, would try to act as both a client and an access-point and could cause network-issues with your other WiFi-devices on your WiFi-network. */ 
WiFi.mode(WIFI_STA); 
WiFi.begin(ssid, password); 
while (WiFi.status() != WL_CONNECTED) 
{ 
delay(500); 
Serial.print("."); 
} 
Serial.println(""); 
Serial.println("WiFi connected"); 
Serial.println("IP address: "); 
Serial.println(WiFi.localIP()); } 
int value = 0; 
void loop() 
{ 
delay(5000); 
adcvalue=analogRead(A0); //Read Analog value of pin A0 
Serial.print("connecting to "); 
Serial.println(host); // Use WiFiClient class to create TCP connections 
WiFiClient client; 
const int httpPort = 80; 
if (!client.connect(host, httpPort)) 
{ 
Serial.println("connection failed"); 
return; 
} 
Serial.print("Requesting URL: "); 


String post = "{'UserEmail':'harshit.oytechnology@gmail.com'}";
String address = "http://innovativeupshot.in//harshit/userverify.php"; 
Serial.println(url1);  //Post Data 
HTTPClient http; 
http.begin(address); 
http.addHeader("Accept", "application/json"); 
auto httpCode = http.POST(post);
Serial.print("httpCode");
Serial.println(httpCode); //Print HTTP return code 
http.writeToStream(&Serial);
String payload = http.getString(); 
Serial.print("payload");
Serial.println(payload); //Print request response payload 

unsigned long timeout = millis();
while (client.available() == 0)
{
if (millis() - timeout > 5000)
{ Serial.println(">>> Client Timeout !");
client.stop(); return; } } // Read all the lines of the reply from server and print them to Serial
while (client.available())
{ String line = client.readStringUntil('\r'); 
Serial.print(line);
http.end(); //Close connection 
Serial.println(); 
Serial.println("closing connection");
} 
}
