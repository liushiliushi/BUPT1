#include<stdio.h>
#include<stdlib.h>
#include"head.h" 

extern int money,ridernumber,time,temp,accept,over,finish,prefinish,preover;//�Ǿ�̬ȫ�ֱ��������ʼֵ�Ķ��� 
extern struct order * firstorder;//ͷ����ָ�� 
extern struct rider allriders[50];//����������Ϣ 
extern txtoutput()//�ı��������    
{
  	int i,m,j = 0;//Ϊ������������׼�� 
  	FILE *p;//ָ���ļ�output.txt��ָ�� 

  	p=fopen("output.txt","a");//���ļ� 
  	fprintf( p , "ʱ�䣺%d\n" , time );//�����ǰʱ�� 
  	fprintf( p , "Ǯ��%d\n" , money );//�����ǰǮ�� 
  	fprintf( p , "�ӵ�����%d\n" , accept );//�����ǰ�ӵ���  
  	fprintf( p , "�������%d�� �ᵥ��" , finish );//�����ǰ����� 
	for( m = 0 ; m < ridernumber ; m++ )//����ÿһ�����֣��������ʳ�ʹ�����ᵥ 
	{
		if(allriders[m].stop==2)//���ͣ����ʳ�� 
		{
			fprintf( p , "%d" , allriders[m].finaltask->num );
			j++;
			if(j!=finish-prefinish)
			fprintf( p , " " );
		}
	}
	fprintf( p , "��\n" );
	j=0;
	fprintf( p , "��ʱ����%d�� ������" , over );//�����ǰ��ʱ�� 
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
	fprintf(p,"��\n");
	for(i=0;i<ridernumber;i++)
  	{ 
  		fprintf(p,"����%dλ�ã�%d��%d��ͣ����",i,allriders[i].x,allriders[i].y);//�����������λ�� 
		if(allriders[i].stop==0)//�����ͣ�� 
		fprintf(p,"��\n");
		else if(allriders[i].stop==1)//���ͣ���ڲ͹� 
		fprintf(p,"�͹� %d %d��\n",allriders[i].finaltask->cx,allriders[i].finaltask->cy);
		else if(allriders[i].stop==2)//���ͣ����ʳ�� 
		fprintf(p,"ʳ�� %d %d��\n",allriders[i].finaltask->sx,allriders[i].finaltask->sy);
	} 
	fclose(p);//�ر��ļ� 
} 
extern pictureoutput()//ͼ��������� 
{
	struct order *allorders[300],*orderptr=firstorder;//��Ҫͼ��չʾ�Ķ���ָ�����飬����ָ�� 
	int i,j,x,y,temp=0,m,q;//x��yΪ���λ�ã�i��jΪѭ��������tempΪ�����жϱ���,qΪ�������� 
	for(i=0,j=0;orderptr!=NULL&&orderptr->time<=time;i++)//�ж��Ƿ��Ѿ������Ķ��� 
	{
		if(orderptr->current<3)//�ж��Ƿ�δ������ 
		{   
		    allorders[j]=orderptr;//������ɸѡ�Ķ�����ָ����붩��ָ������ 
			j++;
		}
		orderptr=orderptr->orderptr;//�ж���һ������ 
	} //���ս���Ҫͼ��չʾ�Ķ�����ָ��ȫ�����붩��ָ��������
	//   	printf("%d",j); 
	for(x=0;x<16;x++)//���0��15�е���� 
	{
	   printf(" ______        ______        ______        ______        ______        ______        ______        ______        ______ \n");
	   printf("|      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |\n");//���ͼ���϶� 
	   for(y=0;y<16;y++)//�����x�е���� 
	   {
	     for(i=0;i<j&&temp==0;i++)//Ѱ��x��y���Ƿ��в͹ݻ�ʳ�� 
		 {
		   if(allorders[i]->cx==x&&allorders[i]->cy==y) temp=1;//x��y���в͹� 
		   if(allorders[i]->sx==x&&allorders[i]->sy==y) temp=2;//x��y����ʳ�� 
		  } 
		  	
		 if(temp==1) printf("| �͹� |");//����͹� 
		 else if(temp==2) printf("| ʳ�� |");//���ʳ�� 
		 else printf("|      |");//��ʾ���޲͹�Ҳ��ʳ�� 
		 y++;//������1 
		 temp=0;//�����жϱ�����λ 
		 for(i=0;i<ridernumber&&temp==0;i++)//�ж�x��y���Ƿ������� 
		 {
		   if(allriders[i].x==x&&allriders[i].y==y) temp=1;//x��y��������	
		 } 
		 if(temp==1) printf(" ���� ");//������� 
		 else printf("      ");//�������Ϊ�� 
		 temp=0;//�����жϱ�����λ 
	   }
	   for(i=0;i<j&&temp==0;i++)//�ж�x��16���Ƿ��в͹ݻ�ʳ�� 
	    {
		   if(allorders[i]->cx==x&&allorders[i]->cy==y) temp=1;//x��16���в͹� 
		   if(allorders[i]->sx==x&&allorders[i]->sy==y) temp=2;//x��16����ʳ�� 
	    }
	    if(temp==1) printf("| �͹� |\n");//x��16������͹� 
		else if(temp==2) printf("| ʳ�� |\n");//x��16�����ʳ�� 
		else printf("|      |\n");//x��16�����Ϊ�� 
		temp=0;//�����жϱ�����λ 
		x++;//������1 
		printf("|______|      |______|      |______|      |______|      |______|      |______|      |______|      |______|      |______|\n");//���ͼ���µ� 
		printf("\n");
		for(y=0;y<16;y+=2)//���x����� 
	   {
		 for(i=0;i<ridernumber&&temp==0;i++)//�ж�x��y���Ƿ������� 
		 {
		   if(allriders[i].x==x&&allriders[i].y==y) temp=1;//x��y��������	
		 } 
		 if(temp==1) printf("  ����        ");//������� 
		 else printf("              ");//��������� 
		 temp=0;//�����жϱ�����λ 
	   }
	   for(i=0;i<ridernumber&&temp==0;i++)//�ж�x��16���Ƿ������� 
		 {
		   if(allriders[i].x==x&&allriders[i].y==y) temp=1;	//x��16�������� 
		 } 
		 if(temp==1) printf("  ����  \n");//������� 
		 else printf("        \n");//��������� 
		 temp=0;//�жϱ�����λ 
	}
	printf(" ______        ______        ______        ______        ______        ______        ______        ______        ______ \n");
	printf("|      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |\n");//���16���϶� 
	for(y=0;y<16;y++)//���16����� 
	{
	    for(i=0;i<j&&temp==0;i++)//�ж�16�в͹ݻ�ʳ����� 
		{
		   if(allorders[i]->cx==x&&allorders[i]->cy==y) temp=1;//16��y���в͹� 
		   if(allorders[i]->sx==x&&allorders[i]->sy==y) temp=2;//16��y����ʳ�� 
		}	
		if(temp==1) printf("| �͹� |");//����͹� 
		else if(temp==2) printf("| ʳ�� |");//���ʳ�� 
		else printf("|      |");//������޲͹�Ҳ��ʳ�� 
		y++;//������һ 
		temp=0;//�����жϱ�����λ 
		for(i=0;i<ridernumber&&temp==0;i++)//�ж�16��y���Ƿ������� 
		{
		  if(allriders[i].x==x&&allriders[i].y==y) temp=1;//������	
		} 
		if(temp==1) printf(" ���� ");//������� 
		else printf("      ");//����� 
		temp=0;//�����жϱ�����λ  
	}
	for(i=0;i<j&&temp==0;i++)//���16��16����� 
	{
		if(allorders[i]->cx==x&&allorders[i]->cy==y) temp=1;//16��16���в͹� 
		if(allorders[i]->sx==x&&allorders[i]->sy==y) temp=2;//16��16����ʳ�� 
	}
	if(temp==1) printf("| �͹� |\n");//16��16������͹� 
	else if(temp==2) printf("| ʳ�� |\n");//16��16�����ʳ�� 
	else printf("|      |\n");//16��16������� 
	temp=0;
		printf("|______|      |______|      |______|      |______|      |______|      |______|      |______|      |______|      |______|\n");//�������ͼ���µ� 
	 
	printf("ʱ�䣺%d\n",time);//�����ǰʱ�� 
	printf("Ǯ��%d\n",money);//�����ǰǮ�� 
	printf("�ӵ�����%d\n",accept);//�����ǰ�ӵ��� 
	printf("�������%d�� �ᵥ��",finish);//�����ǰ����� 
	q=0; 
	for(m=0;m<ridernumber;m++)//����ÿһ�����֣��������ʳ�ʹ�����ᵥ 
	{
		if(allriders[m].stop==2)//���ͣ����ʳ�� 
		{
			printf("%d",allriders[m].finaltask->num);
			q++;
			if(q!=finish-prefinish)
			printf(" ");
		}
	}
	printf("��\n");
	q=0;
	printf("��ʱ����%d�� ������",over);//�����ǰ��ʱ�� 
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
	printf("��\n");
	for(i=0;i<ridernumber;i++)
  	{ 
  		printf("����%dλ�ã�%d��%d��ͣ����",i,allriders[i].x,allriders[i].y);//�����������λ�� 
		if(allriders[i].stop==0)//�����ͣ�� 
		{
			printf("��\n");
		}
		else if(allriders[i].stop==1)//���ͣ���ڲ͹� 
		{
			printf("�͹� %d %d��\n",allriders[i].finaltask->cx,allriders[i].finaltask->cy);
			allriders[i].finaltask=NULL;
			allriders[i].stop=0;//��Ϊ��ͣ����״̬ 
		}
		else if(allriders[i].stop==2)//���ͣ����ʳ�� 
		{
			printf("ʳ�� %d %d��\n",allriders[i].finaltask->sx,allriders[i].finaltask->sy);
			allriders[i].finaltask=NULL;
			allriders[i].stop=0;//��Ϊ��ͣ����״̬ 
		}
	} 
}   
