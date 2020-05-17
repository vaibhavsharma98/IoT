#include <LPC214x.h>

#define RET0	0x00010000	// P1.16
#define RET1	0x00020000	// P1.17
#define RET2	0x00040000	// P1.18
#define RET3	0x00080000	// P1.19

#define	ALL_RET	(RET0|RET1|RET2|RET3)

#define SCAN0	0x00100000	// P1.20
#define SCAN1	0x00200000	// P1.21
#define SCAN2	0x00400000	// P1.22
#define SCAN3	0x00800000	// P1.23

const unsigned int KBD_u32scanport1[4]={SCAN0,SCAN1,SCAN2,SCAN3};

const unsigned int KBD_u32retport[4]={RET0,RET1,RET2,RET3};

#define CRYSTAL_FREQUENCY_IN_HZ 12000000
#define PLL_MULTIPLIER	1
#define DEL_LOOPS	CRYSTAL_FREQUENCY_IN_HZ*PLL_MULTIPLIER/500000

unsigned int KBD_i32keydown;

void KBD_cdelay(void)
{
	int i32i;
	for (i32i=0; i32i<5*DEL_LOOPS; i32i++) {}
}

int KBD_i32the_sc ;

int KBD_kbhit (void)
{
	int i32sc , i32sc0 ;
	int i32ret, i32ret0 ;

	for(i32sc = 0;i32sc < 4 ; i32sc ++)
	{
		IO1DIR = KBD_u32scanport1[i32sc] | (0x03000000)	; // For RS and RW of LCD
		IO1CLR = KBD_u32scanport1[i32sc] ;
		
		KBD_cdelay() ;
		i32ret = IO1PIN & ALL_RET ; 

		if (KBD_i32keydown == -1)
		{
			switch(i32ret)
			{
				case	(ALL_RET & (~RET0))	:
						KBD_i32the_sc = i32sc ;
						KBD_i32keydown = (i32sc * 4) ;
						return 1 ;
				case	(ALL_RET & (~RET1))	:
						KBD_i32the_sc = i32sc ;
						KBD_i32keydown = (i32sc * 4) + 1 ;
						return 1 ;
				case	(ALL_RET & (~RET2))	:
						KBD_i32the_sc = i32sc ;
						KBD_i32keydown = (i32sc * 4) + 2 ;
						return 1 ;
				case	(ALL_RET & (~RET3))	:
						KBD_i32the_sc = i32sc ;
						KBD_i32keydown = (i32sc * 4) + 3 ;
						return 1 ;
				
			}
			
		}
		else
		{
			// i.e. key is already pressed, wait until it is released
			if (i32sc == KBD_i32the_sc)
			{
				if (i32ret == ALL_RET)
				{
					KBD_i32keydown = -1 ;	// key has been released
				}
			}
		}

	}
	return 0 ;
}

int KBD_rdkbd(void)
{
	while(!KBD_kbhit()) {}
	return KBD_i32keydown ;
}

