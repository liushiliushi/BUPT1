#include<stdio.h>
#include<stdlib.h>
#include"head.h" 

extern struct order * firstorder;
extern int all;
/*typedef struct order LISTNODE;
typedef LISTNODE * LISTNODEPTR;*/
//�������͵Ķ������head.h���� 

struct input_order{
	int num;//���
	int time;//���������ʱ��
	int cx;
	int cy;//�͹ݺ������� 
	int sx;
	int sy;//ʳ�ͺ������� 
};//���ڽ��յ�ǰ����Ķ�����Ϣ�Ľṹ�� 

/* 
void printlist(LISTNODEPTR headPtr);
void destory(LISTNODEPTR headPtr);
*/

void input(void)
{
	int x;
	struct input_order input;
	LISTNODEPTR headPtr = NULL , lastPtr = NULL , currentPtr = NULL;
	FILE * fPtr;
	
	all=0;
	
	if((fPtr=fopen("scale.txt","r")) != NULL)//���Ŀ¼���Ƿ����ļ� 
	{
		fscanf(fPtr,"%d%d%d%d%d%d",&input.num,&input.time,&input.cx,&input.cy,&input.sx,&input.sy);
		while(!feof(fPtr))
		{
			currentPtr = (LISTNODE*)malloc(sizeof(LISTNODE));
			all++; 
			if(currentPtr != NULL)
			{
				currentPtr->num = input.num;
				currentPtr->time = input.time;
				currentPtr->cx = input.cx;
				currentPtr->cy = input.cy;
				currentPtr->sx = input.sx;
				currentPtr->sy = input.sy; 
				currentPtr->current = 0;
				currentPtr->overtime= 0; 
				 
				if( headPtr == NULL )
				{
					headPtr = currentPtr;
					lastPtr = currentPtr;
				}
				else
				{
					lastPtr -> orderptr = currentPtr;
					lastPtr = currentPtr;	
				}
			}
			
			fscanf(fPtr,"%d%d%d%d%d%d",&input.num,&input.time,&input.cx,&input.cy,&input.sx,&input.sy);
		}
		lastPtr -> orderptr = NULL;
	}
	else//ʹ�ü������� 
	{
		while(scanf("%d",&x) != EOF)
		{
			scanf("%d%d%d%d%d",&input.time,&input.cx,&input.cy,&input.sx,&input.sy);
			input.num = x;
			
			currentPtr = (LISTNODE*)malloc(sizeof(LISTNODE));
			all++;
			if(currentPtr != NULL)
			{
				currentPtr->num = input.num;
				currentPtr->time = input.time;
				currentPtr->cx = input.cx;
				currentPtr->cy = input.cy;
				currentPtr->sx = input.sx;
				currentPtr->sy = input.sy; 
				currentPtr->current = 0;
				currentPtr->overtime = 0; 
				
				if( headPtr == NULL )
				{
					headPtr = currentPtr;
					lastPtr = currentPtr;
				}
				else
				{
					lastPtr -> orderptr = currentPtr;
					lastPtr = currentPtr;	
				}
			}
		}
		lastPtr -> orderptr = NULL;
	}
	
	firstorder = headPtr;
	
	/*printlist(headPtr);
	destory(headPtr);*/	
} 

/* 
void printlist(LISTNODEPTR headPtr)
{
	LISTNODEPTR currentPtr = NULL;
	
	currentPtr = headPtr;
	while(currentPtr != NULL)
	{
		printf("%d %d %d %d %d %d %d\n",currentPtr->num,currentPtr->time,currentPtr->cx,
		currentPtr->cy,currentPtr->sx,currentPtr->sy,currentPtr->current);
		
		currentPtr = currentPtr->orderPtr;
	}
}
void destory(LISTNODEPTR headPtr)
{
	LISTNODEPTR tempPtr = NULL;
	
	while(headPtr != NULL)
	{
		tempPtr = headPtr;
		headPtr = headPtr->orderPtr;
		free(tempPtr);
	}
}*/
//���ڲ��ԣ��ͷŶ�̬�洢�ռ�Ӧ������main.c�� 

