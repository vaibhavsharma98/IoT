#include<avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL

int lcd_num(int num);
void lcd_cmd(int cmd);
void lcd_data(int data);
void lcd_init();
void lcd_str (char* str);
void setup() 
{
  DDRD=0xff;
  DDRB=0xff;
  lcd_init();
  lcd_cmd(0x01);
  delay(20);
}

void loop() 
 {
  lcd_cmd(0x83); 
  lcd_str("Hello World");
 }
void lcd_init()
{
lcd_cmd(0x02); //Return home
lcd_cmd(0x28); // Function Set: 4-bit, 2 Lines
lcd_cmd(0x06); //Increment cursor (shift cursor to right)
lcd_cmd(0x0c); // Display on, cursor off
}
void lcd_cmd(int cmd)
{
  PORTD=(cmd&0xF0);
  PORTD&=~(1<<PD0);
  PORTD|=(1<<PD1);
  delay(100);
  PORTD&=~(1<<PD1);
  delay(100);
  PORTD=((cmd<<4)&0xf0);
  PORTD&=~(1<<PD0);
  PORTD|=(1<<PD1);
  delay(100);
   PORTD&=~(1<<PD1);
  delay(100);
}
void lcd_data(int data)
{
  PORTD=(data&0xF0);
  PORTD|=(1<<PD0);
  PORTD|=(1<<PD1);
  delay(100);
  PORTD&=~(1<<PD1);
  delay(100);
  PORTD=((data<<4)&0xf0);
  PORTD|=(1<<PD0);
  PORTD|=(1<<PD1);
  delay(100);
  PORTD&=~(1<<PD1);
  delay(100);
}
int lcd_num(int num){
   int a;
  if(num==0)
  {
    lcd_data(48);
  }
  while(num!=0)
  {
    a=num%10;
    num=num/10;
    lcd_cmd(0x04);
    lcd_data(48+a);
  }
}
void lcd_str (char* str){
  int i=0;
  while(str!='\0')
  {
 lcd_data(str[i]);
 i++;
 delay(100);
 lcd_cmd(0x06);
  } }
