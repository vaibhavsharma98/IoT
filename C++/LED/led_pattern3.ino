int LED[4] = {13,12,11,10};

void setup()
{
for (int cnt=0; cnt<4; cnt++)
{
pinMode (LED[cnt], OUTPUT);
}
}
void loop()
{

  digitalWrite(13,HIGH);
  digitalWrite(10,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
  digitalWrite(10,LOW);
  //////////////////////
  digitalWrite(12,HIGH);
  digitalWrite(11,HIGH);
  delay(1000);
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
}
