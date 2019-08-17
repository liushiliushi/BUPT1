#include<stdio.h>
#include<stdlib.h>
#include"head.h" 

extern struct order * firstorder;
extern int all;
/*typedef struct order LISTNODE;
typedef LISTNODE * LISTNODEPTR;*/
//变量类型的定义放在head.h里面 

struct input_order{
	int num;//编号
	int time;//订单发起的时间
	int cx;
	int cy;//餐馆横纵坐标 
	int sx;
	int sy;//食客横纵坐标 
};//用于接收当前输入的订单信息的结构体 

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
	
	if((fPtr=fopen("scale.txt","r")) != NULL)//检查目录下是否有文件 
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
	else//使用键盘输入 
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
//用于测试，释放动态存储空间应当放在main.c中 

