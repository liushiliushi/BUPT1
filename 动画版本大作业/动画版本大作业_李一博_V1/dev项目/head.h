#ifndef AB
#define AB
struct order{
	int num;//���
	int time;//���������ʱ��
	int cx;
	int cy;//�͹ݺ������� 
	int sx;
	int sy;//ʳ�ͺ������� 
	int current;//�õ�״̬  δ�ɵ�0/��ȡ��1/���Ͳ�2/�����3/��ʱ���4 
	int rider;//���͸õ���������� 
	int overtime;//δ��ʱ0/��ʱ1 
	struct order * orderptr;//������洢ʱ��һ��������λ�� 
};
typedef struct order LISTNODE;
typedef LISTNODE * LISTNODEPTR;

//input.c�����ڴ洢������Ϣ�Ľṹ��

struct rider{
	int state;//���ֵ�״̬������0/ȡ��1/�Ͳ�2
	int stop;//����ͣ��״̬��·��0/�͹�1/ʳ��2 
	int fadan;//����һ�̷�������¼���ֵķ������ 
	int x;
	int y;//���ֵ�����
	int change;//���ֵĶ����Ƿ���Ҫ��������0Ϊ��Ҫ��1Ϊ����Ҫ
	int accept,over,finish,currentnumber;//�����ֵĽӵ�������ʱ�������������ǰ��������
	int x1,y1,x2,y2,same;//�������������� ,�Ƿ��������������ͬ�����Ƿ��ǿ��������֣�����0/��1  
	struct order *temporarytask[50];//���ֵĶ������� 
	struct order *finaltask;//�������� 
};

#endif
