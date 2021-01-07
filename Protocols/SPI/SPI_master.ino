#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>

void SPI_master_init(void)
{
  
  DDRB=0B00101100;
  SPCR|=(1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);//enable SPI, master,set clk rate

}

unsigned char SPI_tx(unsigned char data)
{
  PORTD&=~(1<<PD7);
  _delay_ms(10);
  SPDR=data;
  while(!(SPSR&(1<<SPIF)));
  SPSR&=~(1<<SPIF);    //wait for tx complete

  _delay_ms(10);
  PORTD|=(1<<PD7);
}
unsigned char SPI_rx(unsigned char data)
{
  PORTD&=~(1<<PD7);
  _delay_ms(10);
  SPDR=0b10101010;
  while(!(SPSR&(1<<SPIF)));
 SPSR&=~(1<<SPIF);    //wait for tx complete

  _delay_ms(10);
  PORTD|=(1<<PD7);
  _delay_ms(10);
  return SPDR;//return data register
}

int main(void)
{
  SPI_master_init(); //intialize master
  _delay_ms(1000);
  
  DDRD=0xff; //port B as output
  DDRC=0x00; //port C as signal input for switch
  Serial.begin(9600);
  unsigned char data,a; // received data stored in it
  
  Serial.println('a');
  _delay_ms(100);
  while(1)
  { 
    
    if (PINC==0x01)
     {
       data= SPI_tx('n');  //send a, recevie ACK in data
       Serial.println("step3");
       Serial.println(data);    
      }
     
    }
  }
