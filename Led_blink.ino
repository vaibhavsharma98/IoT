#include<avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL

int main (void)
{
  DDRB=0b00000011;
int arr[7]= {0x01,0x02,0x04,0x08,0x40,0x20,0x10};
  while(1)
  {
    for (int i=0;i<8;i++)
    {
     PORTB= arr[i];
    _delay_ms(500);
    }
  }
}
