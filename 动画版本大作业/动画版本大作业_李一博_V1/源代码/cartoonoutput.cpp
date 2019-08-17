#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include"head.h"
/*include区*/
 
#define length 50
#define width 40 
/*宏定义区*/ 

extern int money,ridernumber,time,allaccept,over,finish;//非静态全局变量和起初始值的定义 
extern struct order * firstorder;//头订单指针 
extern struct rider allriders[50];//所有骑手信息 
/*变量,指针,结构区*/ 

void background(); // 绘制背景 
void variableoutput();//输出时间、钱、接单数、完成数、超时数等变量 
void otheroutput();//输出骑手、餐馆、食客

extern void cartoonoutput()//动画输出 
{
	
	background();//绘制背景 
	variableoutput();//输出变量 
	otheroutput();//输出图形 
		
}

void background()//绘制背景 
{
	int i,j;
	int x = 80, y = 80;
	PIMAGE img;//声明img为图片类型的变量 

	
	setbkcolor(WHITE); //设置底色 
	setcolor(BLACK);
	setfillcolor( EGERGB(255,216,103) );//设置方块填充的颜色为浅橙色 
	for(i = 0 ; i < 9 ; i++)//绘制9X9方块 
	{
		for (j = 0 ; j < 9 ; j++)
		{
			bar(x, y, x+length, y+width);
			x = x + length + 30;
	}
		y = y + width + 25;
		x = 80;
	} 
	
	setbkmode(TRANSPARENT);//将字体背景色设为透明 
	setfont(30, 0, "华文楷体");//指定字体高度宽度
	
	outtextxy(440, 20, "外卖派单模拟系统");
	outtextxy(900, 100, "时间：");
	outtextxy(900, 160, "钱：");
	outtextxy(900, 220, "接单数："); 
	outtextxy(900, 280, "完成数：");
	outtextxy(900, 340, "发起订单编号：");
	outtextxy(900, 400, "完成订单编号："); 
	
	img=newimage();
	getimage(img, "按钮1.jpg", 0, 0);
	putimage(900, 450, img);//将退出按钮图片贴图 
}

void variableoutput()//输出变量 
{
	xyprintf(990, 100, "%d", time);//输出时间 
	xyprintf(990, 160, "%d", money);//金钱 
	xyprintf(1020, 220, "%d", allaccept);//总接单数 
	xyprintf(1020, 280, "%d", finish);//完成数 

}

