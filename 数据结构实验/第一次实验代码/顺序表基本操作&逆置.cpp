#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define List_Init_Size 100  //线性表存储空间的初始分配量
#define List_Increment 10   //线性表存储空间的分配增量
#define Status int
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW 0
#define ERROR 0
typedef int ElemType;   //元素类型
typedef struct {
	ElemType* elem;   //存储空间基址
	int length;       //当前长度
	int listsize;     //当前分配的存储容量（以sizeof(ElemType)为单位）
}SqList;

void visit(ElemType e)
{
	printf("%d ", e);
}
Status InitList_Sq(SqList &L)
{//构造一个空的线性表L
	L.elem = (ElemType*)malloc(List_Init_Size * sizeof(SqList));
	if (!L.elem) exit(OVERFLOW);  //存储空间分配失败
	L.length = 0;
	L.listsize = List_Init_Size; //初始分配容量
	return OK;
}
void DestroyList(SqList &L)
{
	free(L.elem);
}
void ClearList(SqList &L)
{
	memset(L.elem, 0, sizeof(ElemType)*L.length); 
	L.length = 0;
	
}
Status ListEmpty(SqList &L)
{
	if (L.length > 0)
		return FALSE;
	else
		return TRUE;
}
Status ListLength(SqList L)
{
	return L.length;
}
Status GetElem(SqList L,int i,ElemType &e)
{
	if (i > ListLength(L) || i < 1)
		return ERROR;
	else
	{
		e = L.elem[i-1];
		return OK;
	}
}
Status LocateElem(SqList L, ElemType e)
{
	int i, temp = FALSE;
	for (i = 1; i <= ListLength(L); i++)
	{
		if (L.elem[i - 1] == e)
		{
			temp = i;
			return temp;
		}
	}
	return FALSE;
}
Status PriorElem(SqList L, ElemType cur_e, ElemType &pre_e)
{
	int i;
	if (L.elem[0] == cur_e)
		{
			printf("当前元素为首位，无前驱\n");
			return ERROR;
		}
	for (i = 2; i <= ListLength(L); i++)
	{
		if (L.elem[i - 1] == cur_e)
		{
			pre_e = L.elem[i - 2];
			return OK;
		}
	}
	printf("不存在当前元素\n");
	return FALSE;
}
Status NextElem(SqList L, ElemType cur_e, ElemType& next_e)
{
	int i;
	if (L.elem[ListLength(L) - 1] == cur_e)
	{
		printf("当前元素为末位，无后继\n");
			return ERROR;
	}
	for (i = 1; i < ListLength(L); i++)
	{
		if (L.elem[i - 1] == cur_e)
		{
			next_e = L.elem[i];
			return OK;
		}
	}
	printf("不存在当前元素\n");
	return ERROR;
}
Status ListInsert_Sq(SqList& L, int i, ElemType e)  
{
	ElemType* newbase, * q, * p;
	if (i<1 || i>ListLength(L)+1)
	{
		printf("i值不合法\n");
		return FALSE;
	}
	if (L.length > L.listsize)
	{
		printf("当前分配存储空间不足，增加空间\n");
		newbase = (ElemType*)realloc(L.elem, (L.listsize + List_Increment) * sizeof(ElemType));
		if (!newbase) 
			exit(OVERFLOW); //存储分配失败
		L.elem = newbase;  //新基址
		L.listsize = L.listsize + List_Increment;  //增加存储容量
	}
	q = &L.elem[i - 1];
	for (p = &(L.elem[L.length - 1]); p >= q; --p) * (p + 1) = *p;
	*q = e;
	++L.length;
	return OK;
}
Status ListDelete_Sq(SqList& L, int i, ElemType &e)         
{
	ElemType* p,*q;
	if ((i < 1) || (i > L.length))
	{
		printf("i值不合法\n");
		return FALSE;
	}
	p = &L.elem[i - 1];
	e = *p;
	for (q = p; q < &L.elem[L.length - 1]; ++q)
	{
		*q = *(q + 1);
	}
	L.length--;
	return OK;
}
Status ListTraverse(SqList L)    //实现顺序表元素的遍历
{
	int i = 1;
	for (i; i <= L.length; i++)
	{
		visit(L.elem[i - 1]);
	}
	printf("\n");
	return OK;
}
Status ListInverse(SqList L)    //实现顺序表元素就地逆置
{
	int i=0,n = L.length-1;
	ElemType temp;
	while (i < n)
	{
		temp = L.elem[i];
		L.elem[i] = L.elem[n];
		L.elem[n] = temp;
		++i;
		--n;
	}
	return OK;
}
Status ListInsertSort(SqList& L)   //插入排序  升序
{
	int n,i;
	n = ListLength(L);
	for (i = 1; i < n; i++)
	{
		if (L.elem[i] < L.elem[i - 1])  //第i个元素比第i-1个大的话，无需插入
		{
			int j = i - 1;
			int value = L.elem[i];
			while (j > -1 && value < L.elem[j])   //从i-1开始遍历寻找插入位置
			{
				L.elem[j + 1] = L.elem[j];
				j--;
			}
			L.elem[j + 1] = value; //找到要插入的位置之后插入
		}
	}
	return OK;
}
Status List_Intersection_Set(SqList& La, SqList& Lb, SqList& Lc)
{    //求表的交集,生成表C
	int i,t,j=0;
	ElemType e;
	for (i = 0; i < La.length; i++)
	{
		t = 0;
		while (j < Lb.length)  //t记录表A中元素是否在B中
		{
			if (La.elem[i] == Lb.elem[j])
			{
				t = 1;
				j++;
				break;
			}
			else if (La.elem[i] >= Lb.elem[j])
			{
				j++;
			}
			else
				break;
		}
		if (t == 0)  //说明此元素不在在表A、B交集中
		{
			ListDelete_Sq(La, i+1, e);
			i--;
		}
	}
	Lc = La;

	if (Lc.length != 0)
	{
		ListInsertSort(Lc);
		for (i = 0; i < Lc.length-1; i++)  //删除表中重复的元素
		{
			if (Lc.elem[i] == Lc.elem[i + 1])
			{
				ListDelete_Sq(Lc, i + 1, e);
				i--;
			}
		}
		printf("表A、B的交集C为：");
		ListTraverse(Lc);
		return OK;
	}
	else
	{
		printf("表A、B的交集C为空集：");
		return FALSE;
	}
}
Status Listunion_Sq(SqList& La, SqList& Lb, SqList& Lc)
{  //求表的并集，在A的空间上
	int i, j=0;
	int n = ListLength(Lb);
	ElemType e;
	for (i = 0; i < n; i++)
	{
		e = Lb.elem[i];    //拿出b中元素
		while (j < La.length)
		{
			if (e < La.elem[j])    //说明此元素不在表A中
			{
				ListInsert_Sq(La, j + 1, e);
				j++;
				break;
			}
			else if (e == La.elem[j])
			{
				j++;
				break;
			}
			else
			{
				j++;
			}
		}
		if (j >= La.length)    //A已遍历结束，剩余元素全部插入
		{
			ListInsert_Sq(La, j + 1, e);
			j++;
		}
	}
	Lc = La;
	for (i = 0; i < Lc.length - 1; i++)  //删除表中重复的元素
	{
		if (Lc.elem[i] == Lc.elem[i + 1])
		{
			ListDelete_Sq(Lc, i + 1, e);
			i--;
		}
	}
	printf("表A、B的并集C为：");
	ListTraverse(Lc);

	return OK;
}
int main()
{
	SqList L,La,Lb,Lc;
	int n,k,i;
	char ch;
	ElemType e;
	InitList_Sq(La);
	printf("请输入表A数据个数:");
	scanf_s("%d",&n);
	printf("请依次输入每个数据，以空格隔开:");
	for (i = 1; i <= n; i++)
	{
		scanf_s("%d",&e);
		ListInsert_Sq(La, i, e);
	}
	InitList_Sq(Lb);
	printf("请输入表B数据个数:");
	scanf_s("%d", &k);
	printf("请依次输入每个数据，以空格隔开:");
	for (i = 1; i <= k; i++)
	{
		scanf_s("%d", &e);
		ListInsert_Sq(Lb, i, e);
	}
	if (ListEmpty(La))
	{
		printf("表A为空表，已退出");
		return ERROR;
	}
	if (ListEmpty(Lb))
	{
		printf("表B为空表，已退出");
		return ERROR;
	}
	ListInsertSort(La);
	printf("排序后的表A为：");
	ListTraverse(La);
	ListInsertSort(Lb);
	printf("排序后的表B为：");
	ListTraverse(Lb);
	Listunion_Sq(La, Lb, Lc);
	//List_Intersection_Set(La, Lb, Lc);

	//ListInsertSort(L);   // 排序函数，升序排列
	//ListTraverse(L);
	
	//调用逆置函数
	/*ListInverse(L);
	printf("逆置后的线性表为：");
	ListTraverse(L);*/

	/*ch = getchar(); //读走缓冲区的\n
	printf("是否需要删除数据元素（是y 否n）");
	if (getchar() == 'y')
	{
		printf("请输入要删除元素的位序：");
		scanf_s("%d",&i);
		ListDelete_Sq(La, i, e);
		printf("被删除的元素为：");
		printf("%d\n", (int)e);
		ListTraverse(La);
	}

	printf("是否需要插入数据元素（是y 否n）");
	ch = getchar();
	if (getchar() == 'y')
	{
		printf("请输入要插入的元素：");
		scanf_s("%d", &e);
		printf("请输入要插入元素的位序：");
		scanf_s("%d", &i);
		ListInsert_Sq(L, i, e);
		ListTraverse(L);
	}*/
	return OK;
}