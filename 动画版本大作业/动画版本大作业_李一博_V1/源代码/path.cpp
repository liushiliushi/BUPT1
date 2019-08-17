#include<stdio.h>
#include<math.h> 
#include<stdlib.h>
#include "head.h"//包含所需头文件 
#include "main.h"
/*include区*/
 
#define LIMIT 30//限制派送的时间 

struct pathpoint{ 
	int x,y,time,n;//x,y是该任务点横纵坐标，time是到达时间，n:0餐馆/1食客 
	struct order *order;//该任务点所属的订单指针 
};//任务点结构体定义 
extern int ridernumber;
/*结构体，变量，指针定义区*/ 

void bestway(int);//函数申明 


extern void bestwaywhile(void)
{
	int n = ridernumber,i; 
	
	for( i = 0;i < n;i++ )//遍历所有骑手 
	{
		if( allriders[i].change==0 )//i号骑手是否需要重新规划路线 
		{
			bestway(i);//为i号骑手重新规划路线 
			allriders[i].change = 1;//将判断辅助量归位 
		}
	}
}

void bestway(int num)//优化路线函数，num为所需优化路线的骑手序号 
{
	int i,j,k,a,b,c,d,e,f,number = 0,timemin,timer,temp; 
	struct pathpoint allpathpoint[100];//定义任务点数组 
	
	if(allriders[num].temporarytask[0]==NULL) return;
	
	for(i = 0,number = 0;i < (allriders[num].currentnumber);i++ )//遍历骑手所有订单信息填充任务点数组，number为总任务点数 
	{
		if( allriders[num].temporarytask[i]->current==1 )//当前判断订单待取餐 
		{
			allpathpoint[number].x = allriders[num].temporarytask[i]->cx;//填充任务点横坐标 
			allpathpoint[number].y = allriders[num].temporarytask[i]->cy;//填充任务点纵坐标 
			allpathpoint[number].n = 0;//该任务点为餐馆 
			allpathpoint[number].order = allriders[num].temporarytask[i];//填充该任务点所属订单指针 
			number += 1;//总任务点数加一 
			allpathpoint[number].x = allriders[num].temporarytask[i]->sx;//填充任务点横坐标 
			allpathpoint[number].y = allriders[num].temporarytask[i]->sy;//填充任务点纵坐标 
			allpathpoint[number].n = 1;//该任务点是食客 
			allpathpoint[number].order = allriders[num].temporarytask[i];//填充该任务点所属订单指针 
			number += 1;//总任务点数加一 
		}
		
		if( allriders[num].temporarytask[i]->current==2 )//当前的判断订单待送餐 
		{
			allpathpoint[number].x = allriders[num].temporarytask[i]->sx;//填充该任务点横坐标 
			allpathpoint[number].y = allriders[num].temporarytask[i]->sy;//填充该任务点纵坐标 
			allpathpoint[number].n = 1;//该任务点食客 
			allpathpoint[number].order = allriders[num].temporarytask[i];//填充该任务点所属订单指针 
			number += 1;//总任务数加一 
		}
	}
	
	if( number >= 6 )//当前任务点数大等于6个 
	{
		struct pathpoint **allpath6[800];//定义长度为800的指向指针的指针数组 
		i = 0;
		number = 0; 
		
		for( a = 0;a < 6;a++ )//第一个任务点序号为a 
		{
			for( b = 0;b < 6;b++ )//第二个任务点序号为b 
			{
				if( b!=a ) //b和a不相同 
				{ 
				    for( c = 0;c < 6;c++ )//第三个任务点序号为c 
					{
				        if( c!=a && c!=b )//c和b和a都不同 
						{
							for( d = 0;d < 6;d++ )//第四个任务点序号为d 
							{
								if( d!=a && d!=b && d!=c )//d和a和b和c均不同 
								{
									for( e = 0;e < 6;e++ )//第五个任务点序号是e 
									{
										if( e!=a && e!=b && e!=c && e!=d )//a,b,c,d,e各不相同 
										{
											for( f = 0;f < 6;f++ )//第六个任务点序号是f 
											{
												if( f!=a && f!=b && f!=c && f!=d && f!=e )//a,b,c,d,e,f各不相同 
												{
													allpath6[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *)*7);
													/*allpath[i]为第i种路线，里面是六个指向任务点的指针*/ 
													while( allpath6[i]==NULL )
													{
														allpath6[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *)*7);
														/*allpath[i]为第i种路线，里面是六个指向任务点的指针*/  
													}
													allpath6[i][0] = &allpathpoint[a];//第i种路线的第一个任务点是a号任务点 
													allpath6[i][1] = &allpathpoint[b];//第i种路线的第二个任务点是b号任务点 
													allpath6[i][2] = &allpathpoint[c];//第i种路线的第三个任务点是c号任务点 
													allpath6[i][3] = &allpathpoint[d];//第i种路线的第四个任务点是d号任务点 
													allpath6[i][4] = &allpathpoint[e];//第i种路线的第五个任务点是e号任务点 
													allpath6[i][5] = &allpathpoint[f];//第i种路线的第六个任务点是f号任务点 
													i++;//路线加一 
												}
											}
										}
									}
								}
							}
						}		
				    }  	
				}
			}
		}//穷举所有任务点排序，即可能路径 
		
		for( i = 0,timemin = 100000;i < 720;i++ )//判断720种路线是否可行并择出最优 
		{
			timemin = 100000;
			
			for( j = 0;j < 6 && allpath6[i]!=NULL;j++ )//判断第i种路线是否有一个订单中食客在餐馆前面 
			{
				if( allpath6[i][j]->order->current==1 && allpath6[i][j]->n==0 )//该任务点属于待取餐订单并且是餐馆 
				{
					for( k = 0;k < 6;k++ )//遍历并找到和该任务点同属一个订单的食客 
					{
						if(allpath6[i][k]->order->current==1 && allpath6[i][k]->n==1 && allpath6[i][j]->order==allpath6[i][k]->order)
						{
							temp = k;//记录该任务点序号 
						}
						/*该任务点是否和上述任务点同属一个订单并且是食客*/  
					}
					
					if(allpath6[i][temp]->order->current==1 && allpath6[i][temp]->n==1 && allpath6[i][j]->order==allpath6[i][temp]->order)
					{
						if( temp < j ) //是否食客在餐馆前面 
						{
							timemin = 150000;
						}
					}
					/*该任务点是否和上述任务点同属一个订单并且是食客*/
				}
			}
			
			if( timemin!=150000 )//是否i号路线未作废 
			{
				timer = (abs(allriders[num].x-allpath6[i][0]->x) + abs(allriders[num].y-allpath6[i][0]->y)) / 2;
				/*骑手到i号路线第一个任务点所需花费时间*/ 
				allpath6[i][0]->time = time + timer;//计算第i号路线第一个任务点到达时间 
				for( j = 0;j < 5;j++ )//计算其余任务点到达时间 
				{
					timer += ((abs(allpath6[i][j]->x-allpath6[i][j+1]->x) + abs(allpath6[i][j]->y-allpath6[i][j+1]->y)) / 2);
					/*计算从第j个任务点到底j+1个任务点所需时间*/ 
					allpath6[i][j+1]->time = timer + time;//计算到第j+1个任务点的时间 
				}
				
				for( j = 0;j < 6 && allpath6[i]!=NULL;j++ )//遍历第i条路线所有任务点，判断其是否超时 
				{
					if( allpath6[i][j]->order->time + LIMIT <= allpath6[i][j]->time )//第i条路线第j个任务点是否超时 
					{
						timemin = 150000;//该任务点超时，该路线废除
				    } 
	            }
	            
	            if( timemin!=150000 )//是否i号路线废除 
	            {
	            	if( timer < timemin )//是否时间最短 
	            	{
	            		timemin = timer;//目前最短时间赋值 
	            		number = i;//目前预备路线赋值 
					}
				}
			}
		}
		
		if( number==0 ) 
		{
			allriders[num].finaltask = allriders[num].temporarytask[0];//没有路线正常时选第一个单为目标点 
		}
		else allriders[num].finaltask = allpath6[number][0]->order;//最佳路线的第一个任务点的订单指针赋给骑手当前目标点
		 
		for( i = 0;i < 720;i++ ) free(allpath6[i]);//释放所有路线 
	}
	
	else if( number==0 ) //骑手当前没有序列 
	{
		allriders[num].finaltask = NULL;//当前任务点赋为空 
		return;//结束函数 
	}
	
	else if( number==1 )//当前只有一个任务点 
	{
		allriders[num].finaltask = allriders[num].temporarytask[0];//唯一任务点的订单指针赋给骑手当前目标点 
	}
	
	else if( number==2 )//当前有两个任务点 
	{
	    if( allpathpoint[0].order==allpathpoint[1].order )//是否两个任务点来自同一订单 
	        allriders[num].finaltask = allpathpoint[0].order;//该订单指针赋给骑手当前目标点 
	    else//两个任务点来自两个指针 
	    {
	        a = ((abs(allriders[num].x - allpathpoint[0].x) + abs(allriders[num].y-allpathpoint[0].y)) / 2 + time);
	        /*先去0号再去1号时到达0号的时间*/
	        b = ((abs(allpathpoint[1].x - allpathpoint[0].x) + abs(allpathpoint[1].y - allpathpoint[0].y)) / 2 + a);
			/*先去0号再去1号时到达1号的时间*/ 
	        c = ((abs(allriders[num].x - allpathpoint[1].x) + abs(allriders[num].y - allpathpoint[1].y)) / 2 + time);
	        /*先去1号再去0号时到达1号的时间*/
		    d = ((abs(allpathpoint[0].x - allpathpoint[1].x) + abs(allpathpoint[0].y - allpathpoint[1].y)) / 2 + c);
			/*先去1号再去0号时到达1号的时间*/  
		    
		    if( b < d || b==d )//是否第一种路线比第二种路线快 
		    {
		    	if( a < allpathpoint[0].order->time + LIMIT && b < allpathpoint[1].order->time + LIMIT )//是否第一种路线不超时 
		    	    allriders[num].finaltask = allriders[num].temporarytask[0];//0号任务点的订单指针赋值给骑手当前任务点 
		    	else if(c < allpathpoint[1].order->time + LIMIT && d < allpathpoint[0].order->time + LIMIT )
		    	/*当第一种路线超时时是否第二种路线不超时*/
		    	    allriders[num].finaltask = allriders[num].temporarytask[1];//1号任务点的订单指针赋给骑手当前任务点 
		    	else allriders[num].finaltask = allriders[num].temporarytask[0];//0号任务点的订单指针赋值给骑手当前任务点
	     	}
			else if( c < allpathpoint[1].order->time + LIMIT && d < allpathpoint[0].order->time + LIMIT)
			/*当第二种路线快时是否第二种路线不超时*/ 
				allriders[num].finaltask = allriders[num].temporarytask[1];//1号任务点的订单指针赋给骑手当前任务点
			else allriders[num].finaltask = allriders[num].temporarytask[0];//0号任务点的订单指针赋给骑手当前任务点
		}
	}
	
	else if( number==3 )//当前有三个任务点 
	{
		struct pathpoint **allpath3[50];//定义长度为800的指向指针的指针数组
		i = 0;
		number = 0; 
		
		for( a = 0;a < 3;a++ )//第一个任务点序号为a
		{
			for( b = 0;b < 3;b++ )//第二个任务点序号为b
			{
				if( b!=a ) //b和a不相同
				{ 
				    for( c = 0;c < 3;c++ )//第三个任务点序号为c
					{
				        if( c!=a && c!=b )//c和b和a都不同
						{
							allpath3[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *) * 4);
							/*allpath[i]为第i种路线，里面是四个指向任务点的指针*/
							while( allpath3[i]==NULL )
							{
								allpath3[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *) * 4);
								/*allpath[i]为第i种路线，里面是四个指向任务点的指针*/
							}
							
							allpath3[i][0] = &allpathpoint[a];//第i种路线的第一个任务点是a号任务点
							allpath3[i][1] = &allpathpoint[b];//第i种路线的第二个任务点是b号任务点
							allpath3[i][2] = &allpathpoint[c];//第i种路线的第三个任务点是c号任务点
						    i++;//路线加一 
						}		
				    }  	
				}
			}
		}//穷举所有任务点排序，即可能路径
		
		for( i = 0,timemin = 100000;i < 6;i++ )//判断6种路线是否可行并择出最优
		{
			timemin = 100000;
			
			for( j = 0;j < 3 && allpath3[i]!=NULL;j++ )//判断第i种路线是否有订单中的食客在餐馆前面
			{
				if( allpath3[i][j]->order->current==1 && allpath3[i][j]->n==0 )//该任务点属于待取餐订单并且是餐馆
				{
					for( k = 0;k < 3;k++ )//遍历并找到和该任务点同属一个订单的食客
					{
						if(allpath3[i][k]->order->current==1 && allpath3[i][k]->n==1 && allpath3[i][j]->order==allpath3[i][k]->order)
						/*该任务点是否和上述任务点同属一个订单并且是食客*/
						{
							temp = k;//记录该任务点序号 
						}
					}
					
					if(allpath3[i][temp]->order->current==1 && allpath3[i][temp]->n==1 && allpath3[i][j]->order==allpath3[i][temp]->order)
					/*该任务点是否和上述任务点同属一个订单并且是食客*/
					{
						if( temp < j )//是否食客在餐馆前面 
						{
							timemin = 150000;
						}
					}
				}
			}
			
			if( timemin!=150000 )//是否i号路线未废除
			{
				timer = (abs(allriders[num].x - allpath3[i][0]->x) + abs(allriders[num].y - allpath3[i][0]->y)) / 2;
				/*骑手到i号路线第一个任务点所需花费时间*/
				allpath3[i][0]->time = time + timer;//计算第i号路线第一个任务点到达时间
				for( j = 0;j < 2;j++ )//计算其余任务点到达时间
				{
					timer += ((abs(allpath3[i][j]->x - allpath3[i][j+1]->x) + abs(allpath3[i][j]->y - allpath3[i][j+1]->y)) /2 );
					/*计算从第j个任务点到底j+1个任务点所需时间*/
					allpath3[i][j+1]->time = timer + time; //计算到第j+1个任务点的时间 
				}
				
				for( j = 0;j < 3 && allpath3[i]!=NULL;j++ )//遍历第i条路线所有任务点，判断其是否超时
				{
					if(allpath3[i][j]->order->time + LIMIT<=allpath3[i][j]->time )//第i条路线第j个任务点是否超时
					{
						timemin = 150000;
					}    
	            }
	            
	            if( timemin!=150000 )//是否i号路线废除
	            {
	            	if( timer < timemin )//是否时间最短
	            	{
	            		timemin = timer;//目前最短时间赋值
	            		number = i;//目前预备路线赋值 
					}
				}
			}
		}
		
		if(number==0) allriders[num].finaltask = allriders[num].temporarytask[0];//无路线正常则任务点为第一个点 
		else allriders[num].finaltask = allpath3[number][0]->order;
		/*最佳路线的第一个任务点的订单指针赋给骑手当前目标点*/
		
		for( i = 0;i < 6;i++ ) free(allpath3[i]);//释放所有路线 
	}
	
	else if( number==4 )//当前有四个任务点 
	{
		struct pathpoint **allpath4[50];//定义长度为50的指向指针的指针数组
		i =0 ;
		number = 0;
		
		for( a = 0;a <4 ;a++ )//第一个任务点序号为a
		{
			for( b =0 ;b < 4;b++ )//第二个任务点序号为b
			{
				if( b!=a ) //b和a不相同
				{ 
				    for( c = 0;c < 4;c++ )//第三个任务点序号为c
					{
				        if( c!=a && c!=b )//c和b和a都不同
						{
							for( d = 0;d < 4;d++ )//第四个任务点序号为d 
							{
								if( d!=a && d!=b && d!=c )//d和c和b和a都不同
								{
									allpath4[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *)*5);
									/*allpath[i]为第i种路线，里面是五个指向任务点的指针*/
									while( allpath4[i]==NULL )//allpath[i]为第i种路线，里面是五个指向任务点的指针)
									{
										allpath4[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *)*5);
										/*allpath[i]为第i种路线，里面是五个指向任务点的指针*/
									}
									allpath4[i][0] = &allpathpoint[a];//第i种路线的第一个任务点是a号任务点
									allpath4[i][1] = &allpathpoint[b];//第i种路线的第二个任务点是b号任务点
									allpath4[i][2] = &allpathpoint[c];//第i种路线的第三个任务点是c号任务点
									allpath4[i][3] = &allpathpoint[d];//第i种路线的第四个任务点是d号任务点
								    i++;//路线加一
								}
							}
						}		
				    }  	
				}
			}
		}//穷举所有任务点排序，即可能路径
		
		for( i =0 ,timemin = 100000;i < 24;i++ )//判断24种路线是否可行并择出最优
		{
			timemin = 100000;
			
			for( j = 0;j < 4 && allpath4[i]!=NULL;j++ )//判断第i种路线是否有订单中的食客在餐馆前面
			{
				if( allpath4[i][j]->order->current==1 && allpath4[i][j]->n==0 )//该任务点属于待取餐订单并且是餐馆
				{
					for( k = 0;k < 4;k++ )//遍历并找到和该任务点同属一个订单的食客
					{
						if(allpath4[i][k]->order->current==1 && allpath4[i][k]->n==1 && allpath4[i][j]->order==allpath4[i][k]->order)
						/*该任务点是否和上述任务点同属一个订单并且是食客*/
						{
							temp = k;//记录该任务点序号 
						}
					}
					
					if(allpath4[i][temp]->order->current==1 && allpath4[i][temp]->n==1 && allpath4[i][j]->order==allpath4[i][temp]->order)
					/*该任务点是否和上述任务点同属一个订单并且是食客*/
					{
						if( temp < j ) //是否食客在餐馆前面
						{
							timemin = 150000;
						}
					}
				}
			}
			
			if( timemin!=150000 )//是否i号路线未废除
			{
				timer = (abs(allriders[num].x - allpath4[i][0]->x) + abs(allriders[num].y - allpath4[i][0]->y)) / 2;
				/*骑手到i号路线第一个任务点所需花费时间*/
				allpath4[i][0]->time = time + timer;//计算第i号路线第一个任务点到达时
				for( j = 0;j < 3;j++ )//计算其余任务点到达时间
				{
					timer += ((abs(allpath4[i][j]->x - allpath4[i][j+1]->x) + abs(allpath4[i][j]->y - allpath4[i][j+1]->y)) / 2);
					/*计算从第j个任务点到底j+1个任务点所需时间*/
					allpath4[i][j+1]->time = timer + time; //计算到第j+1个任务点的时间 
				}
				
				for( j = 0;j < 4 && allpath4[i]!=NULL;j++ )//遍历第i条路线所有任务点，判断其是否超时
				{
					if(allpath4[i][j]->order->time + LIMIT<=allpath4[i][j]->time)//第i条路线第j个任务点是否超时
					{
						timemin = 150000;   
					} 
	            }
	            
	            if( timemin!=150000 )//是否i号路线废除
	            {
	            	if( timer < timemin )//是否时间最短
	            	{
	            		timemin = timer;//目前最短时间赋值
	            		number = i;//目前预备路线赋值
					}
				}
			}
		}
		if(number==0)  allriders[num].finaltask = allriders[num].temporarytask[0];//无路线满足则取第一个点为目标点 
		else allriders[num].finaltask = allpath4[number][0]->order;
		/*最佳路线的第一个任务点的订单指针赋给骑手当前目标点*/
		
		for( i = 0;i < 24;i++ ) free(allpath4[i]);//释放所有路线
	}
	
	else if(number==5)//当前有五个任务点
	{
		struct pathpoint **allpath5[200];//定义长度为150的指向指针的指针数组
		i = 0;
		number = 0;
		
		for( a = 0;a < 5;a++ )//第一个任务点序号为a
		{
			for( b =0 ;b < 5;b++ )//第二个任务点序号为b
			{
				if( b!=a ) //b和a不相同
				{ 
				    for( c = 0;c < 5;c++ )//第三个任务点序号为c
					{
				        if( c!=a && c!=b )//c和b和a都不同
						{
							for( d = 0;d < 5;d++ )//第四个任务点序号为d
							{
								if( d!=a && d!=b && d!=c )//d和c和b和a都不同
								{
									for( e = 0;e < 5;e++ )//第五个任务点序号为e
									{
										if( e!=a && e!=b && e!=c && e!=d )//e和d和c和b和a都不同
										{
											allpath5[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *)*6);
											/*allpath[i]为第i种路线，里面是六个指向任务点的指针*/
											while( allpath5[i]==NULL )
											{
												allpath5[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *)*6);
												/*allpath[i]为第i种路线，里面是六个指向任务点的指针*/
											}
											allpath5[i][0] = &allpathpoint[a];//第i种路线的第一个任务点是a号任务点
											allpath5[i][1] = &allpathpoint[b];//第i种路线的第二个任务点是b号任务点
											allpath5[i][2] = &allpathpoint[c];//第i种路线的第三个任务点是c号任务点
											allpath5[i][3] = &allpathpoint[d];//第i种路线的第四个任务点是d号任务点
											allpath5[i][4] = &allpathpoint[e];//第i种路线的第五个任务点是e号任务点
											i++;//路线加一
									    }
									}
								}
							}
						}		
				    }  	
				}
			}
		}//穷举所有任务点排序，即可能路径
		
		for( i = 0,timemin = 100000;i < 120;i++ )//判断120种路线是否可行并择出最优
		{
			timemin = 100000;
			
			for( j = 0;j < 5 && allpath5[i]!=NULL;j++ )//判断第i种路线是否有订单中的食客在餐馆前面
			{
				if(allpath5[i][j]->order->current==1 && allpath5[i][j]->n==0)//该任务点属于待取餐订单并且是餐馆
				{
					for( k = 0;k < 5;k++ )//遍历并找到和该任务点同属一个订单的食客
					{
						if(allpath5[i][k]->order->current==1 && allpath5[i][k]->n==1 && allpath5[i][j]->order==allpath5[i][k]->order)
						/*该任务点是否和上述任务点同属一个订单并且是食客*/
						{
							temp = k; //记录该任务点序号 
						}
					}
					
					if(allpath5[i][temp]->order->current==1 && allpath5[i][temp]->n==1 && allpath5[i][j]->order==allpath5[i][temp]->order)
					/*该任务点是否和上述任务点同属一个订单并且是食客*/
					{
						if( temp < j ) //是否食客在餐馆前面
						{
							timemin = 150000;
						}
					}
				}
			}
			if( timemin!=150000 )//是否i号路线废除
			{
				timer = (abs(allriders[num].x - allpath5[i][0]->x) + abs(allriders[num].y - allpath5[i][0]->y)) /2 ;
				/*骑手到i号路线第一个任务点所需花费时间*/
				allpath5[i][0]->time = time + timer;//计算第i号路线第一个任务点到达时间
				for( j = 0;j < 4;j++ )//计算其余任务点到达时间
				{
					timer += ((abs(allpath5[i][j]->x - allpath5[i][j+1]->x) + abs(allpath5[i][j]->y - allpath5[i][j+1]->y)) / 2);
					/*计算从第j个任务点到底j+1个任务点所需时间*/
					allpath5[i][j+1]->time = timer + time; //计算到第j+1个任务点的时间 
				}
				
				for( j = 0;j < 5 && allpath5[i]!=NULL;j++ )//遍历第i条路线所有任务点，判断其是否超时
				{
					if( allpath5[i][j]->order->time + LIMIT <= allpath5[i][j]->time )
					/*第i条路线第j个任务点是否超时*/
					{
						timemin = 150000;
					}
	            }
	            
	            if( timemin!=150000 )//是否i号路线废除
	            {
	            	if( timer < timemin )//是否时间最短
	            	{
	            		timemin = timer;//目前最短时间赋值
	            		number = i;//目前预备路线赋值
					}
				}
			}
		}
		if( number==0 ) allriders[num].finaltask = allriders[num].temporarytask[0];//无路线正常则取第一个点为目标点 
		else allriders[num].finaltask = allpath5[number][0]->order;
		/*最佳路线的第一个任务点的订单指针赋给骑手当前目标点*/
		
		for( i = 0;i < 120;i++ ) free(allpath5[i]);//释放所有路线
	}
} 

