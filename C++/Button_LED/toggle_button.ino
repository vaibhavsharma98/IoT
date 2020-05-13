const int ledPin = 13;
const int buttonPin = 2;
int status = false;
void setup()
{
  pinMode(buttonPin,INPUT);
  pinMode(ledPin,OUTPUT);
}
void loop()
{
  if (digitalRead(buttonPin)==true)
  {
    status = !status;
    digitalWrite(ledPin, status);
  }
  while (digitalRead(buttonPin)==true);
  delay(50);
  }

