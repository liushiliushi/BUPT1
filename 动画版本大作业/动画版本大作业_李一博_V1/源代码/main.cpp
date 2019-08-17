#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include<process.h> 
#include"head.h"//包含定义好的头文件 
#include"input.h"
/*include区*/ 

#define length 50
#define width 40 
/*宏定义区*/ 

int money=1000,ridernumber=0,time=0,temp=0,allaccept=0,over=0,finish=0,buytemp,all=0,prefinish,preover;
/*非静态全局变量和起初始值的定义 */
struct order * firstorder;//头订单指针 
struct rider allriders[50];//所有骑手信息 
/*结构，变量，指针定义区*/ 

void destory(LISTNODEPTR);

int main()
{
    int buytemp = 0;//判断是否重新划分区域的辅助变量 
    
    HANDLE hthread1;//线程的访问句柄 
    unsigned threadid = 1;//线程的标识号 
    
	initgraph(1280,720);//初始化图形库 
	
    hthread1 = (HANDLE)_beginthreadex(NULL,0,input,NULL,0,&threadid);//创建对应于input函数的线程 
    
    buytemp = buy();//判断是否购买骑手并操作
    
	while( temp==0 && !kbhit() )//正常派送循环 
	{
		if( buytemp!=0 ) //若购买了骑手 
		{
		    divide();//重新划分区域 
		}
		
		decide();//分配订单
		
		cleardevice();//清屏
       	cartoonoutput();//动画输出 
		
		bestwaywhile();//为所有骑手规划路径 
		
		addwhile();//使所有骑手移动并进行状态改变 
		
		time++;//时间推进一个时间单位 
		
		buytemp = buy();//判断是否购买骑手并操作	
		
	    Sleep(1000);
	}

    WaitForSingleObject(hthread1,INFINITE);//等待线程结束
	CloseHandle(hthread1);//删除句柄 
	
	
	getch();
	closegraph();//关闭图形界面 
	
	destory(firstorder);
    return 0;
}	

void destory(LISTNODEPTR headPtr)//释放链表 
{

	LISTNODEPTR tempPtr = NULL;

	while( headPtr != NULL )//依次释放所有链表 
	{
		tempPtr = headPtr;
		headPtr = headPtr->orderptr;
		free(tempPtr);
	}

}