void otheroutput()//输出图形 
{
	struct order *allorders[300], *orderptr = firstorder;//需要图形展示的订单指针数组，订单指针 
	int i, j, x, y, a, b;//i，j为循环变量，x，y为输出位置，a,b代表xy坐标，用于赋值 
	int temp = 0, m = 0, q = 0;// temp为辅助判断变量，m,q用于计数 
	int neworders[10];
	
	for(i = 0,j = 0; orderptr!=NULL && orderptr->time <= time; i++)//判断是否已经发出的订单 
	{
		
		if(orderptr->current < 3)//判断是否未配送完，未配送完则需要图形化展示 
		{   
		    allorders[j] = orderptr;//将经过筛选的订单的指针存入订单指针数组 
			j++;
		} 
		
		if(orderptr->time == time)//将当前时间发出的订单编号输出 
		{
			setfont(30, 0, "华文楷体");
			xyprintf(1100+q, 340, "%d", orderptr->num); 
  			q += 40;
		}
		
		orderptr = orderptr->orderptr;//判断下一个订单 
		
	}


	for(x = 0 ; x < 17 ; x++)//完成0到16行的输出 
	{
		for(y = 0 ; y < 17 ; y++)//输出第y列的情况 
		{
	    	for(i = 0 ; i < j && temp == 0 ; i++)//寻找x行y列是否有餐馆或食客 
			{
				
				if(allorders[i]->cx == x && allorders[i]->cy == y) temp=1;//x行y列有餐馆 
				if(allorders[i]->sx == x && allorders[i]->sy == y) temp=2;//x行y列有食客 
				
		 		if(temp == 1)//有餐馆 
				{
					
					setfont(20, 0, "华文楷体");
					setfillcolor(EGERGB(255, 177, 208));
					bar((y/2)*80 + 80, (x/2)* 65 + 80, (y/2)*80 + 80 + length, (x/2)*65 + 80 + width);
					/*高亮餐馆为粉色*/ 
					outtextxy(98 + 80*(y/2), 90 + 65*(x/2), "A");//输出餐馆，即A 
					
				} 
				else if(temp == 2)//有食客 
				{
					
					setfont(20, 0, "华文楷体");
					setfillcolor(EGERGB(255, 177, 208));
					bar((y/2)*80 + 80, (x/2)* 65 + 80, (y/2)*80 + 80 + length, (x/2)*65 + 80 + width);
					/*高亮食客为粉色*/ 
					outtextxy(98 + 80*(y/2), 90 + 65*(x/2), "B");//输出食客，即B
					
				}
				
			}
			
		 	temp = 0;//辅助判断变量归位 
		 	
		 	for(i = 0 ; i < ridernumber && temp == 0 ; i++)//判断x行y列是否有骑手 
		 	{
		 		
				if(allriders[i].x == x && allriders[i].y == y) temp=1;//x行y列有骑手	
		 
		 		if(temp == 1) //输出骑手 
		 		{
		 			
		 			setfont(15, 0, "华文楷体");
		 		
					if(y%2 == 0)//在横街道 
					xyprintf(90 + 80*(y/2), 125 + 65*(x-1)/2, "骑手%d", i);
					else if(x%2 == 0)//在纵街道 
					xyprintf(128 + 80*(y-1)/2, 88 + 65*(x/2), "骑手%d", i);
					
				}
				
			}//end of for 
			
			temp=0;//辅助判断变量归位 
			
		}// end of for 
	   
	}//end of for 
	

	for(i = 0; i < ridernumber; i++)//输出高亮 
  	{
  		
  		if(allriders[i].stop == 1)//如果停靠在餐馆 ，高亮方块 
  		{
  			
  			a = allriders[i].finaltask->cx;
  			b = allriders[i].finaltask->cy; 
  			
  			setfont(20, 0, "华文楷体");
  			setfillcolor(EGERGB(126, 202, 218));
			bar((b/2)*80 + 80, (a/2)*65 + 80, (b/2)*80 + 80 + length, (a/2)*65 + 80 + width);
			/*高亮停靠处的餐馆为蓝色*/ 
			outtextxy(98 + 80*(b/2), 90 + 65*(a/2), "A");//输出餐馆，即A 
			
			allriders[i].finaltask = NULL;
			allriders[i].stop = 0;//变为不停靠的状态 
			
  		} 
		else if( allriders[i].stop == 2 ) //如果停靠在食客，此时顺便输出完成的订单编号，并高亮方块 
  		{
  			
  			a = allriders[i].finaltask->sx;
  			b = allriders[i].finaltask->sy;
  			
  			setfont(30, 0, "华文楷体");
  			xyprintf(1100 + m, 400, "%d", allriders[i].finaltask->num); 
  			m += 40;
  			
  			setfont(20, 0, "华文楷体");
  			setfillcolor(EGERGB(126, 202, 218));
			bar((b/2)*80 + 80, (a/2)*65 + 80, (b/2)*80 + 80 + length, (a/2)*65 + 80 + width);
			/*高亮停靠处的食客为蓝色*/ 
			outtextxy(98 + 80*(b/2), 90 + 65*(a/2), "B");//输出食客，即B 
			
			allriders[i].finaltask = NULL;
			allriders[i].stop = 0;//变为不停靠的状态 	
			
		}
		
	}//end of for
	
	 
 } 
 
 
