#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include"head.h"
/*include��*/
 
#define length 50
#define width 40 
/*�궨����*/ 

extern int money,ridernumber,time,allaccept,over,finish;//�Ǿ�̬ȫ�ֱ��������ʼֵ�Ķ��� 
extern struct order * firstorder;//ͷ����ָ�� 
extern struct rider allriders[50];//����������Ϣ 
/*����,ָ��,�ṹ��*/ 

void background(); // ���Ʊ��� 
void variableoutput();//���ʱ�䡢Ǯ���ӵ��������������ʱ���ȱ��� 
void otheroutput();//������֡��͹ݡ�ʳ��

extern void cartoonoutput()//������� 
{
	
	background();//���Ʊ��� 
	variableoutput();//������� 
	otheroutput();//���ͼ�� 
		
}

void background()//���Ʊ��� 
{
	int i,j;
	int x = 80, y = 80;
	PIMAGE img;//����imgΪͼƬ���͵ı��� 

	
	setbkcolor(WHITE); //���õ�ɫ 
	setcolor(BLACK);
	setfillcolor( EGERGB(255,216,103) );//���÷���������ɫΪǳ��ɫ 
	for(i = 0 ; i < 9 ; i++)//����9X9���� 
	{
		for (j = 0 ; j < 9 ; j++)
		{
			bar(x, y, x+length, y+width);
			x = x + length + 30;
	}
		y = y + width + 25;
		x = 80;
	} 
	
	setbkmode(TRANSPARENT);//�����屳��ɫ��Ϊ͸�� 
	setfont(30, 0, "���Ŀ���");//ָ������߶ȿ��
	
	outtextxy(440, 20, "�����ɵ�ģ��ϵͳ");
	outtextxy(900, 100, "ʱ�䣺");
	outtextxy(900, 160, "Ǯ��");
	outtextxy(900, 220, "�ӵ�����"); 
	outtextxy(900, 280, "�������");
	outtextxy(900, 340, "���𶩵���ţ�");
	outtextxy(900, 400, "��ɶ�����ţ�"); 
	
	img=newimage();
	getimage(img, "��ť1.jpg", 0, 0);
	putimage(900, 450, img);//���˳���ťͼƬ��ͼ 
}

void variableoutput()//������� 
{
	xyprintf(990, 100, "%d", time);//���ʱ�� 
	xyprintf(990, 160, "%d", money);//��Ǯ 
	xyprintf(1020, 220, "%d", allaccept);//�ܽӵ��� 
	xyprintf(1020, 280, "%d", finish);//����� 

}

