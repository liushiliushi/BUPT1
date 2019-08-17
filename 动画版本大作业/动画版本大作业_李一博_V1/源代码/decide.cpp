#include<stdio.h>
#include<stdlib.h> 
#include"head.h" 
/*include区*/
 
extern int money,ridernumber,time,temp,allaccept,over,finish,buytemp;//非静态全局变量和起初始值的定义 
extern struct order * firstorder;//头订单指针 
extern struct rider allriders[50];//所有骑手信息 
/*结构，类，变量，指针定义区*/ 


extern void decide(void)
{
	struct order *orderptr = firstorder;//首订单指针赋值 
	int i,j,k,l;//循环变量 
	long int nx,ny,min,overriders[20][2];//前三个是计算派单适合度的辅助变量，最后一个是同区域骑手的序号和其派单适合度的二维数组 
	
	if( firstorder==NULL ) return;
	 
    while(( orderptr->time < time || orderptr->time==time) && orderptr->orderptr != NULL )//遍历所有开始订单 
	{
		if( orderptr->current==0 )//该订单未派单 
		{
			for( i = 0;i < ridernumber && orderptr->current==0;i++ )//遍历所有骑手 
			{
				if((orderptr->cx > allriders[i].x1 || orderptr->cx==allriders[i].x1) && (orderptr->sx > allriders[i].x1 || orderptr->sx==allriders[i].x1))
				{
				    if((orderptr->cx < allriders[i].x2 || orderptr->cx==allriders[i].x2) && (orderptr->sx < allriders[i].x2 || orderptr->sx==allriders[i].x2))
					/*该单餐馆和食客的横坐标满足该骑手区域*/ 
					{
						if((orderptr->cy > allriders[i].y1 || orderptr->cy==allriders[i].y1) && (orderptr->sy > allriders[i].y1 || orderptr->sy==allriders[i].y1))
				        {
				        	if((orderptr->cy < allriders[i].y2 || orderptr->cy==allriders[i].y2) && (orderptr->sy < allriders[i].y2 || orderptr->sy==allriders[i].y2))
							/*该单餐馆和食客的纵坐标满足该骑手区域*/ 
				        	{
					            if( allriders[i].same==0 )//该骑手不是跨区域骑手 
					           	{
					   		        allriders[i].temporarytask[allriders[i].currentnumber] = orderptr;//将该订单分配给该骑手 
					   		        allriders[i].accept++;//该骑手接单数加一 
					   		        allriders[i].currentnumber++;//当前订单数加一
					   		        allriders[i].change = 0;//表示骑手订单序列已经改变 
					   		        allaccept++;//总接单数加一 
					   		        orderptr->rider = i;//将骑手序号值赋给该单配送骑手 
				    		        orderptr->current = 1;//将该单状态改为待取餐 
				            	}
						        else//该骑手是跨区域骑手 
						        {
							        overriders[0][0] = i;//将该骑手序号赋给跨区域骑手序列的第一组								       
									for( j = 1,i++;i < ridernumber;i++ )//遍历剩下骑手，寻找跨同区域骑手 
							        {
								
									    if((allriders[i].x1==allriders[overriders[j-1][0]].x1) && (allriders[i].x2==allriders[overriders[j-1][0]].x2) && allriders[i].same==1) 
									    {
									       	if((allriders[i].y1==allriders[overriders[j-1][0]].y1) && (allriders[i].y2==allriders[overriders[j-1][0]].y2)) 
									       	{
									            overriders[j][0] = i;//将该骑手序号填入跨区域骑手二维数组 
									       	    j++;//跨区域骑手数加一	
											}
								        }
							        }
							        
							        for( k=0;k < j;k++ )//计算所有跨区域骑手的派单适合度 
							        {
							        	nx = allriders[overriders[k][0]].x * 2;//辅助量nx赋初值两倍该骑手的横坐标 
							         	ny = allriders[overriders[k][0]].y * 2;//辅助量ny赋初值两倍该骑手的纵坐标 
							       	    for( l = 0;l < allriders[overriders[k][0]].currentnumber;l++ )//继续计算该骑手派单适合度 
							     		{
											nx += allriders[overriders[k][0]].temporarytask[l]->cx;//nx累加该骑手所有餐馆横坐标 
											nx += allriders[overriders[k][0]].temporarytask[l]->sx;//nx累加该骑手所有食客横坐标 
											ny += allriders[overriders[k][0]].temporarytask[l]->cy;//ny累加该骑手所有餐馆纵坐标 
										    ny += allriders[overriders[k][0]].temporarytask[l]->sy;//ny累加该骑手所有食客纵坐标 
										}
										nx = nx - (allriders[overriders[k][0]].currentnumber+1) * orderptr->cx;
										nx = nx - (allriders[overriders[k][0]].currentnumber+1) * orderptr->sx;
										nx = nx * nx;//nx为所有骑手已分配订单和该订单横坐标距离差的平方和 
										ny = ny - (allriders[overriders[k][0]].currentnumber+1) * orderptr->cy;
										ny = ny - (allriders[overriders[k][0]].currentnumber+1) * orderptr->sy;
										ny = ny * ny;//ny为所有骑手已分配订单和该订单纵坐标距离差的平方和
										overriders[k][1]=(nx+ny) * (allriders[overriders[k][0]].currentnumber) * (allriders[overriders[k][0]].currentnumber) * (allriders[overriders[k][0]].currentnumber);
										/*将该骑手的订单适合度赋值给跨区域骑手数组*/ 
									}
									min = overriders[0][1];//订单适合度最小值赋初值 
									l = 0;//最合适订单序号赋初值 
									
									for( k = 1;k < j;k++ )//遍历所有跨区域选手订单适合度 
									{
	     								if( overriders[k][1] < min )//是否适合度更小 
										{
											min = overriders[k][1];//将其作为最小值 
											l = k;//保留该骑手序号 
										}
									}
									allriders[overriders[l][0]].temporarytask[allriders[overriders[l][0]].currentnumber] = orderptr;//将该订房赋值给最合适的骑手 
					    	        allriders[overriders[l][0]].accept++;//该骑手接单数加一
					    	        allriders[overriders[l][0]].currentnumber++;//该骑手接单数加一
					    	        allriders[overriders[l][0]].change = 0;// 表示骑手订单序列已经改变
					   		        allaccept++;//总接单数加一
					   		        orderptr->rider = overriders[l][0];//将该骑手序号赋给订单派送骑手 
					   		        orderptr->current = 1;//将该订单状态变为待取餐 
							    }	
							}
				    	}
					}
			    }
			}
		}
		else if( buytemp!=0 )//当前重新购买了骑手并且重划分了区域 
		{ 
		    if( orderptr->current==1 )//该单虽然已经分配但未被取餐 
			{
			    i = orderptr->rider;//i为该单当前配送骑手序号 
			    for( j = 0,k = 0;j < (allriders[i].currentnumber);j++ )//找到该骑手派送队列里的该单 
				{
					if( allriders[i].temporarytask[j]==orderptr ) k = j;//找到该骑手派送队列里的该单并记录位置 
				}
				
				for( j = k;j < (allriders[i].currentnumber) - 1;j++ )//删除该单 
				{
					allriders[i].temporarytask[j] = allriders[i].temporarytask[j+1];//覆盖法删除 
				}
				allriders[i].temporarytask[allriders[i].currentnumber-1] = NULL;//最后一个单原位置赋为空 
				allriders[i].accept -= 1;//该骑手接单数减一 
				allriders[i].currentnumber -= 1;//当前骑手订单数减一 
				allriders[i].change = 0;//表示该骑手订单已经改变 
				
				for( i = 0;i < ridernumber;i++ )//将该单重新派单，遍历所有骑手 
			    {
				    if((orderptr->cx > allriders[i].x1 || orderptr->cx==allriders[i].x1) && (orderptr->sx > allriders[i].x1 || orderptr->sx==allriders[i].x1))
				    {
				        if((orderptr->cx < allriders[i].x2 || orderptr->cx==allriders[i].x2) && (orderptr->sx < allriders[i].x2 || orderptr->sx==allriders[i].x2))
					    {/*该单餐馆和食客的横坐标满足该骑手区域*/
						    if((orderptr->cy > allriders[i].y1 || orderptr->cy==allriders[i].y1) && (orderptr->sy > allriders[i].y1 || orderptr->sy==allriders[i].y1))
				            { 
				        	    if((orderptr->cy < allriders[i].y2 || orderptr->cy==allriders[i].y2) && (orderptr->sy < allriders[i].y2 || orderptr->sy==allriders[i].y2))
				        	    {/*该单餐馆和食客的纵坐标满足该骑手区域*/ 
					                if( allriders[i].same==0 )//该骑手不是跨区域骑手
					           	    {
					   		            allriders[i].temporarytask[allriders[i].currentnumber] = orderptr;//将该订单分配给该骑手 
					   		            allriders[i].accept++;//该骑手接单数加一
					   		            allriders[i].currentnumber++;//该骑手订单数加一 
					   		            allriders[i].change = 0;//表示该骑手订单情况已经改变 
					   		            orderptr->rider = i;//将骑手序号值赋给该单配送骑手 
				    		            orderptr->current = 1;//将该单状态改为待取餐 
				            	    }
						            else//该骑手是跨区域骑手 
						            {
							            overriders[0][0] = i;//将该骑手序号赋给跨区域骑手序列的第一组								       
								     	for( j = 1,i++;i < ridernumber;i++ )//遍历剩下骑手，寻找跨同区域骑手 
							            {
								
									        if((allriders[i].x1==allriders[overriders[j-1][0]].x1) && (allriders[i].x2==allriders[overriders[j-1][0]].x2) && allriders[i].same==1)
									        {
									       	    if((allriders[i].y1==allriders[overriders[j-1][0]].y1) && (allriders[i].y2==allriders[overriders[j-1][0]].y2))
									       	    {
									                overriders[j][0] = i;//将该骑手序号填入跨区域骑手二维数组
									       	        j++;//跨区域骑手数加一	
										    	}
								            }
							            }
							            for( k = 0;k < j;k++ )//计算所有跨区域骑手的派单适合度 
							            {
							        	    nx = allriders[overriders[k][0]].x * 2;//辅助量nx赋初值两倍该骑手的横坐标 
							         	    ny = allriders[overriders[k][0]].y * 2;//辅助量ny赋初值两倍该骑手的纵坐标
							       	        for( l = 0;l < allriders[overriders[k][0]].currentnumber;l++ )//继续计算该骑手派单适合度
							     	     	{
											    nx += allriders[overriders[k][0]].temporarytask[l]->cx;//nx累加该骑手所有餐馆横坐标
										    	nx += allriders[overriders[k][0]].temporarytask[l]->sx;//nx累加该骑手所有食客横坐标
										    	ny += allriders[overriders[k][0]].temporarytask[l]->cy;//ny累加该骑手所有餐馆纵坐标
										        ny += allriders[overriders[k][0]].temporarytask[l]->sy;//ny累加该骑手所有食客纵坐标
										    }
									     	nx = nx-(allriders[overriders[k][0]].currentnumber+1) * orderptr->cx;
								    		nx = nx-(allriders[overriders[k][0]].currentnumber+1) * orderptr->sx;
						     				nx = nx * nx;//nx为所有骑手已分配订单和该订单横坐标距离差的平方和										
							    			ny = ny - (allriders[overriders[k][0]].currentnumber+1) * orderptr->cy;
								    		ny = ny - (allriders[overriders[k][0]].currentnumber+1) * orderptr->sy;
									    	ny = ny * ny;//ny为所有骑手已分配订单和该订单纵坐标距离差的平方和
										    overriders[k][1] = (nx+ny) * (allriders[overriders[k][0]].currentnumber) * (allriders[overriders[k][0]].currentnumber) * (allriders[overriders[k][0]].currentnumber);
										    /*将该骑手的订单适合度赋值给跨区域骑手数组*/ 
									    }
								      	min = overriders[0][1];
					    				l = 0;//最合适订单序号赋初值
					    				
						    			for( k = 1;k < j;k++ )//遍历所有跨区域选手订单适合度
							    		{
	     						    		if( overriders[k][1] < min )//是否适合度更小 
							    			{
								    			min = overriders[k][1];//将其作为最小值 
									    		l = k;//保留该骑手序号
										    }
								    	}
								    	allriders[overriders[l][0]].temporarytask[allriders[overriders[l][0]].currentnumber] = orderptr;//将该订房赋值给最合适的骑手 
					    	            allriders[overriders[l][0]].accept++;//该骑手接单数加一
										allriders[overriders[l][0]].currentnumber++;//该骑手当前订单数加一 
					    	            allriders[overriders[l][0]].change = 0;//表明该骑手订单状况已经改变 
					    	            orderptr->rider = overriders[l][0];//总接单数加一 
					   		            orderptr->current = 1;//将订单当前状态改为待取餐 
							        }	
							    }
				         	}
				    	}
			        }
			    }
			}	
		}
		orderptr = orderptr->orderptr;//准备分析下一个订单 
	}
	if((orderptr->time < time || orderptr->time==time) && orderptr->orderptr==NULL)
	{
	    if( orderptr->current==0 )//该订单满足刚发出且未派单 
		{
			for( i = 0;i < ridernumber && orderptr->current==0;i++ )//遍历所有骑手 
			{
				if((orderptr->cx > allriders[i].x1 || orderptr->cx==allriders[i].x1) && (orderptr->sx > allriders[i].x1 || orderptr->sx==allriders[i].x1))
				{
				    if((orderptr->cx < allriders[i].x2 || orderptr->cx==allriders[i].x2) && (orderptr->sx < allriders[i].x2 || orderptr->sx==allriders[i].x2))
					/*该单餐馆和食客的横坐标满足该骑手区域*/ 
					{
						if((orderptr->cy > allriders[i].y1 || orderptr->cy==allriders[i].y1) && (orderptr->sy > allriders[i].y1 || orderptr->sy==allriders[i].y1))
				        {
				        	if((orderptr->cy < allriders[i].y2 || orderptr->cy==allriders[i].y2) && (orderptr->sy < allriders[i].y2 || orderptr->sy==allriders[i].y2))
							/*该单餐馆和食客的纵坐标满足该骑手区域*/ 
				        	{
					            if( allriders[i].same==0 )//该骑手不是跨区域骑手 
					           	{
					   		        allriders[i].temporarytask[allriders[i].currentnumber] = orderptr;//将该订单分配给该骑手 
					   		        allriders[i].accept++;//该骑手接单数加一 
					   		        allriders[i].currentnumber++;//当前订单数加一
					   		        allriders[i].change = 0;//表示骑手订单序列已经改变 
					   		        allaccept++;//总接单数加一 
					   		        orderptr->rider = i;//将骑手序号值赋给该单配送骑手 
				    		        orderptr->current = 1;//将该单状态改为待取餐 
				            	}
						        else//该骑手是跨区域骑手 
						        {
							        overriders[0][0] = i;//将该骑手序号赋给跨区域骑手序列的第一组								       
									for( j = 1,i++;i < ridernumber;i++ )//遍历剩下骑手，寻找跨同区域骑手 
							        {
								
									    if((allriders[i].x1==allriders[overriders[j-1][0]].x1) && (allriders[i].x2==allriders[overriders[j-1][0]].x2) && allriders[i].same==1) 
									    {
									       	if((allriders[i].y1==allriders[overriders[j-1][0]].y1) && (allriders[i].y2==allriders[overriders[j-1][0]].y2))//该骑手是同跨区域骑手 
									       	{
									            overriders[j][0] = i;//将该骑手序号填入跨区域骑手二维数组 
									       	    j++;//跨区域骑手数加一	
											}
								        }
							        }
							        
							        for( k = 0;k < j;k++ )//计算所有跨区域骑手的派单适合度 
							        {
							        	nx = allriders[overriders[k][0]].x * 2;//辅助量nx赋初值两倍该骑手的横坐标 
							         	ny = allriders[overriders[k][0]].y * 2;//辅助量ny赋初值两倍该骑手的纵坐标 
							       	    for( l = 0;l < allriders[overriders[k][0]].currentnumber;l++ )//继续计算该骑手派单适合度 
							     		{
											nx += allriders[overriders[k][0]].temporarytask[l]->cx;//nx累加该骑手所有餐馆横坐标 
											nx += allriders[overriders[k][0]].temporarytask[l]->sx;//nx累加该骑手所有食客横坐标 
											ny += allriders[overriders[k][0]].temporarytask[l]->cy;//ny累加该骑手所有餐馆纵坐标 
										    ny += allriders[overriders[k][0]].temporarytask[l]->sy;//ny累加该骑手所有食客纵坐标 
										}
										nx = nx - (allriders[overriders[k][0]].currentnumber+1) * orderptr->cx;
										nx = nx - (allriders[overriders[k][0]].currentnumber+1) * orderptr->sx;
										nx = nx * nx;//nx为所有骑手已分配订单和该订单横坐标距离差的平方和 
										ny = ny - (allriders[overriders[k][0]].currentnumber+1) * orderptr->cy;
										ny = ny - (allriders[overriders[k][0]].currentnumber+1) * orderptr->sy;
										ny = ny * ny;//ny为所有骑手已分配订单和该订单纵坐标距离差的平方和
										overriders[k][1] = (nx+ny) * (allriders[overriders[k][0]].currentnumber) * (allriders[overriders[k][0]].currentnumber) * (allriders[overriders[k][0]].currentnumber);
										/*将该骑手的订单适合度赋值给跨区域骑手数组*/ 
									}
									min = overriders[0][1];//订单适合度最小值赋初值 
									l = 0;//最合适订单序号赋初值 
									
									for( k = 1;k < j;k++ )//遍历所有跨区域选手订单适合度 
									{
	     								if( overriders[k][1] < min )//是否适合度更小 
										{
											min = overriders[k][1];//将其作为最小值 
											l = k;//保留该骑手序号 
										}
									}
									allriders[overriders[l][0]].temporarytask[allriders[overriders[l][0]].currentnumber] = orderptr;//将该订房赋值给最合适的骑手 
					    	        allriders[overriders[l][0]].accept++;//该骑手接单数加一
					    	        allriders[overriders[l][0]].currentnumber++;//该骑手接单数加一
					    	        allriders[overriders[l][0]].change = 0;// 表示骑手订单序列已经改变
					   		        allaccept++;//总接单数加一
					   		        orderptr->rider = overriders[l][0];//将该骑手序号赋给订单派送骑手 
					   		        orderptr->current = 1;//将该订单状态变为待取餐 
							    }	
							}
				    	}
					}
			    }
			}
		}
		else if( buytemp != 0)//当前重新购买了骑手并且重划分了区域 
		{ 
		    if( orderptr->current==1 )//该单虽然已经分配但未被取餐 
			{
			    i = orderptr->rider;//i为该单当前配送骑手序号 
			    for( j = 0,k = 0;j < (allriders[i].currentnumber);j++ )//找到该骑手派送队列里的该单 
				{
					if( allriders[i].temporarytask[j]==orderptr ) k = j;//找到该骑手派送队列里的该单并记录位置 
				}
				
				for( j = k;j < (allriders[i].currentnumber) - 1;j++ )//删除该单 
				{
					allriders[i].temporarytask[j] = allriders[i].temporarytask[j+1];//覆盖法删除 
				}
				
				allriders[i].temporarytask[allriders[i].currentnumber-1] = NULL;//最后一个单原位置赋为空 
				allriders[i].accept -= 1;//该骑手接单数减一 
				allriders[i].currentnumber -= 1;//当前骑手订单数减一 
				allriders[i].change = 0;//表示该骑手订单已经改变 
				
				for( i = 0;i < ridernumber;i++ )//将该单重新派单，遍历所有骑手 
			    {
				    if((orderptr->cx > allriders[i].x1 || orderptr->cx==allriders[i].x1) && (orderptr->sx > allriders[i].x1 || orderptr->sx==allriders[i].x1))
				    {
				        if((orderptr->cx < allriders[i].x2 || orderptr->cx==allriders[i].x2) && (orderptr->sx < allriders[i].x2 || orderptr->sx==allriders[i].x2))
					    {/*该单餐馆和食客的横坐标满足该骑手区域*/
						    if((orderptr->cy > allriders[i].y1 || orderptr->cy==allriders[i].y1) && (orderptr->sy > allriders[i].y1 || orderptr->sy==allriders[i].y1))
				            { 
				        	    if((orderptr->cy < allriders[i].y2 || orderptr->cy==allriders[i].y2) && (orderptr->sy < allriders[i].y2 || orderptr->sy==allriders[i].y2))
				        	    {/*该单餐馆和食客的纵坐标满足该骑手区域*/ 
					                if( allriders[i].same==0 )//该骑手不是跨区域骑手
					           	    {
					   		            allriders[i].temporarytask[allriders[i].currentnumber] = orderptr;//将该订单分配给该骑手 
					   		            allriders[i].accept++;//该骑手接单数加一
					   		            allriders[i].currentnumber++;//该骑手订单数加一 
					   		            allriders[i].change = 0;//表示该骑手订单情况已经改变 
					   		            orderptr->rider = i;//将骑手序号值赋给该单配送骑手 
				    		            orderptr->current = 1;//将该单状态改为待取餐 
				            	    }
						            else//该骑手是跨区域骑手 
						            {
							            overriders[0][0] = i;//将该骑手序号赋给跨区域骑手序列的第一组								       
								     	for( j = 1,i++;i < ridernumber;i++ )//遍历剩下骑手，寻找跨同区域骑手 
							            {
								
									        if((allriders[i].x1==allriders[overriders[j-1][0]].x1) && (allriders[i].x2==allriders[overriders[j-1][0]].x2) && allriders[i].same==1)
									        {
									       	    if((allriders[i].y1==allriders[overriders[j-1][0]].y1) && (allriders[i].y2==allriders[overriders[j-1][0]].y2))
									       	    {
									                overriders[j][0] = i;//将该骑手序号填入跨区域骑手二维数组
									       	        j++;//跨区域骑手数加一	
										    	}
								            }
							            }
							            for( k = 0;k < j;k++ )//计算所有跨区域骑手的派单适合度 
							            {
							        	    nx = allriders[overriders[k][0]].x * 2;//辅助量nx赋初值两倍该骑手的横坐标 
							         	    ny = allriders[overriders[k][0]].y * 2;//辅助量ny赋初值两倍该骑手的纵坐标
							       	        for( l = 0;l < allriders[overriders[k][0]].currentnumber;l++ )//继续计算该骑手派单适合度
							     	     	{
											    nx += allriders[overriders[k][0]].temporarytask[l]->cx;//nx累加该骑手所有餐馆横坐标
										    	nx += allriders[overriders[k][0]].temporarytask[l]->sx;//nx累加该骑手所有食客横坐标
										    	ny += allriders[overriders[k][0]].temporarytask[l]->cy;//ny累加该骑手所有餐馆纵坐标
										        ny += allriders[overriders[k][0]].temporarytask[l]->sy;//ny累加该骑手所有食客纵坐标
										    }
									     	nx = nx - (allriders[overriders[k][0]].currentnumber+1) * orderptr->cx;
								    		nx = nx - (allriders[overriders[k][0]].currentnumber+1) * orderptr->sx;
						     				nx = nx * nx;//nx为所有骑手已分配订单和该订单横坐标距离差的平方和										
							    			ny = ny - (allriders[overriders[k][0]].currentnumber+1) * orderptr->cy;
								    		ny = ny - (allriders[overriders[k][0]].currentnumber+1) *orderptr->sy;
									    	ny = ny * ny;//ny为所有骑手已分配订单和该订单纵坐标距离差的平方和
										    overriders[k][1] = (nx+ny) * (allriders[overriders[k][0]].currentnumber) * (allriders[overriders[k][0]].currentnumber) * (allriders[overriders[k][0]].currentnumber);
										    /*将该骑手的订单适合度赋值给跨区域骑手数组*/ 
									    }
								      	min = overriders[0][1];
					    				l = 0;//最合适订单序号赋初值
						    			for( k = 1;k < j;k++ )//遍历所有跨区域选手订单适合度
							    		{
	     						    		if( overriders[k][1] < min )//是否适合度更小 
							    			{
								    			min = overriders[k][1];//将其作为最小值 
									    		l = k;//保留该骑手序号
										    }
								    	}
								    	allriders[overriders[l][0]].temporarytask[allriders[overriders[l][0]].currentnumber] = orderptr;//将该订房赋值给最合适的骑手 
					    	            allriders[overriders[l][0]].accept++;//该骑手接单数加一
										allriders[overriders[l][0]].currentnumber++;//该骑手当前订单数加一 
					    	            allriders[overriders[l][0]].change = 0;//表明该骑手订单状况已经改变 
					    	        
					   		            orderptr->rider = overriders[l][0];//总接单数加一 
					   		            orderptr->current = 1;//将订单当前状态改为待取餐 
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

