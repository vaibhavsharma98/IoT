#include<avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL


int main(void)
{
    DDRB=0xff;
    unsigned char arr[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90}; 
    int k;
    while(1)
    {
        for(k=0;k<10;k++)
        {
         PORTB=arr[k]; 
         _delay_ms(100);
        }
    }
}
