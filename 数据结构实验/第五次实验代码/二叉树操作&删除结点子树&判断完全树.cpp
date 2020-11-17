#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW 0
#define Stack_Init_Size  200
#define STACKINCREMENT   40
typedef int Status;
typedef char BiElemType;
typedef struct BNode
{
	BiElemType value;
	struct BNode* lchild, * rchild;    //左右孩子指针
}BiTNode, * BiTree;
typedef BiTree SElemType;
typedef BiTree QElemType;
typedef struct
{
	SElemType* base;   // 栈底指针
	SElemType* top;    // 栈顶指针
	int stacksize;    //当前已分配的存储空间，以SElemType为单位
}SqStack;
Status InitStack(SqStack& S)  //构造一个空栈
{
	S.base = (SElemType*)malloc(Stack_Init_Size * sizeof(SqStack));
	if (!S.base)
	{
		printf("存储空间分配失败");
		exit(OVERFLOW);
	}
	S.top = S.base;
	S.stacksize = Stack_Init_Size;
	return OK;
}
Status DestroyStack(SqStack& S)
{
	free(S.base);
	return OK;
}
Status ClearStack(SqStack& S)
{
	S.top = S.base;
	return OK;
}
Status StackEmpty(SqStack S)
{
	if (S.base == S.top)
		return TRUE;
	else
		return FALSE;
}
Status StackLength(SqStack S)
{
	int length;
	length = S.top - S.base;
	return length;
}
Status GetTop(SqStack S, SElemType& e)  //若栈不空用e返回栈顶元素
{
	if (S.base == S.top)
	{
		printf("该栈为空");
		return ERROR;
	}
	else
	{
		e = *(S.top - 1);
		return OK;
	}
}
Status Push(SqStack& S, SElemType e)    //插入e为新的栈顶元素
{
	SElemType* newbase;
	if (S.top - S.base >= S.stacksize)
	{
		printf("存储空间不足，请增加分配");
		newbase = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!newbase)
		{
			printf("存储分配失败");
			exit(OVERFLOW);
		}
		S.base = newbase;
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top = e;
	S.top++;
	return OK;
}
Status Pop(SqStack& S, SElemType& e)
{
	if (S.top == S.base)
	{
		printf("该栈为空");
		return ERROR;
	}
	e = *(S.top - 1);
	S.top--;
	return OK;
}
void Svisit(SElemType* p)
{
	if (p)
	{
		printf("%c ", (*p)->value);
	}
	else
	{
		printf("访问失败");
	}
}
Status StackTraverse(SqStack S)
{
	SElemType* p;
	for (p = S.base; p < S.top; p++)
	{
		Svisit(p);
	}
	printf("\n");
	return OK;
}
typedef struct QNode
{
	QElemType data;
	struct QNode* next;
}QNode, * QueuePtr;
typedef struct
{
	QueuePtr front;   //队头指针
	QueuePtr rear;    //队尾指针
}LinkQueue;

