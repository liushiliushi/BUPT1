#include<stdio.h>
#include<stdlib.h>
#include "head.h"
#include "main.h"
/*include��*/
 
#define original 1000//��ʼ�ʽ� 
#define max 10//�����������ٸ����� 
#define count 6
#define A 700//����� 
#define B 400//����� 
/*�궨����*/ 

extern int money,ridernumber;

int buy(void)
{
	int i,j;
	if( ridernumber==0 )//Ŀǰû������ 
	{
		money -= 900;
		for( i = 0;i < 3;i++ )//����3������ 
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
			/*���ֳ�ʼ������ֵ*/ 
			
			for( j = 0;j < 50;j++ )
			{
				allriders[ridernumber-1].temporarytask[j] = NULL;
			} 
			allriders[ridernumber-1].finaltask = NULL; 
			/*���ֶ������г�ʼ��Ϊ��*/
		}
		return 1;
	}
	if( ridernumber <= count )
	{
		if( money > B )
		{
			money -= 300;
			ridernumber++;//����һ������ 
			allriders[ridernumber-1].state = 0;
			allriders[ridernumber-1].change = 0;
			allriders[ridernumber-1].x = 8;
			allriders[ridernumber-1].y = 7;
			allriders[ridernumber-1].accept = 0;
			allriders[ridernumber-1].over = 0;
			allriders[ridernumber-1].finish = 0;
			allriders[ridernumber-1].currentnumber = 0;
			/*���ֳ�ʼ������ֵ*/ 
			for( i = 0;i < 50;i++ )
			{
				allriders[ridernumber-1].temporarytask[i] = NULL;
			}
			allriders[ridernumber-1].finaltask = NULL; //���ֳ�ʼ���������㸴��Ϊ�� 
			return 1;
		}
		else return 0;
	}
	else if( ridernumber > count && ridernumber <= max )
	{
		if( money > A )
		{
			money -= 300;
			ridernumber++;//����һ������ 
			allriders[ridernumber-1].state = 0;
			allriders[ridernumber-1].change = 0;
			allriders[ridernumber-1].x = 8;
			allriders[ridernumber-1].y = 7;
			allriders[ridernumber-1].accept = 0;
			allriders[ridernumber-1].over = 0;
			allriders[ridernumber-1].finish = 0;
			allriders[ridernumber-1].currentnumber = 0;
			/*���ֳ�ʼ��Ϣ��ֵ*/ 
			for( i = 0;i < 50;i++ )
			{
				allriders[ridernumber-1].temporarytask[i] = NULL;
			}
			allriders[ridernumber-1].finaltask = NULL;//���ֶ�����Ϊ�� 
			return 1;
		}
		else return 0;
	}
	else
	{
		return 0;
	}
}

