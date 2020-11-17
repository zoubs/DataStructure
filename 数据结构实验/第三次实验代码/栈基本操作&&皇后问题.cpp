// ADT Stack 基本操作9个，用顺序存储结构实现
//利用栈操作实现八皇后问题求解
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
using namespace std;
#define Stack_Init_Size  200
#define STACKINCREMENT   40
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW 0
#define N 4
typedef int Status;
typedef int SElemType;
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
	printf("栈初始化成功\n");
	return OK;
}
Status DestroyStack(SqStack& S)
{
	free(S.base);
	printf("栈已销毁");
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
	if (S.top -S.base >= S.stacksize)
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
	e = *(S.top-1);
	S.top--;
	return OK;
}
void visit(SElemType* p)
{
	if (p)
	{
		printf("%d ", *p);
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
		visit(p);
	}
	printf("\n");
	return OK;
}
Status place(SqStack S)
{//用来判断皇后位置是否合法
	int i, j;
	SElemType* p, * q;
	SElemType e;
	j = S.top - S.base - 1;      //栈顶皇后所在行数
	GetTop(S, e);   //获得栈顶元素
	for (p = S.base; p < S.top - 1; p++)
	{
		i = p - S.base;
		if (e == *p)
		{  //说明存在皇后在同一列
			return FALSE;
		}
		else if (((e - *p) == (j - i)) || ((e - *p) == (i - j)))
		{   //说明出现皇后位于对角线不合法情况
			return FALSE;
		}
	}
	return TRUE;
}
void NQeens(SqStack S)
{  //求解N皇后问题，非递归
	ClearStack(S);    //清空栈
	SElemType e = 1;
	SElemType a[N];
	for (int i = 0; i < N; i++)
	{
		a[i] = 1;
	}
	int  n = 0, count = 0;    //n代表0-7行
	while (a[0] < N+1)
	{
		Push(S, a[n]);       // n为当前操作的行数
		if (place(S))
		{   // 说明皇后位置合法
			n++;        // 下次压入下一行
		}
		else
		{   // 说明皇后位置不合法
			Pop(S, a[n]);
			a[n]++;
			while(a[n] > N && n > 0)
			{    //第n行的8个位置已全部放过皇后，需改变上一行皇后位置
				a[n] = 1;
				n--;
				Pop(S, a[n]);
				a[n]++;
			}
		}
		if (n == N)
		{   //八个皇后已全部摆好
			count++;
			StackTraverse(S);
			n--;   //回到最后一行
			Pop(S, a[n]);
			a[n]++;
			while (a[n] > N && n > 0)
			{    //第n行的N个位置已全部放过皇后，需改变上一行皇后位置
				a[n] = 1;
				n--;
				Pop(S, a[n]);
				a[n]++;
			}
		}
	}
	printf("%d皇后问题解共有 %d 种\n", N, count);
}
Status main()
{
	SqStack S;
	int n, i;
	SElemType e,t;
	InitStack(S);
	NQeens(S);    // 调用N皇后问题求解函数

	printf("请输入栈初始元素个数：");
	scanf_s("%d", &n);
	printf("请依次输入各个元素，空格隔开：");
	for (i = 0; i < n; i++)
	{
		scanf_s("%d", &e);
		Push(S, e);
	}
	//ClearStack(S);
	//Pop(S, e);
	StackTraverse(S);

	//printf("请输入想要压栈的元素：");
	//scanf_s("%d", &e);
	//Push(S, e);
	//StackTraverse(S);
	//Pop(S, t);
	//printf("弹栈元素为：%d\n", t);
	//StackTraverse(S);
	//printf("%d",StackLength(S));
	//DestroyStack(S);
	return OK;
}