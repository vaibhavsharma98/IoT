#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>

void SPI_slave_init(void)
{
 
  DDRB=0b00010000;//set MISO output
  SPCR=(1<<SPE);//enable SPI
}

unsigned char SPI_rx()
{
  while(!(SPSR&(1<<SPIF)))
  {
   Serial.print('w');
  }
  SPSR&=~(1<<SPIF);
  return SPDR;//return data register
}

unsigned char SPI_tx(unsigned char data)
{
   SPDR=data; //start tx
  while(!(SPSR&(1<<SPIF)))
  {
   Serial.print('w'); //wait for tx complete
  }
  SPSR&=~(1<<SPIF);
}
int main(void)
{
  SPI_slave_init();  //salve intialization
  DDRD=0x00;
  Serial.begin(9600);
  unsigned char data;  //receive data store in it
 
  while(1)
  {
     
        data=SPI_rx(); // receive data and send ACK
        //SPI_tx("data");
         Serial.println("sstep1");
         Serial.println(data);
        _delay_ms(100);
        if(data=='n')
        {
          PORTD=0x04;
        }
        else
        {
          PORTD=0x00;
        }
  }
}
