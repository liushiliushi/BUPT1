#include<stdio.h>
#include<stdlib.h>
#include "head.h"
#include "main.h"
#define LIMIT 30
#define BIGLIMIT 60
extern int time;
extern struct order * firstorder;//ͷ����ָ�� 
void addwhile()
{
	int i,j;
	struct order *ptr=firstorder;
	
	for(i=0;i<ridernumber;i++) 
	{
		add(allriders,i);
	}
	if(money<0)//�ж��Ƿ��Ʋ� 
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
	int x3,y3,j;//���ֵ�ǰ��Ŀ��� 
	int x=allriders[i].x,y=allriders[i].y;//���ֵ�ǰ���� 
	if(allriders[i].finaltask==NULL) 
	{
		return ;
	}
	if(allriders[i].finaltask->current==1)//�������ȡ�� 
	{
		x3=allriders[i].finaltask->cx;
		y3=allriders[i].finaltask->cy;
	}
	else if(allriders[i].finaltask->current==2)//��������Ͳ�
	{
		x3=allriders[i].finaltask->sx;
		y3=allriders[i].finaltask->sy;
	} 
	if(x%2==1)//�������ԭ���ں�ֵ��� 
	{
		if(x==x3-1||x==x3+1)//���������Ŀ�������ڽֵ��ϣ������������ת�䣩 
		{
			if(y==y3)//����Ѿ�����
			{
				meet(allriders,i);
			}
			else//���û�� ,ֻ��ı�y���� ������Ҫת�� 
			{
				if(y>y3)
				{
					allriders[i].y-=2;
					if(y==y3+2)//���������� 
					{
						meet(allriders,i);
					}
				}	
				else
				{
					allriders[i].y+=2;
					if(y==y3-2)//���������� 
					{
						meet(allriders,i);
					}
				}
			} 
		}
		else//��Ҫת������
		{
			if(y==y3)
			{
				if(y==0)//����������,ֻ����ת 
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
				else if(y==16)//��������ұߣ�ֻ����ת 
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
				else//������ 
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
			else if(y==y3-2)//����ת��� 
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
			else if(y==y3+2)//����ת��� 
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
			else if(y<y3-2)//����ת��� 
			{
				allriders[i].y+=2;
			}
			else if(y>y3+2)//����ת��� 
			{
				allriders[i].y-=2;
			}
		} 
	}
	if(y%2==1)//�������ԭ���ں�ֵ��� 
	{
		if(y==y3-1||y==y3+1)//���������Ŀ�������ڽֵ��ϣ������������ת�䣩 
		{
			if(x==x3)//����Ѿ�����
			{
				meet(allriders,i);
			}
			else//���û�� ,ֻ��ı�y���� ������Ҫת�� 
			{
				if(x>x3)
				{
					allriders[i].x-=2;
					if(x==x3+2)//���������� 
					{
						meet(allriders,i);
					}
				}	
				else
				{
					allriders[i].x+=2;
					if(x==x3-2)//���������� 
					{
						meet(allriders,i);
					}
				}
			} 
		}
		else//��Ҫת������
		{
			if(x==x3)
			{
				if(x==0)//����������,ֻ����ת 
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
				else if(x==16)//��������ұߣ�ֻ����ת 
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
				else//������ 
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
			else if(x==x3-2)//����ת��� 
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
			else if(x==x3+2)//����ת��� 
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
			else if(x<x3-2)//����ת��� 
			{
				allriders[i].x+=2;
			}
			else if(x>x3+2)//����ת��� 
			{
				allriders[i].x-=2;
			}
		} 
	}
}
void meet(struct rider *allriders,int i)
{
	allriders[i].change=0;//����Ŀ�����Ҫ������һ��Ŀ��� 
	if(allriders[i].finaltask->current==1)//�������ȡ�� 
	{
		allriders[i].stop=1;//ͣ���ڲ͹� 
		allriders[i].finaltask->current=2;//�ı䶩��״̬Ϊ���Ͳ� 
	}
	else if(allriders[i].finaltask->current==2)//��������Ͳ� 
	{
		allriders[i].stop=2;//ͣ����ʳ�� 
		int a=allriders[i].currentnumber;//���ֵĶ��������е�����
		int tem,j;//Ŀ�궩���������е���� 
		int flag=0;
		for(j=0;j<a&&flag==0;j++)
		{
			if(allriders[i].finaltask->num==allriders[i].temporarytask[j]->num)//���Ŀ�궩���������е�����������һ�� 
			{
				tem=j;
				flag=1;
			}	
		} 
		for(j=tem;j<a-1;j++)
		{
			allriders[i].temporarytask[j]=allriders[i].temporarytask[j+1];//��������ǰ�� 
		}
		allriders[i].currentnumber-=1;
		allriders[i].temporarytask[a-1]=NULL;
        if(time<=allriders[i].finaltask->time+LIMIT)//���δ��ʱ ����ô��10 
		{
			money+=10;
			allriders[i].finish+=1;//���ֶ��������+1 
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
