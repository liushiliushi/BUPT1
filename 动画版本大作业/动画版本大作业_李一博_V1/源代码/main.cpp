#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include<process.h> 
#include"head.h"//��������õ�ͷ�ļ� 
#include"input.h"
/*include��*/ 

#define length 50
#define width 40 
/*�궨����*/ 

int money=1000,ridernumber=0,time=0,temp=0,allaccept=0,over=0,finish=0,buytemp,all=0,prefinish,preover;
/*�Ǿ�̬ȫ�ֱ��������ʼֵ�Ķ��� */
struct order * firstorder;//ͷ����ָ�� 
struct rider allriders[50];//����������Ϣ 
/*�ṹ��������ָ�붨����*/ 

void destory(LISTNODEPTR);

int main()
{
    int buytemp = 0;//�ж��Ƿ����»�������ĸ������� 
    
    HANDLE hthread1;//�̵߳ķ��ʾ�� 
    unsigned threadid = 1;//�̵߳ı�ʶ�� 
    
	initgraph(1280,720);//��ʼ��ͼ�ο� 
	
    hthread1 = (HANDLE)_beginthreadex(NULL,0,input,NULL,0,&threadid);//������Ӧ��input�������߳� 
    
    buytemp = buy();//�ж��Ƿ������ֲ�����
    
	while( temp==0 && !kbhit() )//��������ѭ�� 
	{
		if( buytemp!=0 ) //������������ 
		{
		    divide();//���»������� 
		}
		
		decide();//���䶩��
		
		cleardevice();//����
       	cartoonoutput();//������� 
		
		bestwaywhile();//Ϊ�������ֹ滮·�� 
		
		addwhile();//ʹ���������ƶ�������״̬�ı� 
		
		time++;//ʱ���ƽ�һ��ʱ�䵥λ 
		
		buytemp = buy();//�ж��Ƿ������ֲ�����	
		
	    Sleep(1000);
	}

    WaitForSingleObject(hthread1,INFINITE);//�ȴ��߳̽���
	CloseHandle(hthread1);//ɾ����� 
	
	
	getch();
	closegraph();//�ر�ͼ�ν��� 
	
	destory(firstorder);
    return 0;
}	

void destory(LISTNODEPTR headPtr)//�ͷ����� 
{

	LISTNODEPTR tempPtr = NULL;

	while( headPtr != NULL )//�����ͷ��������� 
	{
		tempPtr = headPtr;
		headPtr = headPtr->orderptr;
		free(tempPtr);
	}

}

