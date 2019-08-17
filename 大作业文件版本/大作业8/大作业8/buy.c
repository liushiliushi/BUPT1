#include<stdio.h>
#include<stdlib.h>
#include "head.h"
#include "main.h"
#define original 1000
#define max 10//定义最多买多少个骑手 
#define count 6
#define A 700 
#define B 400

extern int money,ridernumber;

int buy(void)
{
	int i,j;
	if(ridernumber == 0 )
	{
		money -= 900;
		for(i = 0;i < 3;i++)
		{
			ridernumber++;
			allriders[ridernumber-1].state = 0;
			allriders[ridernumber-1].change = 0;
			allriders[ridernumber-1].x = 8;
			allriders[ridernumber-1].y = 7;
			allriders[ridernumber-1].accept = 0;
			allriders[ridernumber-1].over = 0;
			allriders[ridernumber-1].finish = 0;
			allriders[ridernumber-1].currentnumber = 0;
			
			for(j = 0;j < 50;j++)
			{
				allriders[ridernumber-1].temporarytask[j] = NULL;
			}
			allriders[ridernumber-1].finaltask = NULL; 
		}
		return 1;
	}
	if(ridernumber <= count)
	{
		if(money > B)
		{
			money -= 300;
			ridernumber++;
			allriders[ridernumber-1].state = 0;
			allriders[ridernumber-1].change = 0;
			allriders[ridernumber-1].x = 8;
			allriders[ridernumber-1].y = 7;
			allriders[ridernumber-1].accept = 0;
			allriders[ridernumber-1].over = 0;
			allriders[ridernumber-1].finish = 0;
			allriders[ridernumber-1].currentnumber = 0;
			for(i = 0;i < 50;i++)
			{
				allriders[ridernumber-1].temporarytask[i] = NULL;
			}
			allriders[ridernumber-1].finaltask = NULL;  
			return 1;
		}
		else return 0;
	}
	else if(ridernumber > count && ridernumber <= max)
	{
		if(money > A)
		{
			money -= 300;
			ridernumber++;
			allriders[ridernumber-1].state = 0;
			allriders[ridernumber-1].change = 0;
			allriders[ridernumber-1].x = 8;
			allriders[ridernumber-1].y = 7;
			allriders[ridernumber-1].accept = 0;
			allriders[ridernumber-1].over = 0;
			allriders[ridernumber-1].finish = 0;
			allriders[ridernumber-1].currentnumber = 0;
			for(i = 0;i < 50;i++)
			{
				allriders[ridernumber-1].temporarytask[i] = NULL;
			}
			allriders[ridernumber-1].finaltask = NULL; 
			return 1;
		}
		else return 0;
	}
	else
	{
		return 0;
	}
}


