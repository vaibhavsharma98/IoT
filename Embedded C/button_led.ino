#include<avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL

int main (void)
{
  DDRB=0b00100000;
  DDRC=0b00000000;
  while(1)
  {
    if (PINC==0b00000001)
    {
   PORTB=0b00100000;
   _delay_ms(300);
    }
    else
    {
    PORTB=0b00000000;
    _delay_ms(300);
    }
  }
}
