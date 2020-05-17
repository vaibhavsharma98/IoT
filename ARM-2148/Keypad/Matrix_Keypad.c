#include <LPC214x.h>
#include <stdio.h>
#include "KBD.h"
#include "lcd.h"



  void delay1()
 {
 unsigned int delay,j;
  for(j=0; j<50; j++)
 for(delay=0; delay<50000; delay++);
 }
void main (void)
{int key ;	
LcdInit();
LcdInit();

LcdCmd(0x01);

delay1();

	Display_string("Keypad Test ");				// Display message on 1st line of LCD 
 

	while(1)
	{
		key = KBD_rdkbd() ;					// Read Keyboard
	
	delay1();
	LcdCmd(0xc0);
		displaypval(key) ;					// Display keycode on 2nd line of LCD
delay1();
	}
	
}
