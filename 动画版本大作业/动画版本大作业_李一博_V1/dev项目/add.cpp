#include<stdio.h>
#include<stdlib.h>
#include "head.h"
#include "main.h"
/*include��*/
 
#define LIMIT 30
#define BIGLIMIT 60
/*�궨����*/ 

extern int time;
extern struct order * firstorder;//ͷ����ָ�� 
/*�ṹ���࣬������ָ�붨����*/
 
void add(struct rider *,int);
void meet(struct rider *,int);

void addwhile()//���������ֽ����ƶ� 
{
	int i,j;
	struct order *ptr = firstorder;
	
	if( firstorder==NULL ) return;//��ǰ�޶��� 
	
	for( i = 0;i < ridernumber;i++ ) //���������ֽ����ƶ� 
	{
		add(allriders,i);//��i�����ֽ����ƶ� 
	}
	
	if( money < 0 )//�ж��Ƿ��Ʋ� 
	{
		temp = 2;
	}
	
	for( i = 0;i < ridernumber;i++ )//�ж��Ƿ�ʱ��������� 
	{
	    for( j = 0;j < allriders[i].currentnumber;j++ )
		{
			if( allriders[i].temporarytask[j]->time + LIMIT==time )//�ж��Ƿ�ʱ 
			{
				allriders[i].over++;//���ֳ�ʱ����һ 
				over++;//�ܳ�ʱ����һ 
				money -= 50;//��Ǯ50 
			}
			else if( allriders[i].temporarytask[j]->time + BIGLIMIT < time )//�ж��Ƿ�������� 
			    temp = 1;
		}	
	} 
	
	while( ptr->time < time && ptr->orderptr!=NULL )//�ж��Ƿ�3��ʱ�䵥λ���ɵ��ɹ� 
	{
		if( ptr->current==0 )//�Ƿ�õ�δ�ɵ� 
		{
			if( ptr->time + 3 < time )
			    temp = 4;
		}
		ptr = ptr->orderptr;
	}
}

void add(struct rider *allriders,int i)//��i�����ֽ����ƶ� 
{
	int x3,y3,j;//���ֵ�ǰ��Ŀ��� 
	int x = allriders[i].x,y = allriders[i].y;//���ֵ�ǰ���� 
	
	if( allriders[i].finaltask==NULL ) //�Ƿ�ǰ�����޴��͵� 
	{
		return ;
	}
	
	if( allriders[i].finaltask->current==1 )//�������ȡ�� 
	{
		x3 = allriders[i].finaltask->cx;
		y3 = allriders[i].finaltask->cy;
	}
	else if( allriders[i].finaltask->current==2 )//��������Ͳ�
	{
		x3 = allriders[i].finaltask->sx;
		y3 = allriders[i].finaltask->sy;
	} 
	
	if( x % 2==1 )//�������ԭ���ں�ֵ��� 
	{
		if( x==x3 - 1 || x==x3 + 1 )//���������Ŀ�������ڽֵ��ϣ������������ת�䣩 
		{
			if( y==y3 )//����Ѿ�����
			{
				meet(allriders,i);
			}
			else//���û�� ,ֻ��ı�y���� ������Ҫת�� 
			{
				if(y > y3)
				{
					allriders[i].y -= 2;
					if( y==y3 + 2 )//���������� 
					{
						meet(allriders,i);
					}
				}	
				else
				{
					allriders[i].y += 2;
					if( y==y3 - 2 )//���������� 
					{
						meet(allriders,i);
					}
				}
			} 
		}
		else//��Ҫת������
		{
			if( y==y3 )
			{
				if( y==0 )//����������,ֻ����ת 
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
				else if( y==16 )//��������ұߣ�ֻ����ת 
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
				else//������ 
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
			else if( y==y3 - 2 )//����ת��� 
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
			else if( y==y3 + 2 )//����ת��� 
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
			else if( y < y3 - 2 )//����ת��� 
			{
				allriders[i].y += 2;
			}
			else if( y > y3 + 2 )//����ת��� 
			{
				allriders[i].y -= 2;
			}
		} 
	}
	
	if( y % 2==1 )//�������ԭ�������ֵ��� 
	{
		if( y==y3 - 1 || y==y3 + 1 )//���������Ŀ�������ڽֵ��ϣ������������ת�䣩 
		{
			if( x==x3 )//����Ѿ�����
			{
				meet(allriders,i);
			}
			else//���û�� ,ֻ��ı�y���� ������Ҫת�� 
			{
				if( x > x3 ) 
				{
					allriders[i].x -= 2;
					if( x==x3 + 2 )//���������� 
					{
						meet(allriders,i);
					}
				}	
				else
				{
					allriders[i].x += 2;
					if( x==x3 - 2 )//���������� 
					{
						meet(allriders,i);
					}
				}
			} 
		}
		else//��Ҫת������
		{
			if( x==x3 )
			{
				if( x==0 )//����������,ֻ����ת 
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
				else if( x==16 )//��������ұߣ�ֻ����ת 
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
				else//������ 
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
			else if( x==x3 - 2 )//����ת��� 
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
			else if( x==x3 + 2 )//����ת��� 
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
			else if( x < x3 - 2 )//����ת��� 
			{
				allriders[i].x += 2;
			}
			else if( x > x3 + 2 )//����ת��� 
			{
				allriders[i].x -= 2;
			}
		} 
	}
}

void meet(struct rider *allriders,int i)
{
	int flag = 0,a,tem,j;//���ֵĶ��������е�����,Ŀ�궩���������е���� 
	
    allriders[i].change = 0;//����Ŀ�����Ҫ������һ��Ŀ��� 
    
	if( allriders[i].finaltask->current==1 )//�������ȡ�� 
	{
		allriders[i].stop = 1;//ͣ���ڲ͹� 
		allriders[i].finaltask->current = 2;//�ı䶩��״̬Ϊ���Ͳ� 
	}
	else if( allriders[i].finaltask->current==2 )//��������Ͳ� 
	{
		allriders[i].stop = 2;//ͣ����ʳ�� 
		a=allriders[i].currentnumber;//���ֵĶ��������е�����
		
		for( j = 0;j < a && flag==0;j++ )
		{
			if( allriders[i].finaltask->num==allriders[i].temporarytask[j]->num )//���Ŀ�궩���������е�����������һ�� 
			{
				tem = j;
				flag = 1;
			}	
		} 
		for( j = tem;j < a - 1;j++ )
		{
			allriders[i].temporarytask[j] = allriders[i].temporarytask[j+1];//��������ǰ�� 
		}
		allriders[i].currentnumber -= 1;
		allriders[i].temporarytask[a-1] = NULL;
		
        if( time <= allriders[i].finaltask->time + LIMIT )//���δ��ʱ ����ô��10 
		{
			money += 10;//׬10Ԫ 
			allriders[i].finish += 1;//���ֶ��������+1 
			finish++;//���������һ 
			allriders[i].finaltask->current = 3;//�õ�״̬��Ϊ����� 
		}
		else if(time <= allriders[i].finaltask->time + BIGLIMIT)//�õ��Ѿ���ʱ��û�ж������� 
		{
			allriders[i].finish++;//�������������һ 
			finish++;//���������һ 
			allriders[i].finaltask->current = 4;//�ĵ�״̬Ϊ����ʱ��� 
		}
		else temp = 1;
	} 
}
