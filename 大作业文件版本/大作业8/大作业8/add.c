#include<stdio.h>
#include<stdlib.h>
#include "head.h"
#include "main.h"
#define LIMIT 30
#define BIGLIMIT 60
extern int time;
extern struct order * firstorder;//头订单指针 
void addwhile()
{
	int i,j;
	struct order *ptr=firstorder;
	
	for(i=0;i<ridernumber;i++) 
	{
		add(allriders,i);
	}
	if(money<0)//判断是否破产 
	{
		temp=2;
	}
	for(i=0;i<ridernumber;i++)
	{
	    for(j=0;j<allriders[i].currentnumber;j++)
		{
			if(allriders[i].temporarytask[j]->time+LIMIT<time)
			{
				allriders[i].over++;
				over++;
				money-=50;
			}
			else if(allriders[i].temporarytask[j]+BIGLIMIT<time)
			    temp=1;
		}	
	} 
	while(ptr->time<time&&ptr->orderptr!=NULL)
	{
		if(ptr->current==0)
		{
			if(ptr->time+3<time)
			    temp=4;
		}
		ptr=ptr->orderptr;
	}
}
void add(struct rider *allriders,int i)
{
	int x3,y3,j;//骑手当前的目标点 
	int x=allriders[i].x,y=allriders[i].y;//骑手当前坐标 
	if(allriders[i].finaltask==NULL) 
	{
		return ;
	}
	if(allriders[i].finaltask->current==1)//如果骑手取餐 
	{
		x3=allriders[i].finaltask->cx;
		y3=allriders[i].finaltask->cy;
	}
	else if(allriders[i].finaltask->current==2)//如果骑手送餐
	{
		x3=allriders[i].finaltask->sx;
		y3=allriders[i].finaltask->sy;
	} 
	if(x%2==1)//如果骑手原来在横街道上 
	{
		if(x==x3-1||x==x3+1)//如果骑手在目标点的相邻街道上（这种情况不用转弯） 
		{
			if(y==y3)//如果已经到了
			{
				meet(allriders,i);
			}
			else//如果没到 ,只需改变y即可 ，不需要转弯 
			{
				if(y>y3)
				{
					allriders[i].y-=2;
					if(y==y3+2)//如果走完后到了 
					{
						meet(allriders,i);
					}
				}	
				else
				{
					allriders[i].y+=2;
					if(y==y3-2)//如果走完后到了 
					{
						meet(allriders,i);
					}
				}
			} 
		}
		else//需要转弯的情况
		{
			if(y==y3)
			{
				if(y==0)//如果在最左边,只能右转 
				{
					allriders[i].y+=1;
					if(x>x3)
					{
						allriders[i].x-=1;
					}
					else
					{
						allriders[i].x+=1;
					}
				} 
				else if(y==16)//如果在最右边，只能左转 
				{
					allriders[i].y-=1;
					if(x>x3)
					{
						allriders[i].x-=1;
					}
					else
					{
						allriders[i].x+=1;
					}
				} 
				else//都可以 
				{
					allriders[i].y-=1;
					if(x>x3)
					{
						allriders[i].x-=1;
					}
					else
					{
						allriders[i].x+=1;
					}
				} 
			}
			else if(y==y3-2)//到达转弯点 
			{
				allriders[i].y+=1;
				if(x>x3)
				{
					allriders[i].x-=1;
				}
				else
				{
					allriders[i].x+=1;
				}
			}
			else if(y==y3+2)//到达转弯点 
			{
				allriders[i].y-=1;
				if(x>x3)
				{
					allriders[i].x-=1;
				}
				else
				{
					allriders[i].x+=1;
				}
			}
			else if(y<y3-2)//不是转弯点 
			{
				allriders[i].y+=2;
			}
			else if(y>y3+2)//不是转弯点 
			{
				allriders[i].y-=2;
			}
		} 
	}
	if(y%2==1)//如果骑手原来在横街道上 
	{
		if(y==y3-1||y==y3+1)//如果骑手在目标点的相邻街道上（这种情况不用转弯） 
		{
			if(x==x3)//如果已经到了
			{
				meet(allriders,i);
			}
			else//如果没到 ,只需改变y即可 ，不需要转弯 
			{
				if(x>x3)
				{
					allriders[i].x-=2;
					if(x==x3+2)//如果走完后到了 
					{
						meet(allriders,i);
					}
				}	
				else
				{
					allriders[i].x+=2;
					if(x==x3-2)//如果走完后到了 
					{
						meet(allriders,i);
					}
				}
			} 
		}
		else//需要转弯的情况
		{
			if(x==x3)
			{
				if(x==0)//如果在最左边,只能右转 
				{
					allriders[i].x+=1;
					if(y>y3)
					{
						allriders[i].y-=1;
					}
					else
					{
						allriders[i].y+=1;
					}
				} 
				else if(x==16)//如果在最右边，只能左转 
				{
					allriders[i].x-=1;
					if(y>y3)
					{
						allriders[i].y-=1;
					}
					else
					{
						allriders[i].y+=1;
					}
				} 
				else//都可以 
				{
					allriders[i].x-=1;
					if(y>y3)
					{
						allriders[i].y-=1;
					}
					else
					{
						allriders[i].y+=1;
					}
				} 
			}
			else if(x==x3-2)//到达转弯点 
			{
				allriders[i].x+=1;
				if(y>y3)
				{
					allriders[i].y-=1;
				}
				else
				{
					allriders[i].y+=1;
				}
			}
			else if(x==x3+2)//到达转弯点 
			{
				allriders[i].x-=1;
				if(y>y3)
				{
					allriders[i].y-=1;
				}
				else
				{
					allriders[i].y+=1;
				}
			}
			else if(x<x3-2)//不是转弯点 
			{
				allriders[i].x+=2;
			}
			else if(x>x3+2)//不是转弯点 
			{
				allriders[i].x-=2;
			}
		} 
	}
}
void meet(struct rider *allriders,int i)
{
	allriders[i].change=0;//到达目标点需要决定下一个目标点 
	if(allriders[i].finaltask->current==1)//如果骑手取餐 
	{
		allriders[i].stop=1;//停靠在餐馆 
		allriders[i].finaltask->current=2;//改变订单状态为待送餐 
	}
	else if(allriders[i].finaltask->current==2)//如果骑手送餐 
	{
		allriders[i].stop=2;//停靠在食客 
		int a=allriders[i].currentnumber;//骑手的订单数组中的数量
		int tem,j;//目标订单在数组中的序号 
		int flag=0;
		for(j=0;j<a&&flag==0;j++)
		{
			if(allriders[i].finaltask->num==allriders[i].temporarytask[j]->num)//如果目标订单和数组中的这个订单编号一样 
			{
				tem=j;
				flag=1;
			}	
		} 
		for(j=tem;j<a-1;j++)
		{
			allriders[i].temporarytask[j]=allriders[i].temporarytask[j+1];//数组依次前移 
		}
		allriders[i].currentnumber-=1;
		allriders[i].temporarytask[a-1]=NULL;
        if(time<=allriders[i].finaltask->time+LIMIT)//如果未超时 ，那么挣10 
		{
			money+=10;
			allriders[i].finish+=1;//骑手订单完成数+1 
			finish++;
			allriders[i].finaltask->current=3;
		}
		else if(time<=allriders[i].finaltask->time+BIGLIMIT)
		{
			allriders[i].finish++;
			finish++;
			allriders[i].finaltask->current=4;
		}
		else temp=1;
	} 
}
