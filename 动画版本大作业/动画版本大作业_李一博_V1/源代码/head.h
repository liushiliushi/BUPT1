#ifndef AB
#define AB
struct order{
	int num;//编号
	int time;//订单发起的时间
	int cx;
	int cy;//餐馆横纵坐标 
	int sx;
	int sy;//食客横纵坐标 
	int current;//该单状态  未派单0/待取餐1/待送餐2/已完成3/超时完成4 
	int rider;//配送该单的骑手序号 
	int overtime;//未超时0/超时1 
	struct order * orderptr;//用链表存储时下一个订单的位置 
};
typedef struct order LISTNODE;
typedef LISTNODE * LISTNODEPTR;

//input.c中用于存储订单信息的结构体

struct rider{
	int state;//骑手的状态，空闲0/取餐1/送餐2
	int stop;//骑手停靠状态，路上0/餐馆1/食客2 
	int fadan;//若这一刻罚单，记录骑手的罚单编号 
	int x;
	int y;//骑手的坐标
	int change;//骑手的订单是否需要重新排序，0为需要，1为不需要
	int accept,over,finish,currentnumber;//该骑手的接单数，超时数，完成数，当前订单数；
	int x1,y1,x2,y2,same;//该骑手派送区域 ,是否和其他骑手有相同区域即是否是跨区域骑手，不是0/是1  
	struct order *temporarytask[50];//骑手的订单序列 
	struct order *finaltask;//最终序列 
};

#endif
