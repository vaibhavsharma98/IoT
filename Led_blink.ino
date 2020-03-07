#include<avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL

int main (void)
{
  DDRB=0b00000001;
  //DDRB=0x01; //in hex
  while(1)
    {
     PORTB= 0b00000001;
    //PORTB= 0x01; // in hex
    _delay_ms(500);
    PORTB= 0b00000000;
    //PORTB= 0x00; // in hex
    _delay_ms(500);
    }  
}
