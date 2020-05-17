#include<lpc21xx.h> 
int main()
{ 
  long int delay ;  
  IO0DIR = 0x003c0000; // Configure P0.10 to P0.13 and P0.18 to P0.21 as Output 
	while(1) {
		IO0CLR = 0x003c0000 ; // CLEAR (0) P0.10 to P0.13 and P0.18 to P0.21, LEDs ON 
		for (delay=0 ; delay<5000000 ; delay++) ; 
		IO0SET = 0x003c0000 ; // SET (1) P0.10 to P0.13 and P0.18 to P0.21, LEDs OFF 
		for (delay=0 ; delay<5000000 ; delay++) ; 
	}
} 
