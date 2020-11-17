#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define TRUE 1
#define ERROR 0
#define FALSE 0
#define OVERFLOW 0

typedef int Status;
typedef int QElemType;
typedef struct QNode
{
	QElemType data;
	struct QNode* next;
}QNode,*QueuePtr;
typedef struct
{
	QueuePtr front;   //队头指针
	QueuePtr rear;    //队尾指针
}LinkQueue;

Status visit(QueuePtr p)
{
	if (p)
	{
		printf("%d ", p->data);
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
Status DestoryQueue(LinkQueue& Q)
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
	while(Q.rear)
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
			visit(p);
			p = p->next;
		}
		printf("\n");
		return OK;
	}
}

Status main()
{
	LinkQueue Q;
	QElemType e;
	int n,i;
	InitQueue(Q);
	printf("请输入队列初始元素个数：");
	scanf_s("%d", &n);
	printf("请依次输入各个元素的值，空格隔开：");
	for (i = 0; i < n; i++)
	{
		scanf_s("%d", &e);
		EnQueue(Q, e);
	}
	QueueTraverse(Q);
	ClearQueue(Q);
	DeQueue(Q, e);
	//printf("%d", QueueLength(Q));
	return OK;
}