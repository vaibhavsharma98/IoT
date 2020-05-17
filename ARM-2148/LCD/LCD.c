#include <LPC214x.h>

 void SmallDelay (void)
{

	int i;
	for(i=0;i<100;i++);	
}

void LcdCmd1 (unsigned char cmd)
{

	// send command on on data lines (D4 to D7)
	if (cmd & 0x01)
		IO0SET = (1<<15);
	else
		IO0CLR = (1<<15);
		

	if (cmd & 0x02)
		IO0SET = (1<<17);
	else
		IO0CLR = (1<<17);
		

	if (cmd & 0x04)
		IO0SET = (1<<22);
	else
		IO0CLR = (1<<22);
		

	if (cmd & 0x08)
		IO0SET = (1<<30);
	else
		IO0CLR = (1<<30);
		

	IO1CLR = 0x03000000  ;	// CLEAR(0) RS and EN 
	SmallDelay() ;

	IO1SET = 0x01000000  ;	// SET(1) EN 

	SmallDelay() ;

	IO1CLR = 0x01000000  ;	// CLEAR(0) EN 

	SmallDelay() ;
}

void LcdDat1 (unsigned char dat)
{
	// send data on on data lines (D4 to D7)
	if (dat & 0x01)
		IO0SET = (1<<15);
	else
		IO0CLR = (1<<15);
		

	if (dat & 0x02)
		IO0SET = (1<<17);
	else
		IO0CLR = (1<<17);
		

	if (dat & 0x04)
		IO0SET = (1<<22);
	else
		IO0CLR = (1<<22);
		

	if (dat & 0x08)
		IO0SET = (1<<30);
	else
		IO0CLR = (1<<30);
		
	
	IO1SET = 0x02000000  ;	// SET(1) RS 
	
	SmallDelay() ;
	
	IO1CLR = 0x01000000  ;	// CLEAR(0) EN 

	SmallDelay() ;	
		
	IO1SET = 0x01000000  ;	// SET(1) EN 

	SmallDelay() ;

	IO1CLR = 0x01000000  ;	// CLEAR(0) EN 

	SmallDelay() ;	
}
void Delay250 (void)
{
	int k,j ;
	j =200 ;
	for(k = 0 ; k < 100 ; k ++)
	{
		j-- ;
	}
}
void DelayMs (int n)
{
	int k ;
	for(k = 0 ; k < n ; k ++)
	{
		Delay250() ;
		Delay250() ;
	}
}
void LcdCmd (unsigned char cmd)
{
	LcdCmd1(cmd >> 4) ;
	LcdCmd1(cmd) ;
	Delay250() ;
	Delay250() ;
}
void LcdDat (unsigned char dat)
{
	LcdDat1(dat >> 4) ;
	LcdDat1(dat) ;
	Delay250() ;
	Delay250() ;
}
void LcdInit (void)
{
	IO1DIR = 0x03000000  ;		// Configure P1.24(EN) and P1.25(RS) as Output
	IO1CLR = 0x03000000  ;		// CLEAR(0) P1.24(EN) and P1.25(RS)

	IO0DIR = 0x40428000  ;		// Configure P0.15(D4), P0.17(D5), P0.22(D6) and P0.30(D7) as Output
	IO0CLR = 0x40428000  ;		// CLEAR(0) P0.15(D4), P0.17(D5), P0.22(D6) and P0.30(D7)

	DelayMs(6) ;
	LcdCmd1(0x03) ;
	
	DelayMs(6) ;
	LcdCmd1(0x03) ;
	Delay250() ;

	LcdCmd1(0x03) ;
	Delay250() ;

	LcdCmd1(0x02) ;
	Delay250() ;

	LcdCmd(0x28) ;
	LcdCmd(0x08) ;
	LcdCmd(0x0c) ;
	LcdCmd(0x06) ;

}
void Display_string(char *s)
{
  
while(*s != '\0')	 
   {
    
    LcdDat(*s);
    s++;
   }
}


main ()
{	  	Delay250() ;	Delay250() ;	Delay250() ;
		Delay250() ;							// Initialize LCD
	   	
		LcdInit();	 
	  	LcdInit();
	  while(1){
	  	LcdCmd(0x80);
		Display_string ("welcome NIELIT");	
		LcdCmd(0xC0);
		Display_string ("                 ");		
		Delay250() ;
		Delay250() ;
		Delay250() ;
	}
}
