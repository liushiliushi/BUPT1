#include<stdio.h>
#include"head.h"
/*include��*/ 

extern int ridernumber;
extern struct rider allriders[50];
/*�ṹ�壬������*/ 

void divide(void)
{
	int crossarea,i;//crossareaΪ���������ֵ����� 
	
    for(i = 0; i < ridernumber ; i++)//�������� 
	{
		allriders[i].x1 = 0;
		allriders[i].y1 = 0; 
		allriders[i].x2 = 16;
		allriders[i].y2 = 16;
		allriders[i].same = 1;	
	} 
}
