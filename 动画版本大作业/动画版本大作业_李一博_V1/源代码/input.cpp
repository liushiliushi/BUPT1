#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include<process.h> 
#include "head.h" 
#include "main.h"
/*include区*/ 

extern struct order * firstorder;
extern int temp;
int in(int x, int y);//判断鼠标是否在方块内 是1/否0 
int stop(int x, int y); //判断鼠标是否点中停止按钮 是1/否0 

struct input_order{
	int num;//编号
	int time;//订单发起的时间
	int cx;
	int cy;//餐馆横纵坐标 
	int sx;
	int sy;//食客横纵坐标 
};//用于接收当前输入的订单信息的结构体 

extern unsigned _stdcall input(void * pArgumens)
{
	int x,y;//为鼠标的坐标点 
	int state = 0;//鼠标目前状态   
	struct input_order input;
	LISTNODEPTR headPtr = NULL , lastPtr = NULL , currentPtr = NULL;
	mouse_msg msg = {0}; 
	all=0;//总订单数初始化 
	
	while(temp == 0 && !kbhit())//主函数正常进行且未被终止 
	{
		if (mousemsg())//用于检测有没有鼠标消息
		{
			msg = getmouse();
			if(msg.is_down() && in(msg.y,msg.x) && state == 0)//如果鼠标按下且在方块内，则开始一个新的订单 
			{
				currentPtr = (LISTNODE*)malloc(sizeof(LISTNODE));
				if(currentPtr != NULL)
				{
					currentPtr->num = all ;//该定单编号赋值 
					currentPtr->cy = 2 * ((msg.x - 50) / 80);
					currentPtr->cx = 2 * ((msg.y - 55) / 65) ;//获取餐馆坐标 
					currentPtr->current = 0 ;
					currentPtr->overtime= 0 ;//该订单状态赋值  
					state = 1;//改变状态 
				}
			}
			else if(msg.is_down() && in(msg.y,msg.x) && state == 1)//如果鼠标第二次按下且在方块内
			{
				currentPtr->sy = 2 * ((msg.x - 50) / 80) ;
				currentPtr->sx = 2 * ((msg.y - 55) / 65) ;//获取食客坐标 
				currentPtr->time = time ;//该订单发起时间赋值 
				currentPtr->orderptr = NULL;
				all++;//订单总数+1		
				state = 0;	
				
				if( headPtr == NULL )//该单为第一个单 
				{
					headPtr = currentPtr;
					lastPtr = currentPtr;
					firstorder = headPtr;//链表连接 
				}
				else//该单不是第一个单 
				{
					lastPtr -> orderptr = currentPtr;
					lastPtr = currentPtr;//链表连接	
				}
				
			}
			else if(msg.is_down() && stop(msg.y,msg.x))//如果鼠标按下退出按钮 
			{
				temp = 3;	
			} 
			else if(msg.is_down() && ( in(msg.y,msg.x) == 0 ) && ( stop(msg.y,msg.x)==0 ) && state == 1)//如果鼠标松开但不在方块内，则无效
			{
				;//无效操作 
			} 
			 
			msg = {0};//鼠标信息清零 
		}
	}
	_endthreadex(0);//线程完成时调用 
	return 0;
		
}
int in(int x,int y)//判断鼠标是否在方块内 是1/否0 
{


	if((y >= 80 && y <= 770) && ( x >=80 && x <= 640))
	{
		if((y - 80) % 80 <= 50)//y坐标满足
		{
	
			if((x - 80) % 65 <= 40)//x坐标满足 
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

int stop(int x, int y)//如果鼠标按下退出按钮 
{
	
	if((x >= 450 && x <= 500)&&(y >= 900 && y <=950))  return 1;
	else return 0;
	
}
