#include<stdio.h>
#include<stdlib.h>
#include "head.h"
#include "main.h"
/*include区*/
 
#define LIMIT 30
#define BIGLIMIT 60
/*宏定义区*/ 

extern int time;
extern struct order * firstorder;//头订单指针 
/*结构，类，变量，指针定义区*/
 
void add(struct rider *,int);
void meet(struct rider *,int);

void addwhile()//对所有骑手进行移动 
{
	int i,j;
	struct order *ptr = firstorder;
	
	if( firstorder==NULL ) return;//当前无订单 
	
	for( i = 0;i < ridernumber;i++ ) //对所有骑手进行移动 
	{
		add(allriders,i);//对i号骑手进行移动 
	}
	
	if( money < 0 )//判断是否破产 
	{
		temp = 2;
	}
	
	for( i = 0;i < ridernumber;i++ )//判断是否超时或恶意弃单 
	{
	    for( j = 0;j < allriders[i].currentnumber;j++ )
		{
			if( allriders[i].temporarytask[j]->time + LIMIT==time )//判断是否超时 
			{
				allriders[i].over++;//骑手超时数加一 
				over++;//总超时数加一 
				money -= 50;//罚钱50 
			}
			else if( allriders[i].temporarytask[j]->time + BIGLIMIT < time )//判断是否恶意弃单 
			    temp = 1;
		}	
	} 
	
	while( ptr->time < time && ptr->orderptr!=NULL )//判断是否3个时间单位内派单成功 
	{
		if( ptr->current==0 )//是否该单未派单 
		{
			if( ptr->time + 3 < time )
			    temp = 4;
		}
		ptr = ptr->orderptr;
	}
}

void add(struct rider *allriders,int i)//对i号骑手进行移动 
{
	int x3,y3,j;//骑手当前的目标点 
	int x = allriders[i].x,y = allriders[i].y;//骑手当前坐标 
	
	if( allriders[i].finaltask==NULL ) //是否当前骑手无待送单 
	{
		return ;
	}
	
	if( allriders[i].finaltask->current==1 )//如果骑手取餐 
	{
		x3 = allriders[i].finaltask->cx;
		y3 = allriders[i].finaltask->cy;
	}
	else if( allriders[i].finaltask->current==2 )//如果骑手送餐
	{
		x3 = allriders[i].finaltask->sx;
		y3 = allriders[i].finaltask->sy;
	} 
	
	if( x % 2==1 )//如果骑手原来在横街道上 
	{
		if( x==x3 - 1 || x==x3 + 1 )//如果骑手在目标点的相邻街道上（这种情况不用转弯） 
		{
			if( y==y3 )//如果已经到了
			{
				meet(allriders,i);
			}
			else//如果没到 ,只需改变y即可 ，不需要转弯 
			{
				if(y > y3)
				{
					allriders[i].y -= 2;
					if( y==y3 + 2 )//如果走完后到了 
					{
						meet(allriders,i);
					}
				}	
				else
				{
					allriders[i].y += 2;
					if( y==y3 - 2 )//如果走完后到了 
					{
						meet(allriders,i);
					}
				}
			} 
		}
		else//需要转弯的情况
		{
			if( y==y3 )
			{
				if( y==0 )//如果在最左边,只能右转 
				{
					allriders[i].y += 1;
					if( x > x3 )
					{
						allriders[i].x -= 1;
					}
					else
					{
						allriders[i].x += 1;
					}
				} 
				else if( y==16 )//如果在最右边，只能左转 
				{
					allriders[i].y -= 1;
					if( x > x3 )
					{
						allriders[i].x -= 1;
					}
					else
					{
						allriders[i].x += 1;
					}
				} 
				else//都可以 
				{
					allriders[i].y -= 1;
					if( x > x3 )
					{
						allriders[i].x -= 1;
					}
					else
					{
						allriders[i].x += 1;
					}
				} 
			}
			else if( y==y3 - 2 )//到达转弯点 
			{
				allriders[i].y += 1;
				if( x > x3 )
				{
					allriders[i].x -= 1;
				}
				else
				{
					allriders[i].x += 1;
				}
			}
			else if( y==y3 + 2 )//到达转弯点 
			{
				allriders[i].y -= 1;
				if( x > x3 )
				{
					allriders[i].x -= 1;
				}
				else
				{
					allriders[i].x += 1;
				}
			}
			else if( y < y3 - 2 )//不是转弯点 
			{
				allriders[i].y += 2;
			}
			else if( y > y3 + 2 )//不是转弯点 
			{
				allriders[i].y -= 2;
			}
		} 
	}
	
	if( y % 2==1 )//如果骑手原来在竖街道上 
	{
		if( y==y3 - 1 || y==y3 + 1 )//如果骑手在目标点的相邻街道上（这种情况不用转弯） 
		{
			if( x==x3 )//如果已经到了
			{
				meet(allriders,i);
			}
			else//如果没到 ,只需改变y即可 ，不需要转弯 
			{
				if( x > x3 ) 
				{
					allriders[i].x -= 2;
					if( x==x3 + 2 )//如果走完后到了 
					{
						meet(allriders,i);
					}
				}	
				else
				{
					allriders[i].x += 2;
					if( x==x3 - 2 )//如果走完后到了 
					{
						meet(allriders,i);
					}
				}
			} 
		}
		else//需要转弯的情况
		{
			if( x==x3 )
			{
				if( x==0 )//如果在最左边,只能右转 
				{
					allriders[i].x += 1;
					if( y > y3 )
					{
						allriders[i].y -= 1;
					}
					else
					{
						allriders[i].y += 1;
					}
				} 
				else if( x==16 )//如果在最右边，只能左转 
				{
					allriders[i].x -= 1;
					if( y > y3 )
					{
						allriders[i].y -= 1;
					}
					else
					{
						allriders[i].y += 1;
					}
				} 
				else//都可以 
				{
					allriders[i].x -= 1;
					if( y > y3 )
					{
						allriders[i].y -= 1;
					}
					else
					{
						allriders[i].y += 1;
					}
				} 
			}
			else if( x==x3 - 2 )//到达转弯点 
			{
				allriders[i].x += 1;
				if( y > y3 )
				{
					allriders[i].y -= 1;
				}
				else
				{
					allriders[i].y += 1;
				}
			}
			else if( x==x3 + 2 )//到达转弯点 
			{
				allriders[i].x -= 1;
				if( y > y3 )
				{
					allriders[i].y -= 1;
				}
				else
				{
					allriders[i].y += 1;
				}
			}
			else if( x < x3 - 2 )//不是转弯点 
			{
				allriders[i].x += 2;
			}
			else if( x > x3 + 2 )//不是转弯点 
			{
				allriders[i].x -= 2;
			}
		} 
	}
}

