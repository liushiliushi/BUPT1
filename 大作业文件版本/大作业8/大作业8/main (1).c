#include<stdio.h>
#include<stdlib.h>
#include<head.h>//��������õ�ͷ�ļ� 
int money=100,ridernumber=3,time=0,temp=0,accept=0,over=0,finish=0;//�Ǿ�̬ȫ�ֱ��������ʼֵ�Ķ��� 
struct order *firstorder;//ͷ����ָ�� 
struct rider allriders[50];//����������Ϣ 
main()
{
	int buy=0//�ж��Ƿ����»�������ĸ������� 
    input();//�������� 
    devide();//����3�����ֵ����� 
	while(temp==0)//��������ѭ�� 
	{
		if(buy!=0) //������������ 
		{
		    devide();//�������� 
			buy=0;	// �ж��Ƿ����»�������ĸ���������λ 
		}
		
		decide();//���䶩�� 
		bestwaywhile();//Ϊ�������ֹ滮·�� 
		addwhile();//ʹ���������ƶ�������״̬�ı� 
		time++;//ʱ���ƽ�һ��ʱ�䵥λ 
		pictureoutput();//ͼ�λ���� 
		txtoutput();//�ı���� 
		buy=buy();//�ж��Ƿ������ֲ����� 
    }
    
    if(temp==0) prnitf("����ȫ��������\n");//��Ϊ����ȫ���������ѭ�� 
    else if(temp==1) printf("��������������\n");//��Ϊ������������������ѭ�� 
    else if(temp==2) printf("���Ʋ�\n");//��Ϊ���Ʋ�����ѭ�� 
	else printf("����ʱ�䵥λδ�ɵ��ɹ�\n");//��Ϊ����ʱ�䵥λδ�ɵ��ɹ�����ѭ�� 
	return 0;
	 
}	







 





























} 