void otheroutput()//���ͼ�� 
{
	struct order *allorders[300], *orderptr = firstorder;//��Ҫͼ��չʾ�Ķ���ָ�����飬����ָ�� 
	int i, j, x, y, a, b;//i��jΪѭ��������x��yΪ���λ�ã�a,b����xy���꣬���ڸ�ֵ 
	int temp = 0, m = 0, q = 0;// tempΪ�����жϱ�����m,q���ڼ��� 
	int neworders[10];
	
	for(i = 0,j = 0; orderptr!=NULL && orderptr->time <= time; i++)//�ж��Ƿ��Ѿ������Ķ��� 
	{
		
		if(orderptr->current < 3)//�ж��Ƿ�δ�����꣬δ����������Ҫͼ�λ�չʾ 
		{   
		    allorders[j] = orderptr;//������ɸѡ�Ķ�����ָ����붩��ָ������ 
			j++;
		} 
		
		if(orderptr->time == time)//����ǰʱ�䷢���Ķ��������� 
		{
			setfont(30, 0, "���Ŀ���");
			xyprintf(1100+q, 340, "%d", orderptr->num); 
  			q += 40;
		}
		
		orderptr = orderptr->orderptr;//�ж���һ������ 
		
	}


	for(x = 0 ; x < 17 ; x++)//���0��16�е���� 
	{
		for(y = 0 ; y < 17 ; y++)//�����y�е���� 
		{
	    	for(i = 0 ; i < j && temp == 0 ; i++)//Ѱ��x��y���Ƿ��в͹ݻ�ʳ�� 
			{
				
				if(allorders[i]->cx == x && allorders[i]->cy == y) temp=1;//x��y���в͹� 
				if(allorders[i]->sx == x && allorders[i]->sy == y) temp=2;//x��y����ʳ�� 
				
		 		if(temp == 1)//�в͹� 
				{
					
					setfont(20, 0, "���Ŀ���");
					setfillcolor(EGERGB(255, 177, 208));
					bar((y/2)*80 + 80, (x/2)* 65 + 80, (y/2)*80 + 80 + length, (x/2)*65 + 80 + width);
					/*�����͹�Ϊ��ɫ*/ 
					outtextxy(98 + 80*(y/2), 90 + 65*(x/2), "A");//����͹ݣ���A 
					
				} 
				else if(temp == 2)//��ʳ�� 
				{
					
					setfont(20, 0, "���Ŀ���");
					setfillcolor(EGERGB(255, 177, 208));
					bar((y/2)*80 + 80, (x/2)* 65 + 80, (y/2)*80 + 80 + length, (x/2)*65 + 80 + width);
					/*����ʳ��Ϊ��ɫ*/ 
					outtextxy(98 + 80*(y/2), 90 + 65*(x/2), "B");//���ʳ�ͣ���B
					
				}
				
			}
			
		 	temp = 0;//�����жϱ�����λ 
		 	
		 	for(i = 0 ; i < ridernumber && temp == 0 ; i++)//�ж�x��y���Ƿ������� 
		 	{
		 		
				if(allriders[i].x == x && allriders[i].y == y) temp=1;//x��y��������	
		 
		 		if(temp == 1) //������� 
		 		{
		 			
		 			setfont(15, 0, "���Ŀ���");
		 		
					if(y%2 == 0)//�ں�ֵ� 
					xyprintf(90 + 80*(y/2), 125 + 65*(x-1)/2, "����%d", i);
					else if(x%2 == 0)//���ݽֵ� 
					xyprintf(128 + 80*(y-1)/2, 88 + 65*(x/2), "����%d", i);
					
				}
				
			}//end of for 
			
			temp=0;//�����жϱ�����λ 
			
		}// end of for 
	   
	}//end of for 
	

	for(i = 0; i < ridernumber; i++)//������� 
  	{
  		
  		if(allriders[i].stop == 1)//���ͣ���ڲ͹� ���������� 
  		{
  			
  			a = allriders[i].finaltask->cx;
  			b = allriders[i].finaltask->cy; 
  			
  			setfont(20, 0, "���Ŀ���");
  			setfillcolor(EGERGB(126, 202, 218));
			bar((b/2)*80 + 80, (a/2)*65 + 80, (b/2)*80 + 80 + length, (a/2)*65 + 80 + width);
			/*����ͣ�����Ĳ͹�Ϊ��ɫ*/ 
			outtextxy(98 + 80*(b/2), 90 + 65*(a/2), "A");//����͹ݣ���A 
			
			allriders[i].finaltask = NULL;
			allriders[i].stop = 0;//��Ϊ��ͣ����״̬ 
			
  		} 
		else if( allriders[i].stop == 2 ) //���ͣ����ʳ�ͣ���ʱ˳�������ɵĶ�����ţ����������� 
  		{
  			
  			a = allriders[i].finaltask->sx;
  			b = allriders[i].finaltask->sy;
  			
  			setfont(30, 0, "���Ŀ���");
  			xyprintf(1100 + m, 400, "%d", allriders[i].finaltask->num); 
  			m += 40;
  			
  			setfont(20, 0, "���Ŀ���");
  			setfillcolor(EGERGB(126, 202, 218));
			bar((b/2)*80 + 80, (a/2)*65 + 80, (b/2)*80 + 80 + length, (a/2)*65 + 80 + width);
			/*����ͣ������ʳ��Ϊ��ɫ*/ 
			outtextxy(98 + 80*(b/2), 90 + 65*(a/2), "B");//���ʳ�ͣ���B 
			
			allriders[i].finaltask = NULL;
			allriders[i].stop = 0;//��Ϊ��ͣ����״̬ 	
			
		}
		
	}//end of for
	
	 
 } 
 
 
