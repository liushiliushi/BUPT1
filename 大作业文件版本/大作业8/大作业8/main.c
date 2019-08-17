#include<stdio.h>
#include<stdlib.h>
#include"head.h"//包含定义好的头文件 
#include"input.h"

int money=1000,ridernumber=0,time=0,temp=0,accept=0,over=0,finish=0,buytemp,all=0,prefinish,preover;//非静态全局变量和起初始值的定义 
struct order * firstorder;//头订单指针 
struct rider allriders[50];//所有骑手信息 
void destory(LISTNODEPTR);

int main()
{
    int buytemp=0;//判断是否重新划分区域的辅助变量 
    input();//进行输入 
    buytemp=buy();//判断是否购买骑手并操作
	while(temp==0)//正常派送循环 
	{
		if(buytemp!=0) //若购买了骑手 
		{
		    divide();//重新划分区域 
		}
		decide();//分配订单
		
		txtoutput();//文本输出 
		pictureoutput();//图形化输出
		
		if(all==finish) temp=3;
		bestwaywhile();//为所有骑手规划路径 
		
		preover=over;
		prefinish=finish;//保留上一时刻完成数，超时数 
		
		addwhile();//使所有骑手移动并进行状态改变 
		time++;//时间推进一个时间单位 
		buytemp=buy();//判断是否购买骑手并操作	
	    
		//system("pause"); 
	    Sleep(2000);
	}

    if(temp==1) printf("订单被恶意抛弃\n");//因为订单被恶意抛弃而出循环 
    else if(temp==2) printf("已破产\n");//因为已破产而出循环 
    else if(temp==3) printf("订单已全部派送完\n");//因为订单已全部派送完而退出循环 
	else printf("三个时间单位未派单成功\n");//因为三个时间单位未派单成功而出循环 
	destory(firstorder);
    return 0;

}	

void destory(LISTNODEPTR headPtr)
{

	LISTNODEPTR tempPtr = NULL;

	while(headPtr != NULL)
	{

		tempPtr = headPtr;
		headPtr = headPtr->orderptr;
		free(tempPtr);
	}

}
