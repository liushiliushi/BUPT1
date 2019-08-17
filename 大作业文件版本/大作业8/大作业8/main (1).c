#include<stdio.h>
#include<stdlib.h>
#include<head.h>//包含定义好的头文件 
int money=100,ridernumber=3,time=0,temp=0,accept=0,over=0,finish=0;//非静态全局变量和起初始值的定义 
struct order *firstorder;//头订单指针 
struct rider allriders[50];//所有骑手信息 
main()
{
	int buy=0//判断是否重新划分区域的辅助变量 
    input();//进行输入 
    devide();//划分3个骑手的区域 
	while(temp==0)//正常派送循环 
	{
		if(buy!=0) //若购买了骑手 
		{
		    devide();//划分区域 
			buy=0;	// 判断是否重新划分区域的辅助变量归位 
		}
		
		decide();//分配订单 
		bestwaywhile();//为所有骑手规划路径 
		addwhile();//使所有骑手移动并进行状态改变 
		time++;//时间推进一个时间单位 
		pictureoutput();//图形化输出 
		txtoutput();//文本输出 
		buy=buy();//判断是否购买骑手并操作 
    }
    
    if(temp==0) prnitf("订单全部派送完\n");//因为订单全部派完而出循环 
    else if(temp==1) printf("订单被恶意抛弃\n");//因为订单被恶意抛弃而出循环 
    else if(temp==2) printf("已破产\n");//因为已破产而出循环 
	else printf("三个时间单位未派单成功\n");//因为三个时间单位未派单成功而出循环 
	return 0;
	 
}	







 





























} 