Status Qvisit(QueuePtr p)
{
	if (p)
	{
		printf("%c ", (p->data)->value);
	}
	return OK;
}
Status InitQueue(LinkQueue& Q)
{ // 构造一个空队列Q
	Q.front = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
	{
		printf("空间分配失败");
		exit(OVERFLOW);
	}
	Q.rear = Q.front;
	Q.front->next = NULL;
	return OK;
}
Status DestroyQueue(LinkQueue& Q)
{
	while (Q.front)
	{
		Q.rear = Q.front;
		Q.front = Q.front->next;
		free(Q.rear);
	}
	return OK;
}
Status ClearQueue(LinkQueue& Q)
{
	QueuePtr temp;
	Q.rear = Q.front->next;
	Q.front->next = NULL;
	while (Q.rear)
	{
		temp = Q.rear;
		Q.rear = Q.rear->next;
		free(temp);
	}
	Q.rear = Q.front;
	return OK;
}
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)  //队列为空
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
int QueueLength(LinkQueue Q)
{
	int i = 0;
	QueuePtr p = Q.front;
	while (p != Q.rear)
	{
		i++;
		p = p->next;
	}
	return i;
}
Status GetHead(LinkQueue Q, QElemType& e)
{ //用e返回Q的队头元素
	if (Q.front == Q.rear)
	{
		printf("该队列为空");
		return ERROR;
	}
	else
	{
		e = Q.front->data;
		return OK;
	}
}
Status EnQueue(LinkQueue& Q, QElemType e)
{ //插入元素e为Q的新队尾元素
	QueuePtr s;
	s = (QueuePtr)malloc(sizeof(QNode));
	if (!s)  //空间分配失败
	{
		printf("空间分配失败");
		exit(OVERFLOW);
	}
	s->next = NULL;
	s->data = e;
	Q.rear->next = s;
	Q.rear = s;
	return OK;
}
Status DeQueue(LinkQueue& Q, QElemType& e)
{
	QueuePtr p;
	if (Q.front == Q.rear)
	{
		printf("该队列为空");
		return ERROR;
	}
	p = Q.front;
	Q.front = Q.front->next;
	e = Q.front->data;
	free(p);
	return OK;
}
Status QueueTraverse(LinkQueue Q)
{
	if (!Q.front || !Q.rear)
	{
		printf("该队列不存在");
		return ERROR;
	}
	QueuePtr p;
	if (Q.front == Q.rear)
	{
		printf("该队列为空");
		return ERROR;
	}
	else
	{
		p = Q.front->next;
		while (p)
		{
			Qvisit(p);
			p = p->next;
		}
		printf("\n");
		return OK;
	}
}

