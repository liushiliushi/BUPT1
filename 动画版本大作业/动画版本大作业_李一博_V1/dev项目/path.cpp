#include<stdio.h>
#include<math.h> 
#include<stdlib.h>
#include "head.h"//��������ͷ�ļ� 
#include "main.h"
/*include��*/
 
#define LIMIT 30//�������͵�ʱ�� 

struct pathpoint{ 
	int x,y,time,n;//x,y�Ǹ������������꣬time�ǵ���ʱ�䣬n:0�͹�/1ʳ�� 
	struct order *order;//������������Ķ���ָ�� 
};//�����ṹ�嶨�� 
extern int ridernumber;
/*�ṹ�壬������ָ�붨����*/ 

void bestway(int);//�������� 


extern void bestwaywhile(void)
{
	int n = ridernumber,i; 
	
	for( i = 0;i < n;i++ )//������������ 
	{
		if( allriders[i].change==0 )//i�������Ƿ���Ҫ���¹滮·�� 
		{
			bestway(i);//Ϊi���������¹滮·�� 
			allriders[i].change = 1;//���жϸ�������λ 
		}
	}
}

void bestway(int num)//�Ż�·�ߺ�����numΪ�����Ż�·�ߵ�������� 
{
	int i,j,k,a,b,c,d,e,f,number = 0,timemin,timer,temp; 
	struct pathpoint allpathpoint[100];//������������� 
	
	if(allriders[num].temporarytask[0]==NULL) return;
	
	for(i = 0,number = 0;i < (allriders[num].currentnumber);i++ )//�����������ж�����Ϣ�����������飬numberΪ��������� 
	{
		if( allriders[num].temporarytask[i]->current==1 )//��ǰ�ж϶�����ȡ�� 
		{
			allpathpoint[number].x = allriders[num].temporarytask[i]->cx;//������������� 
			allpathpoint[number].y = allriders[num].temporarytask[i]->cy;//�������������� 
			allpathpoint[number].n = 0;//�������Ϊ�͹� 
			allpathpoint[number].order = allriders[num].temporarytask[i];//�����������������ָ�� 
			number += 1;//�����������һ 
			allpathpoint[number].x = allriders[num].temporarytask[i]->sx;//������������� 
			allpathpoint[number].y = allriders[num].temporarytask[i]->sy;//�������������� 
			allpathpoint[number].n = 1;//���������ʳ�� 
			allpathpoint[number].order = allriders[num].temporarytask[i];//�����������������ָ�� 
			number += 1;//�����������һ 
		}
		
		if( allriders[num].temporarytask[i]->current==2 )//��ǰ���ж϶������Ͳ� 
		{
			allpathpoint[number].x = allriders[num].temporarytask[i]->sx;//�������������� 
			allpathpoint[number].y = allriders[num].temporarytask[i]->sy;//��������������� 
			allpathpoint[number].n = 1;//�������ʳ�� 
			allpathpoint[number].order = allriders[num].temporarytask[i];//�����������������ָ�� 
			number += 1;//����������һ 
		}
	}
	
	if( number >= 6 )//��ǰ������������6�� 
	{
		struct pathpoint **allpath6[800];//���峤��Ϊ800��ָ��ָ���ָ������ 
		i = 0;
		number = 0; 
		
		for( a = 0;a < 6;a++ )//��һ����������Ϊa 
		{
			for( b = 0;b < 6;b++ )//�ڶ�����������Ϊb 
			{
				if( b!=a ) //b��a����ͬ 
				{ 
				    for( c = 0;c < 6;c++ )//��������������Ϊc 
					{
				        if( c!=a && c!=b )//c��b��a����ͬ 
						{
							for( d = 0;d < 6;d++ )//���ĸ���������Ϊd 
							{
								if( d!=a && d!=b && d!=c )//d��a��b��c����ͬ 
								{
									for( e = 0;e < 6;e++ )//���������������e 
									{
										if( e!=a && e!=b && e!=c && e!=d )//a,b,c,d,e������ͬ 
										{
											for( f = 0;f < 6;f++ )//����������������f 
											{
												if( f!=a && f!=b && f!=c && f!=d && f!=e )//a,b,c,d,e,f������ͬ 
												{
													allpath6[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *)*7);
													/*allpath[i]Ϊ��i��·�ߣ�����������ָ��������ָ��*/ 
													while( allpath6[i]==NULL )
													{
														allpath6[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *)*7);
														/*allpath[i]Ϊ��i��·�ߣ�����������ָ��������ָ��*/  
													}
													allpath6[i][0] = &allpathpoint[a];//��i��·�ߵĵ�һ���������a������� 
													allpath6[i][1] = &allpathpoint[b];//��i��·�ߵĵڶ����������b������� 
													allpath6[i][2] = &allpathpoint[c];//��i��·�ߵĵ������������c������� 
													allpath6[i][3] = &allpathpoint[d];//��i��·�ߵĵ��ĸ��������d������� 
													allpath6[i][4] = &allpathpoint[e];//��i��·�ߵĵ�����������e������� 
													allpath6[i][5] = &allpathpoint[f];//��i��·�ߵĵ������������f������� 
													i++;//·�߼�һ 
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
		}//���������������򣬼�����·�� 
		
		for( i = 0,timemin = 100000;i < 720;i++ )//�ж�720��·���Ƿ���в�������� 
		{
			timemin = 100000;
			
			for( j = 0;j < 6 && allpath6[i]!=NULL;j++ )//�жϵ�i��·���Ƿ���һ��������ʳ���ڲ͹�ǰ�� 
			{
				if( allpath6[i][j]->order->current==1 && allpath6[i][j]->n==0 )//����������ڴ�ȡ�Ͷ��������ǲ͹� 
				{
					for( k = 0;k < 6;k++ )//�������ҵ��͸������ͬ��һ��������ʳ�� 
					{
						if(allpath6[i][k]->order->current==1 && allpath6[i][k]->n==1 && allpath6[i][j]->order==allpath6[i][k]->order)
						{
							temp = k;//��¼���������� 
						}
						/*��������Ƿ�����������ͬ��һ������������ʳ��*/  
					}
					
					if(allpath6[i][temp]->order->current==1 && allpath6[i][temp]->n==1 && allpath6[i][j]->order==allpath6[i][temp]->order)
					{
						if( temp < j ) //�Ƿ�ʳ���ڲ͹�ǰ�� 
						{
							timemin = 150000;
						}
					}
					/*��������Ƿ�����������ͬ��һ������������ʳ��*/
				}
			}
			
			if( timemin!=150000 )//�Ƿ�i��·��δ���� 
			{
				timer = (abs(allriders[num].x-allpath6[i][0]->x) + abs(allriders[num].y-allpath6[i][0]->y)) / 2;
				/*���ֵ�i��·�ߵ�һ����������軨��ʱ��*/ 
				allpath6[i][0]->time = time + timer;//�����i��·�ߵ�һ������㵽��ʱ�� 
				for( j = 0;j < 5;j++ )//������������㵽��ʱ�� 
				{
					timer += ((abs(allpath6[i][j]->x-allpath6[i][j+1]->x) + abs(allpath6[i][j]->y-allpath6[i][j+1]->y)) / 2);
					/*����ӵ�j������㵽��j+1�����������ʱ��*/ 
					allpath6[i][j+1]->time = timer + time;//���㵽��j+1��������ʱ�� 
				}
				
				for( j = 0;j < 6 && allpath6[i]!=NULL;j++ )//������i��·����������㣬�ж����Ƿ�ʱ 
				{
					if( allpath6[i][j]->order->time + LIMIT <= allpath6[i][j]->time )//��i��·�ߵ�j��������Ƿ�ʱ 
					{
						timemin = 150000;//������㳬ʱ����·�߷ϳ�
				    } 
	            }
	            
	            if( timemin!=150000 )//�Ƿ�i��·�߷ϳ� 
	            {
	            	if( timer < timemin )//�Ƿ�ʱ����� 
	            	{
	            		timemin = timer;//Ŀǰ���ʱ�丳ֵ 
	            		number = i;//ĿǰԤ��·�߸�ֵ 
					}
				}
			}
		}
		
		if( number==0 ) 
		{
			allriders[num].finaltask = allriders[num].temporarytask[0];//û��·������ʱѡ��һ����ΪĿ��� 
		}
		else allriders[num].finaltask = allpath6[number][0]->order;//���·�ߵĵ�һ�������Ķ���ָ�븳�����ֵ�ǰĿ���
		 
		for( i = 0;i < 720;i++ ) free(allpath6[i]);//�ͷ�����·�� 
	}
	
	else if( number==0 ) //���ֵ�ǰû������ 
	{
		allriders[num].finaltask = NULL;//��ǰ����㸳Ϊ�� 
		return;//�������� 
	}
	
	else if( number==1 )//��ǰֻ��һ������� 
	{
		allriders[num].finaltask = allriders[num].temporarytask[0];//Ψһ�����Ķ���ָ�븳�����ֵ�ǰĿ��� 
	}
	
	else if( number==2 )//��ǰ����������� 
	{
	    if( allpathpoint[0].order==allpathpoint[1].order )//�Ƿ��������������ͬһ���� 
	        allriders[num].finaltask = allpathpoint[0].order;//�ö���ָ�븳�����ֵ�ǰĿ��� 
	    else//�����������������ָ�� 
	    {
	        a = ((abs(allriders[num].x - allpathpoint[0].x) + abs(allriders[num].y-allpathpoint[0].y)) / 2 + time);
	        /*��ȥ0����ȥ1��ʱ����0�ŵ�ʱ��*/
	        b = ((abs(allpathpoint[1].x - allpathpoint[0].x) + abs(allpathpoint[1].y - allpathpoint[0].y)) / 2 + a);
			/*��ȥ0����ȥ1��ʱ����1�ŵ�ʱ��*/ 
	        c = ((abs(allriders[num].x - allpathpoint[1].x) + abs(allriders[num].y - allpathpoint[1].y)) / 2 + time);
	        /*��ȥ1����ȥ0��ʱ����1�ŵ�ʱ��*/
		    d = ((abs(allpathpoint[0].x - allpathpoint[1].x) + abs(allpathpoint[0].y - allpathpoint[1].y)) / 2 + c);
			/*��ȥ1����ȥ0��ʱ����1�ŵ�ʱ��*/  
		    
		    if( b < d || b==d )//�Ƿ��һ��·�߱ȵڶ���·�߿� 
		    {
		    	if( a < allpathpoint[0].order->time + LIMIT && b < allpathpoint[1].order->time + LIMIT )//�Ƿ��һ��·�߲���ʱ 
		    	    allriders[num].finaltask = allriders[num].temporarytask[0];//0�������Ķ���ָ�븳ֵ�����ֵ�ǰ����� 
		    	else if(c < allpathpoint[1].order->time + LIMIT && d < allpathpoint[0].order->time + LIMIT )
		    	/*����һ��·�߳�ʱʱ�Ƿ�ڶ���·�߲���ʱ*/
		    	    allriders[num].finaltask = allriders[num].temporarytask[1];//1�������Ķ���ָ�븳�����ֵ�ǰ����� 
		    	else allriders[num].finaltask = allriders[num].temporarytask[0];//0�������Ķ���ָ�븳ֵ�����ֵ�ǰ�����
	     	}
			else if( c < allpathpoint[1].order->time + LIMIT && d < allpathpoint[0].order->time + LIMIT)
			/*���ڶ���·�߿�ʱ�Ƿ�ڶ���·�߲���ʱ*/ 
				allriders[num].finaltask = allriders[num].temporarytask[1];//1�������Ķ���ָ�븳�����ֵ�ǰ�����
			else allriders[num].finaltask = allriders[num].temporarytask[0];//0�������Ķ���ָ�븳�����ֵ�ǰ�����
		}
	}
	
	else if( number==3 )//��ǰ����������� 
	{
		struct pathpoint **allpath3[50];//���峤��Ϊ800��ָ��ָ���ָ������
		i = 0;
		number = 0; 
		
		for( a = 0;a < 3;a++ )//��һ����������Ϊa
		{
			for( b = 0;b < 3;b++ )//�ڶ�����������Ϊb
			{
				if( b!=a ) //b��a����ͬ
				{ 
				    for( c = 0;c < 3;c++ )//��������������Ϊc
					{
				        if( c!=a && c!=b )//c��b��a����ͬ
						{
							allpath3[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *) * 4);
							/*allpath[i]Ϊ��i��·�ߣ��������ĸ�ָ��������ָ��*/
							while( allpath3[i]==NULL )
							{
								allpath3[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *) * 4);
								/*allpath[i]Ϊ��i��·�ߣ��������ĸ�ָ��������ָ��*/
							}
							
							allpath3[i][0] = &allpathpoint[a];//��i��·�ߵĵ�һ���������a�������
							allpath3[i][1] = &allpathpoint[b];//��i��·�ߵĵڶ����������b�������
							allpath3[i][2] = &allpathpoint[c];//��i��·�ߵĵ������������c�������
						    i++;//·�߼�һ 
						}		
				    }  	
				}
			}
		}//���������������򣬼�����·��
		
		for( i = 0,timemin = 100000;i < 6;i++ )//�ж�6��·���Ƿ���в��������
		{
			timemin = 100000;
			
			for( j = 0;j < 3 && allpath3[i]!=NULL;j++ )//�жϵ�i��·���Ƿ��ж����е�ʳ���ڲ͹�ǰ��
			{
				if( allpath3[i][j]->order->current==1 && allpath3[i][j]->n==0 )//����������ڴ�ȡ�Ͷ��������ǲ͹�
				{
					for( k = 0;k < 3;k++ )//�������ҵ��͸������ͬ��һ��������ʳ��
					{
						if(allpath3[i][k]->order->current==1 && allpath3[i][k]->n==1 && allpath3[i][j]->order==allpath3[i][k]->order)
						/*��������Ƿ�����������ͬ��һ������������ʳ��*/
						{
							temp = k;//��¼���������� 
						}
					}
					
					if(allpath3[i][temp]->order->current==1 && allpath3[i][temp]->n==1 && allpath3[i][j]->order==allpath3[i][temp]->order)
					/*��������Ƿ�����������ͬ��һ������������ʳ��*/
					{
						if( temp < j )//�Ƿ�ʳ���ڲ͹�ǰ�� 
						{
							timemin = 150000;
						}
					}
				}
			}
			
			if( timemin!=150000 )//�Ƿ�i��·��δ�ϳ�
			{
				timer = (abs(allriders[num].x - allpath3[i][0]->x) + abs(allriders[num].y - allpath3[i][0]->y)) / 2;
				/*���ֵ�i��·�ߵ�һ����������軨��ʱ��*/
				allpath3[i][0]->time = time + timer;//�����i��·�ߵ�һ������㵽��ʱ��
				for( j = 0;j < 2;j++ )//������������㵽��ʱ��
				{
					timer += ((abs(allpath3[i][j]->x - allpath3[i][j+1]->x) + abs(allpath3[i][j]->y - allpath3[i][j+1]->y)) /2 );
					/*����ӵ�j������㵽��j+1�����������ʱ��*/
					allpath3[i][j+1]->time = timer + time; //���㵽��j+1��������ʱ�� 
				}
				
				for( j = 0;j < 3 && allpath3[i]!=NULL;j++ )//������i��·����������㣬�ж����Ƿ�ʱ
				{
					if(allpath3[i][j]->order->time + LIMIT<=allpath3[i][j]->time )//��i��·�ߵ�j��������Ƿ�ʱ
					{
						timemin = 150000;
					}    
	            }
	            
	            if( timemin!=150000 )//�Ƿ�i��·�߷ϳ�
	            {
	            	if( timer < timemin )//�Ƿ�ʱ�����
	            	{
	            		timemin = timer;//Ŀǰ���ʱ�丳ֵ
	            		number = i;//ĿǰԤ��·�߸�ֵ 
					}
				}
			}
		}
		
		if(number==0) allriders[num].finaltask = allriders[num].temporarytask[0];//��·�������������Ϊ��һ���� 
		else allriders[num].finaltask = allpath3[number][0]->order;
		/*���·�ߵĵ�һ�������Ķ���ָ�븳�����ֵ�ǰĿ���*/
		
		for( i = 0;i < 6;i++ ) free(allpath3[i]);//�ͷ�����·�� 
	}
	
	else if( number==4 )//��ǰ���ĸ������ 
	{
		struct pathpoint **allpath4[50];//���峤��Ϊ50��ָ��ָ���ָ������
		i =0 ;
		number = 0;
		
		for( a = 0;a <4 ;a++ )//��һ����������Ϊa
		{
			for( b =0 ;b < 4;b++ )//�ڶ�����������Ϊb
			{
				if( b!=a ) //b��a����ͬ
				{ 
				    for( c = 0;c < 4;c++ )//��������������Ϊc
					{
				        if( c!=a && c!=b )//c��b��a����ͬ
						{
							for( d = 0;d < 4;d++ )//���ĸ���������Ϊd 
							{
								if( d!=a && d!=b && d!=c )//d��c��b��a����ͬ
								{
									allpath4[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *)*5);
									/*allpath[i]Ϊ��i��·�ߣ����������ָ��������ָ��*/
									while( allpath4[i]==NULL )//allpath[i]Ϊ��i��·�ߣ����������ָ��������ָ��)
									{
										allpath4[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *)*5);
										/*allpath[i]Ϊ��i��·�ߣ����������ָ��������ָ��*/
									}
									allpath4[i][0] = &allpathpoint[a];//��i��·�ߵĵ�һ���������a�������
									allpath4[i][1] = &allpathpoint[b];//��i��·�ߵĵڶ����������b�������
									allpath4[i][2] = &allpathpoint[c];//��i��·�ߵĵ������������c�������
									allpath4[i][3] = &allpathpoint[d];//��i��·�ߵĵ��ĸ��������d�������
								    i++;//·�߼�һ
								}
							}
						}		
				    }  	
				}
			}
		}//���������������򣬼�����·��
		
		for( i =0 ,timemin = 100000;i < 24;i++ )//�ж�24��·���Ƿ���в��������
		{
			timemin = 100000;
			
			for( j = 0;j < 4 && allpath4[i]!=NULL;j++ )//�жϵ�i��·���Ƿ��ж����е�ʳ���ڲ͹�ǰ��
			{
				if( allpath4[i][j]->order->current==1 && allpath4[i][j]->n==0 )//����������ڴ�ȡ�Ͷ��������ǲ͹�
				{
					for( k = 0;k < 4;k++ )//�������ҵ��͸������ͬ��һ��������ʳ��
					{
						if(allpath4[i][k]->order->current==1 && allpath4[i][k]->n==1 && allpath4[i][j]->order==allpath4[i][k]->order)
						/*��������Ƿ�����������ͬ��һ������������ʳ��*/
						{
							temp = k;//��¼���������� 
						}
					}
					
					if(allpath4[i][temp]->order->current==1 && allpath4[i][temp]->n==1 && allpath4[i][j]->order==allpath4[i][temp]->order)
					/*��������Ƿ�����������ͬ��һ������������ʳ��*/
					{
						if( temp < j ) //�Ƿ�ʳ���ڲ͹�ǰ��
						{
							timemin = 150000;
						}
					}
				}
			}
			
			if( timemin!=150000 )//�Ƿ�i��·��δ�ϳ�
			{
				timer = (abs(allriders[num].x - allpath4[i][0]->x) + abs(allriders[num].y - allpath4[i][0]->y)) / 2;
				/*���ֵ�i��·�ߵ�һ����������軨��ʱ��*/
				allpath4[i][0]->time = time + timer;//�����i��·�ߵ�һ������㵽��ʱ
				for( j = 0;j < 3;j++ )//������������㵽��ʱ��
				{
					timer += ((abs(allpath4[i][j]->x - allpath4[i][j+1]->x) + abs(allpath4[i][j]->y - allpath4[i][j+1]->y)) / 2);
					/*����ӵ�j������㵽��j+1�����������ʱ��*/
					allpath4[i][j+1]->time = timer + time; //���㵽��j+1��������ʱ�� 
				}
				
				for( j = 0;j < 4 && allpath4[i]!=NULL;j++ )//������i��·����������㣬�ж����Ƿ�ʱ
				{
					if(allpath4[i][j]->order->time + LIMIT<=allpath4[i][j]->time)//��i��·�ߵ�j��������Ƿ�ʱ
					{
						timemin = 150000;   
					} 
	            }
	            
	            if( timemin!=150000 )//�Ƿ�i��·�߷ϳ�
	            {
	            	if( timer < timemin )//�Ƿ�ʱ�����
	            	{
	            		timemin = timer;//Ŀǰ���ʱ�丳ֵ
	            		number = i;//ĿǰԤ��·�߸�ֵ
					}
				}
			}
		}
		if(number==0)  allriders[num].finaltask = allriders[num].temporarytask[0];//��·��������ȡ��һ����ΪĿ��� 
		else allriders[num].finaltask = allpath4[number][0]->order;
		/*���·�ߵĵ�һ�������Ķ���ָ�븳�����ֵ�ǰĿ���*/
		
		for( i = 0;i < 24;i++ ) free(allpath4[i]);//�ͷ�����·��
	}
	
	else if(number==5)//��ǰ����������
	{
		struct pathpoint **allpath5[200];//���峤��Ϊ150��ָ��ָ���ָ������
		i = 0;
		number = 0;
		
		for( a = 0;a < 5;a++ )//��һ����������Ϊa
		{
			for( b =0 ;b < 5;b++ )//�ڶ�����������Ϊb
			{
				if( b!=a ) //b��a����ͬ
				{ 
				    for( c = 0;c < 5;c++ )//��������������Ϊc
					{
				        if( c!=a && c!=b )//c��b��a����ͬ
						{
							for( d = 0;d < 5;d++ )//���ĸ���������Ϊd
							{
								if( d!=a && d!=b && d!=c )//d��c��b��a����ͬ
								{
									for( e = 0;e < 5;e++ )//�������������Ϊe
									{
										if( e!=a && e!=b && e!=c && e!=d )//e��d��c��b��a����ͬ
										{
											allpath5[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *)*6);
											/*allpath[i]Ϊ��i��·�ߣ�����������ָ��������ָ��*/
											while( allpath5[i]==NULL )
											{
												allpath5[i] = (struct pathpoint **)malloc(sizeof(struct pathpoint *)*6);
												/*allpath[i]Ϊ��i��·�ߣ�����������ָ��������ָ��*/
											}
											allpath5[i][0] = &allpathpoint[a];//��i��·�ߵĵ�һ���������a�������
											allpath5[i][1] = &allpathpoint[b];//��i��·�ߵĵڶ����������b�������
											allpath5[i][2] = &allpathpoint[c];//��i��·�ߵĵ������������c�������
											allpath5[i][3] = &allpathpoint[d];//��i��·�ߵĵ��ĸ��������d�������
											allpath5[i][4] = &allpathpoint[e];//��i��·�ߵĵ�����������e�������
											i++;//·�߼�һ
									    }
									}
								}
							}
						}		
				    }  	
				}
			}
		}//���������������򣬼�����·��
		
		for( i = 0,timemin = 100000;i < 120;i++ )//�ж�120��·���Ƿ���в��������
		{
			timemin = 100000;
			
			for( j = 0;j < 5 && allpath5[i]!=NULL;j++ )//�жϵ�i��·���Ƿ��ж����е�ʳ���ڲ͹�ǰ��
			{
				if(allpath5[i][j]->order->current==1 && allpath5[i][j]->n==0)//����������ڴ�ȡ�Ͷ��������ǲ͹�
				{
					for( k = 0;k < 5;k++ )//�������ҵ��͸������ͬ��һ��������ʳ��
					{
						if(allpath5[i][k]->order->current==1 && allpath5[i][k]->n==1 && allpath5[i][j]->order==allpath5[i][k]->order)
						/*��������Ƿ�����������ͬ��һ������������ʳ��*/
						{
							temp = k; //��¼���������� 
						}
					}
					
					if(allpath5[i][temp]->order->current==1 && allpath5[i][temp]->n==1 && allpath5[i][j]->order==allpath5[i][temp]->order)
					/*��������Ƿ�����������ͬ��һ������������ʳ��*/
					{
						if( temp < j ) //�Ƿ�ʳ���ڲ͹�ǰ��
						{
							timemin = 150000;
						}
					}
				}
			}
			if( timemin!=150000 )//�Ƿ�i��·�߷ϳ�
			{
				timer = (abs(allriders[num].x - allpath5[i][0]->x) + abs(allriders[num].y - allpath5[i][0]->y)) /2 ;
				/*���ֵ�i��·�ߵ�һ����������軨��ʱ��*/
				allpath5[i][0]->time = time + timer;//�����i��·�ߵ�һ������㵽��ʱ��
				for( j = 0;j < 4;j++ )//������������㵽��ʱ��
				{
					timer += ((abs(allpath5[i][j]->x - allpath5[i][j+1]->x) + abs(allpath5[i][j]->y - allpath5[i][j+1]->y)) / 2);
					/*����ӵ�j������㵽��j+1�����������ʱ��*/
					allpath5[i][j+1]->time = timer + time; //���㵽��j+1��������ʱ�� 
				}
				
				for( j = 0;j < 5 && allpath5[i]!=NULL;j++ )//������i��·����������㣬�ж����Ƿ�ʱ
				{
					if( allpath5[i][j]->order->time + LIMIT <= allpath5[i][j]->time )
					/*��i��·�ߵ�j��������Ƿ�ʱ*/
					{
						timemin = 150000;
					}
	            }
	            
	            if( timemin!=150000 )//�Ƿ�i��·�߷ϳ�
	            {
	            	if( timer < timemin )//�Ƿ�ʱ�����
	            	{
	            		timemin = timer;//Ŀǰ���ʱ�丳ֵ
	            		number = i;//ĿǰԤ��·�߸�ֵ
					}
				}
			}
		}
		if( number==0 ) allriders[num].finaltask = allriders[num].temporarytask[0];//��·��������ȡ��һ����ΪĿ��� 
		else allriders[num].finaltask = allpath5[number][0]->order;
		/*���·�ߵĵ�һ�������Ķ���ָ�븳�����ֵ�ǰĿ���*/
		
		for( i = 0;i < 120;i++ ) free(allpath5[i]);//�ͷ�����·��
	}
} 

