#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include<process.h> 
#include "head.h" 
#include "main.h"
/*include��*/ 

extern struct order * firstorder;
extern int temp;
int in(int x, int y);//�ж�����Ƿ��ڷ����� ��1/��0 
int stop(int x, int y); //�ж�����Ƿ����ֹͣ��ť ��1/��0 

struct input_order{
	int num;//���
	int time;//���������ʱ��
	int cx;
	int cy;//�͹ݺ������� 
	int sx;
	int sy;//ʳ�ͺ������� 
};//���ڽ��յ�ǰ����Ķ�����Ϣ�Ľṹ�� 

extern unsigned _stdcall input(void * pArgumens)
{
	int x,y;//Ϊ��������� 
	int state = 0;//���Ŀǰ״̬   
	struct input_order input;
	LISTNODEPTR headPtr = NULL , lastPtr = NULL , currentPtr = NULL;
	mouse_msg msg = {0}; 
	all=0;//�ܶ�������ʼ�� 
	
	while(temp == 0 && !kbhit())//����������������δ����ֹ 
	{
		if (mousemsg())//���ڼ����û�������Ϣ
		{
			msg = getmouse();
			if(msg.is_down() && in(msg.y,msg.x) && state == 0)//�����갴�����ڷ����ڣ���ʼһ���µĶ��� 
			{
				currentPtr = (LISTNODE*)malloc(sizeof(LISTNODE));
				if(currentPtr != NULL)
				{
					currentPtr->num = all ;//�ö�����Ÿ�ֵ 
					currentPtr->cy = 2 * ((msg.x - 50) / 80);
					currentPtr->cx = 2 * ((msg.y - 55) / 65) ;//��ȡ�͹����� 
					currentPtr->current = 0 ;
					currentPtr->overtime= 0 ;//�ö���״̬��ֵ  
					state = 1;//�ı�״̬ 
				}
			}
			else if(msg.is_down() && in(msg.y,msg.x) && state == 1)//������ڶ��ΰ������ڷ�����
			{
				currentPtr->sy = 2 * ((msg.x - 50) / 80) ;
				currentPtr->sx = 2 * ((msg.y - 55) / 65) ;//��ȡʳ������ 
				currentPtr->time = time ;//�ö�������ʱ�丳ֵ 
				currentPtr->orderptr = NULL;
				all++;//��������+1		
				state = 0;	
				
				if( headPtr == NULL )//�õ�Ϊ��һ���� 
				{
					headPtr = currentPtr;
					lastPtr = currentPtr;
					firstorder = headPtr;//�������� 
				}
				else//�õ����ǵ�һ���� 
				{
					lastPtr -> orderptr = currentPtr;
					lastPtr = currentPtr;//��������	
				}
				
			}
			else if(msg.is_down() && stop(msg.y,msg.x))//�����갴���˳���ť 
			{
				temp = 3;	
			} 
			else if(msg.is_down() && ( in(msg.y,msg.x) == 0 ) && ( stop(msg.y,msg.x)==0 ) && state == 1)//�������ɿ������ڷ����ڣ�����Ч
			{
				;//��Ч���� 
			} 
			 
			msg = {0};//�����Ϣ���� 
		}
	}
	_endthreadex(0);//�߳����ʱ���� 
	return 0;
		
}
int in(int x,int y)//�ж�����Ƿ��ڷ����� ��1/��0 
{


	if((y >= 80 && y <= 770) && ( x >=80 && x <= 640))
	{
		if((y - 80) % 80 <= 50)//y��������
		{
	
			if((x - 80) % 65 <= 40)//x�������� 
			{
				return 1;
			}
			else return 0;
		} 
		else return 0;
	}
	else
	{
		return 0;
	}
}

int stop(int x, int y)//�����갴���˳���ť 
{
	
	if((x >= 450 && x <= 500)&&(y >= 900 && y <=950))  return 1;
	else return 0;
	
}
