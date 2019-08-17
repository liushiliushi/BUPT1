#include<stdio.h>
#include"head.h"

extern int ridernumber;
extern struct rider allriders[50];
 

void divide(void)
{
	int crossarea,i;//crossarea为跨区域骑手的数量 
	
	
	for(i=0;i<ridernumber;i++)
	{
		allriders[i].x1 =0;
		allriders[i].y1 =0; 
		allriders[i].x2 =16;
		allriders[i].y2 =16;
		allriders[i].same =1;	
	} 
}
