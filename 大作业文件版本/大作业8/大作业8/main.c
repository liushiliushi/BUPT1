#include<stdio.h>
#include<stdlib.h>
#include"head.h"//��������õ�ͷ�ļ� 
#include"input.h"

int money=1000,ridernumber=0,time=0,temp=0,accept=0,over=0,finish=0,buytemp,all=0,prefinish,preover;//�Ǿ�̬ȫ�ֱ��������ʼֵ�Ķ��� 
struct order * firstorder;//ͷ����ָ�� 
struct rider allriders[50];//����������Ϣ 
void destory(LISTNODEPTR);

int main()
{
    int buytemp=0;//�ж��Ƿ����»�������ĸ������� 
    input();//�������� 
    buytemp=buy();//�ж��Ƿ������ֲ�����
	while(temp==0)//��������ѭ�� 
	{
		if(buytemp!=0) //������������ 
		{
		    divide();//���»������� 
		}
		decide();//���䶩��
		
		txtoutput();//�ı���� 
		pictureoutput();//ͼ�λ����
		
		if(all==finish) temp=3;
		bestwaywhile();//Ϊ�������ֹ滮·�� 
		
		preover=over;
		prefinish=finish;//������һʱ�����������ʱ�� 
		
		addwhile();//ʹ���������ƶ�������״̬�ı� 
		time++;//ʱ���ƽ�һ��ʱ�䵥λ 
		buytemp=buy();//�ж��Ƿ������ֲ�����	
	    
		//system("pause"); 
	    Sleep(2000);
	}

    if(temp==1) printf("��������������\n");//��Ϊ������������������ѭ�� 
    else if(temp==2) printf("���Ʋ�\n");//��Ϊ���Ʋ�����ѭ�� 
    else if(temp==3) printf("������ȫ��������\n");//��Ϊ������ȫ����������˳�ѭ�� 
	else printf("����ʱ�䵥λδ�ɵ��ɹ�\n");//��Ϊ����ʱ�䵥λδ�ɵ��ɹ�����ѭ�� 
	destory(firstorder);
    return 0;

}	

void destory(LISTNODEPTR headPtr)
{

	LISTNODEPTR tempPtr = NULL;

	while(headPtr != NULL)
	{

		tempPtr = headPtr;
		headPtr = headPtr->orderptr;
		free(tempPtr);
	}

}