void meet(struct rider *allriders,int i)
{
	int flag = 0,a,tem,j;//骑手的订单数组中的数量,目标订单在数组中的序号 
	
    allriders[i].change = 0;//到达目标点需要决定下一个目标点 
    
	if( allriders[i].finaltask->current==1 )//如果骑手取餐 
	{
		allriders[i].stop = 1;//停靠在餐馆 
		allriders[i].finaltask->current = 2;//改变订单状态为待送餐 
	}
	else if( allriders[i].finaltask->current==2 )//如果骑手送餐 
	{
		allriders[i].stop = 2;//停靠在食客 
		a=allriders[i].currentnumber;//骑手的订单数组中的数量
		
		for( j = 0;j < a && flag==0;j++ )
		{
			if( allriders[i].finaltask->num==allriders[i].temporarytask[j]->num )//如果目标订单和数组中的这个订单编号一样 
			{
				tem = j;
				flag = 1;
			}	
		} 
		for( j = tem;j < a - 1;j++ )
		{
			allriders[i].temporarytask[j] = allriders[i].temporarytask[j+1];//数组依次前移 
		}
		allriders[i].currentnumber -= 1;
		allriders[i].temporarytask[a-1] = NULL;
		
        if( time <= allriders[i].finaltask->time + LIMIT )//如果未超时 ，那么挣10 
		{
			money += 10;//赚10元 
			allriders[i].finish += 1;//骑手订单完成数+1 
			finish++;//总完成数加一 
			allriders[i].finaltask->current = 3;//该单状态改为已完成 
		}
		else if(time <= allriders[i].finaltask->time + BIGLIMIT)//该单已经超时且没有恶意弃单 
		{
			allriders[i].finish++;//该骑手完成数加一 
			finish++;//总完成数加一 
			allriders[i].finaltask->current = 4;//改单状态为被超时完成 
		}
		else temp = 1;
	} 
}
