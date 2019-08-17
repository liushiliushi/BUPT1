#include<stdio.h>
#include<stdlib.h>
#include"head.h" 

extern int money,ridernumber,time,temp,accept,over,finish,prefinish,preover;//非静态全局变量和起初始值的定义 
extern struct order * firstorder;//头订单指针 
extern struct rider allriders[50];//所有骑手信息 
extern txtoutput()//文本输出函数    
{
  	int i,m,j = 0;//为骑手情况输出做准备 
  	FILE *p;//指向文件output.txt的指针 

  	p=fopen("output.txt","a");//打开文件 
  	fprintf( p , "时间：%d\n" , time );//输出当前时间 
  	fprintf( p , "钱：%d\n" , money );//输出当前钱数 
  	fprintf( p , "接单数；%d\n" , accept );//输出当前接单数  
  	fprintf( p , "完成数：%d； 结单：" , finish );//输出当前完成数 
	for( m = 0 ; m < ridernumber ; m++ )//遍历每一个骑手，如果到了食客处，则结单 
	{
		if(allriders[m].stop==2)//如果停靠在食客 
		{
			fprintf( p , "%d" , allriders[m].finaltask->num );
			j++;
			if(j!=finish-prefinish)
			fprintf( p , " " );
		}
	}
	fprintf( p , "；\n" );
	j=0;
	fprintf( p , "超时数：%d； 罚单：" , over );//输出当前超时数 
  	for( m=0 ; m < ridernumber ; m++ )
  	{
  		if( allriders[m].fadan!=0 )
		{
			fprintf( p , "%d" , allriders[m].fadan );
			j++;
			if(j!=over-preover )
			fprintf(p," ");
		}	
		allriders[m].fadan=0;
	}
	fprintf(p,"；\n");
	for(i=0;i<ridernumber;i++)
  	{ 
  		fprintf(p,"骑手%d位置：%d，%d；停靠：",i,allriders[i].x,allriders[i].y);//输出所有骑手位置 
		if(allriders[i].stop==0)//如果不停靠 
		fprintf(p,"；\n");
		else if(allriders[i].stop==1)//如果停靠在餐馆 
		fprintf(p,"餐馆 %d %d；\n",allriders[i].finaltask->cx,allriders[i].finaltask->cy);
		else if(allriders[i].stop==2)//如果停靠在食客 
		fprintf(p,"食客 %d %d；\n",allriders[i].finaltask->sx,allriders[i].finaltask->sy);
	} 
	fclose(p);//关闭文件 
} 
extern pictureoutput()//图形输出函数 
{
	struct order *allorders[300],*orderptr=firstorder;//需要图形展示的订单指针数组，订单指针 
	int i,j,x,y,temp=0,m,q;//x，y为输出位置，i，j为循环变量，temp为辅助判断变量,q为计数变量 
	for(i=0,j=0;orderptr!=NULL&&orderptr->time<=time;i++)//判断是否已经发出的订单 
	{
		if(orderptr->current<3)//判断是否未配送完 
		{   
		    allorders[j]=orderptr;//将经过筛选的订单的指针存入订单指针数组 
			j++;
		}
		orderptr=orderptr->orderptr;//判断下一个订单 
	} //最终将需要图形展示的订单的指针全部存入订单指针数组中
	//   	printf("%d",j); 
	for(x=0;x<16;x++)//完成0到15行的输出 
	{
	   printf(" ______        ______        ______        ______        ______        ______        ______        ______        ______ \n");
	   printf("|      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |\n");//输出图形上顶 
	   for(y=0;y<16;y++)//输出第x行的情况 
	   {
	     for(i=0;i<j&&temp==0;i++)//寻找x行y列是否有餐馆或食客 
		 {
		   if(allorders[i]->cx==x&&allorders[i]->cy==y) temp=1;//x行y列有餐馆 
		   if(allorders[i]->sx==x&&allorders[i]->sy==y) temp=2;//x行y列有食客 
		  } 
		  	
		 if(temp==1) printf("| 餐馆 |");//输出餐馆 
		 else if(temp==2) printf("| 食客 |");//输出食客 
		 else printf("|      |");//表示既无餐馆也无食客 
		 y++;//列数加1 
		 temp=0;//辅助判断变量归位 
		 for(i=0;i<ridernumber&&temp==0;i++)//判断x行y列是否有骑手 
		 {
		   if(allriders[i].x==x&&allriders[i].y==y) temp=1;//x行y列有骑手	
		 } 
		 if(temp==1) printf(" 骑手 ");//输出骑手 
		 else printf("      ");//输出骑手为空 
		 temp=0;//辅助判断变量归位 
	   }
	   for(i=0;i<j&&temp==0;i++)//判断x行16列是否有餐馆或食客 
	    {
		   if(allorders[i]->cx==x&&allorders[i]->cy==y) temp=1;//x行16列有餐馆 
		   if(allorders[i]->sx==x&&allorders[i]->sy==y) temp=2;//x行16列有食客 
	    }
	    if(temp==1) printf("| 餐馆 |\n");//x行16列输出餐馆 
		else if(temp==2) printf("| 食客 |\n");//x行16列输出食客 
		else printf("|      |\n");//x行16列输出为空 
		temp=0;//辅助判断变量归位 
		x++;//行数加1 
		printf("|______|      |______|      |______|      |______|      |______|      |______|      |______|      |______|      |______|\n");//输出图形下底 
		printf("\n");
		for(y=0;y<16;y+=2)//输出x行情况 
	   {
		 for(i=0;i<ridernumber&&temp==0;i++)//判断x行y列是否有骑手 
		 {
		   if(allriders[i].x==x&&allriders[i].y==y) temp=1;//x行y列有骑手	
		 } 
		 if(temp==1) printf("  骑手        ");//输出骑手 
		 else printf("              ");//输出无骑手 
		 temp=0;//辅助判断变量归位 
	   }
	   for(i=0;i<ridernumber&&temp==0;i++)//判断x行16列是否有骑手 
		 {
		   if(allriders[i].x==x&&allriders[i].y==y) temp=1;	//x行16列有骑手 
		 } 
		 if(temp==1) printf("  骑手  \n");//输出骑手 
		 else printf("        \n");//输出无骑手 
		 temp=0;//判断变量归位 
	}
	printf(" ______        ______        ______        ______        ______        ______        ______        ______        ______ \n");
	printf("|      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |\n");//输出16行上顶 
	for(y=0;y<16;y++)//输出16行情况 
	{
	    for(i=0;i<j&&temp==0;i++)//判断16行餐馆或食客情况 
		{
		   if(allorders[i]->cx==x&&allorders[i]->cy==y) temp=1;//16行y列有餐馆 
		   if(allorders[i]->sx==x&&allorders[i]->sy==y) temp=2;//16行y列有食客 
		}	
		if(temp==1) printf("| 餐馆 |");//输出餐馆 
		else if(temp==2) printf("| 食客 |");//输出食客 
		else printf("|      |");//输出既无餐馆也无食客 
		y++;//列数加一 
		temp=0;//辅助判断变量归位 
		for(i=0;i<ridernumber&&temp==0;i++)//判断16行y列是否有骑手 
		{
		  if(allriders[i].x==x&&allriders[i].y==y) temp=1;//有骑手	
		} 
		if(temp==1) printf(" 骑手 ");//输出骑手 
		else printf("      ");//输出空 
		temp=0;//辅助判断变量归位  
	}
	for(i=0;i<j&&temp==0;i++)//输出16行16列情况 
	{
		if(allorders[i]->cx==x&&allorders[i]->cy==y) temp=1;//16行16列有餐馆 
		if(allorders[i]->sx==x&&allorders[i]->sy==y) temp=2;//16行16列有食客 
	}
	if(temp==1) printf("| 餐馆 |\n");//16行16列输出餐馆 
	else if(temp==2) printf("| 食客 |\n");//16行16列输出食客 
	else printf("|      |\n");//16行16列输出空 
	temp=0;
		printf("|______|      |______|      |______|      |______|      |______|      |______|      |______|      |______|      |______|\n");//输出整个图形下底 
	 
	printf("时间：%d\n",time);//输出当前时间 
	printf("钱：%d\n",money);//输出当前钱数 
	printf("接单数：%d\n",accept);//输出当前接单数 
	printf("完成数：%d； 结单：",finish);//输出当前完成数 
	q=0; 
	for(m=0;m<ridernumber;m++)//遍历每一个骑手，如果到了食客处，则结单 
	{
		if(allriders[m].stop==2)//如果停靠在食客 
		{
			printf("%d",allriders[m].finaltask->num);
			q++;
			if(q!=finish-prefinish)
			printf(" ");
		}
	}
	printf("；\n");
	q=0;
	printf("超时数：%d； 罚单：",over);//输出当前超时数 
  	for(m=0;m<ridernumber;m++)
  	{
  		if(allriders[m].fadan!=0)
		{
			printf("%d",allriders[m].fadan);
			q++;
			if(q!=over-preover)
			printf(" ");
		}	
		allriders[m].fadan=0;
	}
	printf("；\n");
	for(i=0;i<ridernumber;i++)
  	{ 
  		printf("骑手%d位置：%d，%d；停靠：",i,allriders[i].x,allriders[i].y);//输出所有骑手位置 
		if(allriders[i].stop==0)//如果不停靠 
		{
			printf("；\n");
		}
		else if(allriders[i].stop==1)//如果停靠在餐馆 
		{
			printf("餐馆 %d %d；\n",allriders[i].finaltask->cx,allriders[i].finaltask->cy);
			allriders[i].finaltask=NULL;
			allriders[i].stop=0;//变为不停靠的状态 
		}
		else if(allriders[i].stop==2)//如果停靠在食客 
		{
			printf("食客 %d %d；\n",allriders[i].finaltask->sx,allriders[i].finaltask->sy);
			allriders[i].finaltask=NULL;
			allriders[i].stop=0;//变为不停靠的状态 
		}
	} 
}   