Status Bivisit(BiTree T)
{
	if (T)
	{
		printf("%c ", T->value);
	}
	return OK;
}
Status InitTree(BiTree& T)
{   //构造空树
	T = NULL;
	return OK;
}
Status DestroyBiTree(BiTree& T)
{
	if (T)
	{
		DestroyBiTree(T->lchild);
		DestroyBiTree(T->rchild);
		free(T);
	}
	return OK;
}
Status CreatBiTree(BiTree& T)
{    //先序遍历创建二叉树
	BiElemType ch;
	//BiTree head;        //head保留init函数里生成的头节点
	BiTree s;
	ch = getchar();
	if (ch == '\0')
	{     //忽略
		return OK;
	}
	if (ch == ' ')
	{  //空树
		T = NULL;
		return OK;
	}
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		if (!T)
		{
			printf("存储空间分配失败：");
			exit(OVERFLOW);
		}
		else
		{
			T->value = ch;                   //生成根节点
			CreatBiTree(T->lchild);         //构造左子树
			CreatBiTree(T->rchild);         //构造右子树
		}
		return OK;
	}
}
Status BiTreeEmpty(BiTree T)
{
	if (!T)
	{
		printf("该树为空");
		return TRUE;
	}
	else
	{
		printf("该树非空");
		return FALSE;
	}
}
Status PreOrderTraverse(BiTree T)
{  //非递归先序遍历
	SqStack S;
	InitStack(S);
	BiTree p;
	if (T == NULL)
	{
		printf("该树为空");
		return ERROR;
	}
	p = T;
	printf("先序遍历的结果为：");
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			Push(S, p);
			Bivisit(p);
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			p = p->rchild;
		}
	}
	printf("\n");
	DestroyStack(S);
	return OK;
}
Status InOrderTraverse(BiTree T)
{ //非递归中序遍历
	SqStack S;
	InitStack(S);
	BiTree p;
	if (T == NULL)
	{
		printf("该树为空");
		return ERROR;
	}
	p = T;
	printf("中序遍历的结果为：");
	while (p != NULL || !StackEmpty(S))
	{
		if (p)
		{   //遍历左子树
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			Bivisit(p);
			p = p->rchild;
		}
	}
	DestroyStack(S);
	printf("\n");
	return OK;
}
Status PostOrderTraverse(BiTree T)
{  //非递归后序遍历
	//方法1，不用加标记
	SqStack S,D;
	InitStack(S); 
	InitStack(D);
	BiTree p;
	if (T == NULL)
	{
		printf("该树为空");
		return ERROR;
	}
	p = T;
	printf("后序遍历的结果为：");
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			Push(S, p);
			Push(D, p);
			p = p->rchild;
		}
		else
		{
			Pop(S, p);
			p = p->lchild;
		}
	}
	while (!StackEmpty(D))
	{
		Pop(D, p);
		printf("%c ", p->value);
	}
	printf("\n");
	return OK;
}
Status LevelOrderTraverse(BiTree T)
{//非递归层序遍历
	LinkQueue Q;
	BiTree p;
	InitQueue(Q);
	if (T == NULL)
	{
		printf("该树为空");
		return ERROR;
	}
	p = T;
	printf("层序遍历的结果为：");
	EnQueue(Q, p);   //根节点入队
	while (!QueueEmpty(Q))
	{    
		DeQueue(Q, p);
		printf("%c ", p->value);
		if (p->lchild)
		{
			EnQueue(Q, p->lchild);        //左儿子不为空，左儿子进队
		}
		if (p->rchild)
		{
			EnQueue(Q, p->rchild);          //右儿子不为空，右儿子进队
		}
	}
	printf("\n");
	return OK;
}
Status BiTreeDepth(BiTree T)
{//非递归求树的深度,利用层序遍历
	
	if (T == NULL)
	{
		return 0;
	}
	BiTree p;
	int depth = 0;
	int len = 0;          //用来记录每层节点数
	LinkQueue Q;
	InitQueue(Q);
	p = T;
	EnQueue(Q, p);
	while (!QueueEmpty(Q))
	{
		depth++;
		len = QueueLength(Q);
		while (len--)
		{
			DeQueue(Q, p);
			if (p->lchild)
			{
				EnQueue(Q, p->lchild);
			}
			if (p->rchild)
			{
				EnQueue(Q, p->rchild);
			}
		}
	}
	return depth;
}
Status ClearBiTree(BiTree& T)
{
	if (T == NULL)
	{
		return OK;
	}
	ClearBiTree(T->lchild);
	ClearBiTree(T->rchild);
	free(T);
	return OK;
}
Status Root(BiTree T)
{
	if (T)
	{
		printf("二叉树的根为：%c\n",T->value);
		return T->value;
	}
	else
	{
		printf("该树为空树：");
		return OK;
	}
}
Status Value(BiTree T, BiTree e)
{
	printf("结点的值为：%d\n", e->value);
	return e->value;
}
Status Assign(BiTree& T, BiTree& e, BiElemType value)
{
	e->value = value;
	return OK;
}
BiTree Parent(BiTree T, BiElemType e)
{
	if (e == T->value)
	{
		printf("该结点为树根，无双亲\n");
		return NULL;
	}
	else
	{
		BiTree p;
		p = T;
		SqStack S;
		InitStack(S);
		while (!StackEmpty(S) || p)
		{
			if (p)
			{
				if ((p->lchild != NULL) && (p->lchild->value == e))
				{
					printf("结点的双亲结点为：%c\n", p->value);
					return p;
				}
				else if ((p->rchild != NULL) && (p->rchild->value == e))
				{
					printf("结点的双亲结点为：%c\n", p->value);
					return p;
				}
				Push(S, p);
				p = p->lchild;
			}
			else
			{
				Pop(S, p);
				p = p->rchild;
			}
		}
	}
	printf("该结点不是树中结点\n");
	return NULL;
}
BiTree LeftChild(BiTree T, BiElemType e)
{
	SqStack S;
	BiTree p;
	if (T == NULL)
	{
		printf("树为空\n");
		return NULL;
	}
	else
	{
		InitStack(S);
		p = T;
		while (!StackEmpty(S) || p)
		{
			if (p)
			{
				if (p->value == e)
				{//代表找到该结点
					if (p->lchild)
					{
						printf("结点%c的左孩子为%c\n", e, p->lchild->value);
						return p->lchild;
					}
					else
					{
						printf("结点%c无左孩子", e);
						return NULL;
					}
				}
				Push(S, p);
				p = p->lchild;
			}
			else
			{
				Pop(S, p);
				p->rchild;
			}
		}
	}
	printf("结点%c不在树中\n", e);
}
BiTree RightChild(BiTree T, BiElemType e)
{
	SqStack S;
	BiTree p;
	if (T == NULL)
	{
		printf("树为空\n");
		return NULL;
	}
	else
	{
		InitStack(S);
		p = T;
		while (!StackEmpty(S) || p)
		{
			if (p)
			{
				if (p->value == e)
				{//代表找到该结点
					if (p->rchild)
					{
						printf("结点%c的右孩子为%c\n", e, p->rchild->value);
						return p->rchild;
					}
					else
					{
						printf("结点%c无右孩子", e);
						return NULL;
					}
				}
				Push(S, p);
				p = p->lchild;
			}
			else
			{
				Pop(S, p);
				p->rchild;
			}
		}
	}
	printf("结点%c不在树中\n", e);
}
BiTree LeftSibling(BiTree T, BiElemType e)
{
	SqStack S;
	BiTree p;
	p = T;
	if (T == NULL)
	{
		printf("该树为空树，该结点无左兄弟\n");
		return NULL;
	}
	else if(T->value == e)
	{
		printf("该结点为树根，无兄弟\n");
		return NULL;
	}
	InitStack(S);
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			if ((p->rchild != NULL) && (e == p->rchild->value))
			{//结点e为树T右孩子，判断其是否有左兄弟
				if (p->lchild)
				{
					printf("该结点的左兄弟为：%c\n", p->lchild->value);
					DestroyStack(S);
					return p->lchild;
				}
				else
				{
					printf("该结点无右兄弟\n");
					DestroyStack(S);
					return NULL;
				}
			}
			if ((p->lchild != NULL) && e == p->lchild->value)
			{//结点为树T左孩子
				printf("该结点为树T的左孩子，无左兄弟\n");
				DestroyStack(S);
				return NULL;
			}
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			p = p->rchild;
		}
	}
	printf("结点%c不在树中\n", e);
	DestroyStack(S);
	return NULL;
}
BiTree RightSibling(BiTree T, BiElemType e)
{
	SqStack S;
	InitStack(S);
	if (T == NULL)
	{
		printf("该树为空,无右兄弟\n");
		return NULL;
	}
	else if (T->value == e)
	{
		printf("该结点为树根，无右兄弟\n");
		return NULL;
	}
	BiTree p;
	p = T;
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			if ((p->lchild !=NULL) && (p->lchild->value == e))
			{//e为T的左孩子,再判断其是否有右兄弟
				if (p->rchild)
				{
					printf("该结点的右兄弟为：%c\n", p->rchild->value);
					return p->rchild;
				}
				else
				{
					printf("该结点无右兄弟\n");
					return NULL;
				}
			}
			else if ((p->rchild != NULL) && (p->rchild->value == e))
			{
				printf("该结点为树T的右孩子，无右兄弟\n");
				return NULL;
			}
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			p = p->rchild;
		}
	}
	printf("结点%c不在树中\n", e);
	return NULL;
}
Status InsertChild(BiTree &T, BiTree e, int LR, BiTree c)
{
	if (LR != 0 && LR != 1)
	{
		printf("LR格式错误，只能插入为结点的左子树或者右子树\n");
		return ERROR;
	}
	BiTree temp;
	if (T == NULL)
	{
		printf("树T为空树，无法插入\n");
		return FALSE;
	}
	if (c == NULL)
	{
		printf("待插入的树为空，无需插入\n");
		return FALSE;
	}
	if (LR == 1)
	{//插入右子树
		temp = e->rchild;
		e->rchild = c;
		c->rchild = temp;
		printf("插入右子树成功\n");
		return OK;
	}
	else if(LR == 0)
	{//插入左子树
		temp = e->lchild;
		e->lchild = c;
		c->rchild = temp;
		printf("插入左子树成功\n");
		return OK;
	}
}
Status DeleteChild(BiTree& T, BiTree e, int LR)
{
	if (LR != 0 && LR != 1)
	{
		printf("LR格式错误，只能删除结点的左子树或者右子树\n");
		return ERROR;
	}
	if (T == NULL)
	{
		printf("树T为空树，无法删除\n");
		return FALSE;
	}
	
	if (LR == 1)
	{//删除右子树
		DestroyBiTree(e->rchild);
		e->rchild = NULL;   //避免野指针
		printf("删除右子树成功\n");
		return OK;
	}
	else if (LR == 0)
	{//删除左子树
		DestroyBiTree(e->lchild);
		e->lchild = NULL;
		printf("删除左子树成功\n");
		return OK;
	}
}
Status Delete_x_Child(BiTree& T, BiElemType e)
{
	SqStack S;
	BiTree p;
	if (T == NULL)
	{
		printf("该树为空树，无法删除孩子\n");
		return FALSE;
	}
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			if (p->value == e)
			{  //找到结点e删除其子树
				DestroyBiTree(p->lchild);
				DestroyBiTree(p->rchild);
				p->rchild = NULL;
				p->lchild = NULL;
				printf("结点%c的子树已删除\n",p->value);
				DestroyStack(S);
				return OK;
			}
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			p = p->rchild;
		}
	}
	printf("结点%c不在该树中\n", e);
	return OK;
}
//*************************************
//遍历递归实现
Status Recur_PreOrderTraverse(BiTree T)
{//先序遍历
	if (T)
	{
		printf("%c ", T->value);
		Recur_PreOrderTraverse(T->lchild);
		Recur_PreOrderTraverse(T->rchild);
	}
	return OK;
}
Status Recur_InOrderTraverse(BiTree T)
{
	if (T)
	{
		Recur_InOrderTraverse(T->lchild);
		printf("%c ", T->value);
		Recur_InOrderTraverse(T->rchild);
	}
	return OK;
}
Status Recur_PostOrderTraverse(BiTree T)
{
	if (T)
	{
		Recur_PostOrderTraverse(T->lchild);
		Recur_PostOrderTraverse(T->rchild);
		printf("%c ", T->value);
	}
	return OK;
}
//*************************************
Status CompleteBiTree(BiTree T)
{
	int d;   //左子树深度-右子树深度
	if (T)
	{
		d = BiTreeDepth(T->lchild);
		if (d < 0 || d > 1)
		{
			return ERROR;
		}
		else
		{
			if (CompleteBiTree(T->lchild) && CompleteBiTree(T->rchild))
			{
				return OK;
			}
			else
			{
				return ERROR;
			}
		}
	}
	return FALSE;
}

