#include<stdio.h>
#include<stdlib.h>
#include "head.h"
#include "main.h"
/*include区*/
 
#define original 1000//初始资金 
#define max 10//定义最多买多少个骑手 
#define count 6
#define A 700//金额数 
#define B 400//金额数 
/*宏定义区*/ 

extern int money,ridernumber;

int buy(void)
{
	int i,j;
	if( ridernumber==0 )//目前没有骑手 
	{
		money -= 900;
		for( i = 0;i < 3;i++ )//购买3个骑手 
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
			/*骑手初始条件赋值*/ 
			
			for( j = 0;j < 50;j++ )
			{
				allriders[ridernumber-1].temporarytask[j] = NULL;
			} 
			allriders[ridernumber-1].finaltask = NULL; 
			/*骑手订单序列初始赋为空*/
		}
		return 1;
	}
	if( ridernumber <= count )
	{
		if( money > B )
		{
			money -= 300;
			ridernumber++;//购买一个骑手 
			allriders[ridernumber-1].state = 0;
			allriders[ridernumber-1].change = 0;
			allriders[ridernumber-1].x = 8;
			allriders[ridernumber-1].y = 7;
			allriders[ridernumber-1].accept = 0;
			allriders[ridernumber-1].over = 0;
			allriders[ridernumber-1].finish = 0;
			allriders[ridernumber-1].currentnumber = 0;
			/*骑手初始条件赋值*/ 
			for( i = 0;i < 50;i++ )
			{
				allriders[ridernumber-1].temporarytask[i] = NULL;
			}
			allriders[ridernumber-1].finaltask = NULL; //骑手初始订单序列你复赋为空 
			return 1;
		}
		else return 0;
	}
	else if( ridernumber > count && ridernumber <= max )
	{
		if( money > A )
		{
			money -= 300;
			ridernumber++;//购买一个骑手 
			allriders[ridernumber-1].state = 0;
			allriders[ridernumber-1].change = 0;
			allriders[ridernumber-1].x = 8;
			allriders[ridernumber-1].y = 7;
			allriders[ridernumber-1].accept = 0;
			allriders[ridernumber-1].over = 0;
			allriders[ridernumber-1].finish = 0;
			allriders[ridernumber-1].currentnumber = 0;
			/*骑手初始信息赋值*/ 
			for( i = 0;i < 50;i++ )
			{
				allriders[ridernumber-1].temporarytask[i] = NULL;
			}
			allriders[ridernumber-1].finaltask = NULL;//骑手订单赋为空 
			return 1;
		}
		else return 0;
	}
	else
	{
		return 0;
	}
}

