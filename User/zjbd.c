#include "zjbd.h"
#include "stm32f10x.h"
#include "Servo.h"
int cs(double d)
{
	
	int c=1790,zkb;
	
	if(d<0.12&&d>-0.12)
		zkb=c;
	
	else if(d>0.12&&d<0.4)
		zkb=c-70/0.3*(d-0.12);
	
	else if(d>=0.4)
		zkb=c-120;
	
	else if(d<-0.12&&d>-0.4)
		zkb=c-70/0.3*(d+0.12);
	
	else if(d<=-0.4)
		zkb=c+120;
	
	return zkb;
		
}
