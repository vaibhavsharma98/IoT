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
for (int cnt=0; cnt<4; cnt++)
{
  digitalWrite(LED[cnt],HIGH);
  delay(1000);
  digitalWrite(LED[cnt],LOW);
}
  for (int cnt=3; cnt>=0; cnt--)
{
  digitalWrite(LED[cnt],HIGH);
  delay(1000);
  digitalWrite(LED[cnt],LOW);
}
}
