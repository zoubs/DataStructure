#include<iostream>
using namespace std;

#define MAX 20
typedef char TElemType;
typedef struct CSNode
{
	TElemType value;
	struct CSNode* firstchild, * nextsibling;
}CSNode,*CSTree;
int CreatCSTree(CSTree& T)
{
	char ch;
	ch = getchar();
	if (ch == '\0' || ch == '\n') 
	{
		return 0;   //忽略 
	}
	if (ch == ' ')
	{
		T = NULL;
		return 0;
	}
	else
	{
		T = (CSTree)malloc(sizeof(CSNode));
		if (!T)
		{
			cout << "空间分配失败";
			exit(0);
		}
		T->value = ch;
		CreatCSTree(T->firstchild);
		CreatCSTree(T->nextsibling);
		return 0;
	}
}
int Depth(CSTree T)
{
	if (!T)
	{
		return 0;
	}
	else
	{
		return (Depth(T->firstchild) + 1) > (Depth(T->nextsibling)) ? (Depth(T->firstchild) + 1) : (Depth(T->nextsibling));
	}
}
int print_x_level(CSTree T,int i)
{
	if (i > Depth(T) || i < 1)
	{
		cout << "输入的层数不合法" << endl;
		return -1;
	}
	if (T == NULL)
	{
		cout << "该树为空" << endl;
		return -1;
	}
	CSTree Qu[MAX];   //定义队列
	int rear, front, level, len;
	CSTree q, p = T;
	rear = 0;
	front = 0;
	level = 0;
	Qu[rear++] = p;    //根节点入队
	len = (rear + MAX - front) % MAX;   //队列元素个数
	cout << "第" << i << "层的结点为：";
	while ((rear != front))
	{
		level++;    //层数
		len = (rear + MAX - front) % MAX;   //队列元素个数
		while (len--)
		{
			p = Qu[front];
			front = (front + 1) % MAX;    //出队
			if (i == level)   //第i层
			{
				cout << p->value << "   ";
			}
			if (p->firstchild)
			{
				Qu[rear] = p->firstchild;   //孩子入队
				rear = (rear + 1) % MAX;
				q = p->firstchild;
				while (q->nextsibling)
				{
					Qu[rear] = q->nextsibling;   
					rear = (rear + 1) % MAX;     //兄弟入队
					q = q->nextsibling;
				}
			}
		}
	}
	return 0;
}
int main()
{
	CSTree T;
	CreatCSTree(T);
	//int depth = Depth(T);
	//cout << depth;
	print_x_level(T, 3);
	//ABF G H  CD  E   
	//AB CD  E   
	return 0;
}