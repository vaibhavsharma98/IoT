   				#include<lpc214x.h>
			 void mydelay()
			 { unsigned int i,j;
			 	 for(i=0;i<4000;i++)
			 	  for( j=0;j<4000;j++);
			 }
int main()
{ 

  IO0DIR = 0x003c3c00;
  IO0CLR = 0x003c3c00;
   
  IO1DIR = 0x00ff0000;
 
  while(1)
  {	
  	   IO0CLR = 0x003c3c00;
  			 mydelay();
  		  IO0SET = 0x003c3c00;
		  mydelay();
  /* IO1SET= 0x00ff0000;
	 IO1DIR = (1<<16);
     IO1CLR = (1<<16);
    if(( IO1PIN & (1<<20))==0)
	{ 		IO0CLR= 0x00000400;		}
	if(( IO1PIN & (1<<21))==0)	 	
	{ 		IO0CLR = 0x00000800;	}
	if(( IO1PIN & (1<<22))==0)
	{ 		IO0CLR = 0x00001000;	}
	if(( IO1PIN &(1<<23))==0)
	{ 		IO0CLR = 0x00002000;	}
	
	IO1SET =(1<<16);
	IO1DIR = (1<<17);
	IO1CLR = (1<<17);
	if(( IO1PIN & (1<<20))==0)
	{ 		IO0SET = 0x00000400;	}
	if(( IO1PIN & (1<<21))==0)
	{ 		IO0SET = 0x00000800;	}
	if(( IO1PIN & (1<<22))==0)
	{ 		IO0SET = 0x00001000;	}
	if(( IO1PIN & (1<<23))==0)		
	{ 		IO0SET = 0x00002000;	}

	IO1SET = (1<<17);
	IO1DIR = (1<<18);
	IO1CLR = (1<<18);
	if(( IO1PIN & (1<<20))==0)
	{ 		IO0CLR = 0x00040000;	 }
	if(( IO1PIN & (1<<21))==0)
	{ 		IO0CLR = 0x00080000;	 }
	if(( IO1PIN & (1<<22))==0)
	{ 		IO0CLR = 0x00100000;	 }
	if(( IO1PIN & (1<<23))==0)
	{ 		IO0CLR = 0x00200000;	}

	IO1SET = (1<<18);
	IO1DIR = (1<<19);
	IO1CLR = (1<<19);
	if(( IO1PIN & (1<<20))==0)
	{ 	IO0SET = 0x00040000;	 }
	if(( IO1PIN & (1<<21))==0)
	{ 	IO0SET = 0x00080000;	  }
	if(( IO1PIN & (1<<22))==0)
	{ 	IO0SET = 0x00100000;	   	}
	if(( IO1PIN & (1<<23))==0)
	{ 	IO0SET = 0x00200000;		}
	 
	IO1SET = (1<<19);
	*/}

}