int main()
{
	BiTree T,C;
	char ch;
	int Depth;
	InitTree(T);
	InitTree(C);
	printf("请输入树T（先序创建）:");
	CreatBiTree(T);
	ch = getchar();    //读走缓冲区的\n
	//ABC  DE G  F  H  
	   
	PreOrderTraverse(T);
	InOrderTraverse(T);
	PostOrderTraverse(T);
	LevelOrderTraverse(T);
	/*Depth = BiTreeDepth(T);
	printf("树的深度为：%d\n", Depth);
	if (CompleteBiTree(T))
	{
		printf("该树是完全二叉树\n");
	}
	else
	{
		printf("该树不是完全二叉树\n");
	}
	printf("输入要找双亲的结点值：");
	scanf_s("%c", &ch,1);
	Parent(T, ch);
	ch = getchar();   //读缓冲区\n
	printf("输入要找右兄弟的结点值：");
	scanf_s("%c", &ch, 1);
	RightSibling(T,ch);
	ch = getchar();   //读缓冲区\n
	printf("请输入待插入树C:");
	CreatBiTree(C);
	ch = getchar();   //读缓冲区\n
	//ST   
	InsertChild(T, T->lchild, 1,C);
	printf("先序遍历的结果为：");
	Recur_PreOrderTraverse(T);
	printf("\n中序遍历的结果为：");
	Recur_InOrderTraverse(T);
	printf("\n后序遍历的结果为：");
	Recur_PostOrderTraverse(T);
	printf("\n");
	LevelOrderTraverse(T);
	DeleteChild(T, T->lchild, 1);
	LevelOrderTraverse(T);*/
	printf("请输入要删除其子树的结点：");
	scanf_s("%c", &ch, 1);
	Delete_x_Child(T, ch);
	ch = getchar();   //读缓冲区\n
	PreOrderTraverse(T);
	InOrderTraverse(T);
	PostOrderTraverse(T);
	LevelOrderTraverse(T);
	return 0;
}