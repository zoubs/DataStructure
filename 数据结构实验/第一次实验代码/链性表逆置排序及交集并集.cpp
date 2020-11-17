#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stddef.h>
using namespace std;

#define Status int
#define OK 1
#define TRUE 1
#define ERROR 0
#define FALSE 0
#define OVERFLOW -1
typedef int ElemType;

typedef struct LNode
{
	ElemType data;
	struct LNode* next;
}LNode,*linklist;

Status InitList(linklist& L)
{
	L = (linklist)malloc(sizeof(LNode));
	if (!L)
		printf("空间分配失败");
	else
	{
		L->next = NULL;
		L->data = 0;
		printf("链表建立成功\n");
	}
	return OK;
}
Status DestoryList(linklist& L)
{
	linklist p,tmp;
	if (!L)
	{
		printf("该表不存在");
		return ERROR;
	}
	p = L->next;
	while (p)
	{
		tmp = p->next;
		free(p);
		p = tmp;
	}
	free(L);
	printf("链性表已销毁\n");
	return OK;
}
Status ClearList(linklist& L)
{
	linklist p,q;
	if (!L)  
	{
		printf("该表不存在");
		return ERROR;
	}
	p = L->next;
	q = p->next;
	L->next = NULL;
	while (p)
	{
		free(p);
		p = q;
		q = q->next;
	}
	free(p);
	printf("链性表已重置为空表");
	return OK;
}
Status ListEmpty(linklist L)
{
	if (!L)
	{
		printf("该表不存在");
		return ERROR;
	}
	if (NULL == L->next)
	{
		printf("链性表是空表\n");
		return TRUE;
	}
	else
	{
		printf("链性表不是空表\n");
		return FALSE;
	}
}
Status ListLength(linklist L)
{
	if (!L)
	{
		printf("该表不存在");
		return ERROR;
	}
	int length=0;
	linklist p;
	p = L->next;
	while (p)
	{
		length++;
		p = p->next;
	}
	return length;
}
Status GetElem(linklist L, int i, ElemType& e)
{
	if (!L)
	{
		printf("该表不存在");
		return ERROR;
	}
	linklist p;
	p = L;
	if (i > ListLength(L) || i < 1)
	{
		printf("输入不合法\n");
		return ERROR;
	}
	while (i != 0)
	{
		p = p->next;
		i--;
	}
	e = p->data;
	return OK;
}
Status LocateElem(linklist L, ElemType e)
{
	if (!L)
	{
		printf("该表不存在");
		return ERROR;
	}
	linklist p;
	int i=0;
	p = L->next;
	while (p)
	{
		i++;
		if (p->data == e)
		{
			return i;
		}
		p = p->next;
	}
	return FALSE;
}
Status PriorElem(linklist L, ElemType cur_e, ElemType& pre_e)
{
	if (!L)
	{
		printf("该表不存在");
		return ERROR;
	}
	linklist p,q;
	p = L->next;
	q = L;
	if (p->data == cur_e)
	{
		printf("当前元素为首位，无前驱\n");
		return FALSE;
	}
	else
	{
		while (p!=NULL)
		{
			if (p->data == cur_e)
			{
				pre_e = q->data;
				printf("其前驱为：%d\n", pre_e);
				return OK;
			}
			q = p;
			p = p->next;
		}
	}
	printf("当前元素不在链表中\n");
	return FALSE;
}
Status NextElem(linklist L, ElemType cur_e, ElemType& next_e)
{
	if (!L)
	{
		printf("该表不存在");
		return ERROR;
	}
	linklist p;
	p = L->next;
	while (p->next != NULL)
		p = p->next;  //跳到最后一个元素
	if (p->data == cur_e)
	{
		printf("当前元素为末位，无后继\n");
		return FALSE;
	}
	p = L->next;
	while (p != NULL)
	{
		if (p->data == cur_e)
		{
			next_e = p->next->data;
			printf("其后继为：%d\n", next_e);
			return OK;
		}
		p = p->next;
	}
	printf("当前元素不在链表中\n");
	return FALSE;
}
Status ListInsert(linklist& L, int i, ElemType e)
{
	if (!L)
	{
		printf("该表不存在");
		return ERROR;
	}
	int j=0;
	linklist q,s;
	s = (linklist)malloc(sizeof(LNode));
	if (s == NULL) 
	{
		printf("空间分配失败\n");
		return ERROR;
	}
	s->data = e;    //构建新的结点
	if (i<1 || i>ListLength(L) + 1)
	{
		printf("插入元素位序越界，i值不合法\n");
		return ERROR;
	}
	else
	{
		q = L;
		j++;
		while (j != i)   //找到插入位置
		{
			q = q->next;
			j++;
		}
		s->next = q->next;
		q->next = s;
		return OK;
	}
}
Status ListDelete(linklist& L, int i, ElemType& e)
{
	if (!L)
	{
		printf("该表不存在");
		return ERROR;
	}
	linklist p,q;
	int j = 1;
	if (i<1 || i>ListLength(L))
	{
		printf("删除元素位序越界，i值不合法\n");
		return ERROR;
	}
	p = L;
	q = L->next;
	while (j != i) //寻找删除位置
	{
		q = q->next;
		p = p->next;
		j++;
	}
	e = q->data;
	//printf("被删除元素为：%d\n", e);
	p->next = q->next;
	free(q);
	return OK;
}
void visit(linklist L)
{
	if (!L)
	{
		printf("该表不存在");
	}
	else
	{
		printf("%d ", L->data);  
	}
}
Status ListTraverse(linklist L)
{
	if (!L)
	{
		printf("该表不存在");
		return ERROR;
	}
	linklist p;
	p = L->next;
	while (p)
	{
		visit(p);
		p = p->next;
	}
	printf("\n");
	return OK;
}
Status ListInverse(linklist &L)  //链表逆置
{
	if (!L)
	{
		printf("该表不存在");
		return ERROR;
	}
	linklist p,q,r;
	p = L->next;
	q = p->next;
	while (q)
	{
		r = L->next;
		
		p->next = q->next;
		q->next = r;L->next = q;
		q = p->next;
	}
	return OK;
}
Status ListInsertSort(linklist& L)  //链表排序，升序
{
	if (!L)
	{
		printf("该表不存在");
		return ERROR;
	}
	int n = ListLength(L);
	int i;
	linklist p, q, r;
	if (n > 1) 
	{
		p = L->next; // p一直指向已有序排列的部分的最后一个元素
		q = p->next; // q当前操作的元素
		for (i = 1; i < n; i++)  // 将第一个元素当作有序的，从第二个开始
		{
			r = L;
			if (q->data < p->data)  // 相等不操作，保证排序的稳定性
			{
				while (r != p)   // 遍历到有序部分的尾部结束
				{
					if (q->data < r->next->data)// 相等不操作，保证排序的稳定性
					{
						p->next = q->next;
						q->next = r->next;
						r->next = q;
						q = p->next;
						break;    // 已正确插入则退出循环
					}
					r = r->next;
				}
			}
			else
			{
				p = q;
				q = q->next;
			}
		}
	}
	return OK;
}
Status List_Insection_Set(linklist& La, linklist& Lb, linklist& Lc)
{    //求两表的交集元素
	if (!La || !Lb || !Lc)
	{
		printf("表不存在\n");
		return ERROR;
	}
	int i=0, t;
	ElemType e;
	linklist q = Lb->next;
	linklist p = La->next;
	linklist r = La;
	linklist temp;
	if (!p || !q)
	{
		printf("表交集为空集\n");
		return ERROR;
	}
	while(p != NULL)  //从表A中遍历所有元素，不是交集元素则进行删除
	{
		i++;
		t = 0;
		while (q) //查询表B中元素
		{
			if (p->data == q->data)   //此次操作的元素是交集元素
			{
				t = 1;
				break;
			}
			else if (p->data > q->data)
			{
				q = q->next;
			}
			else
			{
				break;
			}
		}
		if (!t)
		{
			ListDelete(La, i, e); //不是交集元素，删除
			i--;  //下次操作的元素位序不变
			p = r->next;
		}
		else
		{
			r = p;
			p = p->next;
		}
	}
	Lc = La;
	ListInsertSort(Lc);
	p = Lc->next;
	if(p)   //空集不必判断是否有相同元素
	{ 
		q = p->next;
		while (q)
		{
			if (p->data == q->data)  //删除相同元素
			{
				p->next = q->next;
				temp = q;
				q = p->next;
				free(temp);
			}
			else
			{
				p = q;
				q = q->next;
			}
		}
	}
	if (ListLength(Lc) == 0)
	{
		printf("表A与表B交集为空\n");
	}
	else
	{
		printf("表A与表B的交集为：");
		ListTraverse(Lc);
	}
	return OK;
}
Status Listunion(linklist& La, linklist& Lb, linklist& Lc)
{
	int i, j;
	ElemType e;
	linklist temp;
	linklist p = La->next;
	linklist q = Lb->next; 
	linklist r = La;
	while (q)      //表b中元素遍历一遍
	{
		e = q->data;  //b中要比较的元素
		while (p)
		{
			if (e < p->data)   //e不在表a中,需要插入
			{
				temp = (linklist)malloc(sizeof(LNode));
				if (!temp)
				{
					printf("存储空间分配失败");
						return ERROR;
				}
				temp->data = e;   //保存B,新建结点
				r->next = temp;
				temp->next = p;
				r = r->next;
				q = q->next;   //访问表B的下一个元素
				break;
			}
			else if (e == p->data)    //此元素在A中
			{
				q = q->next;
				break;
			}
			else
			{
				r = p;
				p = p->next;
			}
		}
		if (!p)  //Az中元素已遍历结束，B中剩余元素全部插入
		{
			temp = (linklist)malloc(sizeof(LNode));
			if (!temp)
			{
				printf("存储空间分配失败");
				return ERROR;
			}
			temp->data = e;
			r->next = temp;
			temp->next = p;
			r = r->next;
			q = q->next;   //访问下一个元素
		}
	}
	Lc = La;
	p = Lc->next;
	if (p)   //空集不必判断是否有相同元素
	{
		q = p->next;
		while (q)
		{
			if (p->data == q->data)  //删除相同元素
			{
				p->next = q->next;
				temp = q;
				free(temp);
				q = p->next;
			}
			else
			{
				p = q;
				q = q->next;
			}
		}
	}
	if (ListLength(Lc) == 0)
	{
		printf("表A与表B并集为空\n");
	}
	else
	{
		printf("表A与表B的并集为：");
		ListTraverse(Lc);
	}
	return OK;
}
int main()
{
	linklist L,La,Lb,Lc;
	ElemType e,cur_e,pre_e,next_e;
	int i,n;
	char ch;
	InitList(La);
	printf("请输入表A元素个数：");
	scanf_s("%d", &n);
	printf("请依次输入数据元素：");
	for (i = 1; i <= n; i++)
	{
		scanf_s("%d",&e);
		ListInsert(La, i, e);
	}
	InitList(Lb);
	printf("请输入表B元素个数：");
	scanf_s("%d", &n);
	printf("请依次输入数据元素：");
	for (i = 1; i <= n; i++)
	{
		scanf_s("%d", &e);
		ListInsert(Lb, i, e);
	}
	if (ListEmpty(La))
	{
		printf("表A为空\n");
	}
	if (ListEmpty(Lb))
	{
		printf("表B为空\n");
	}
	ListInsertSort(La);
	printf("排序后的表A内容为：");
	ListTraverse(La);
	
	ListInsertSort(Lb);
	printf("排序后的表B内容为：");
	ListTraverse(Lb);
	Listunion(La, Lb, Lc);
	//List_Insection_Set(La, Lb, Lc);
	/*ch = getchar();
	printf("是否需要逆置链性表（是y 否n）");
	if (getchar() == 'y')
	{
		ListInverse(L);
		printf("逆置后的链性表为：");
		ListTraverse(L);
	}
	type = GetElem(L, i, e);

	printf("请输入需要查询其前驱的数据元素：");
	scanf_s("%d", &cur_e);
	PriorElem(L, cur_e, pre_e);

	printf("请输入需要查询其后继的数据元素：");
	scanf_s("%d", &cur_e);
	NextElem(L, cur_e, next_e);
	
	ch = getchar(); //读走缓冲区的\n
	printf("是否需要删除数据元素（是y 否n）");
	if (getchar() == 'y')
	{
		printf("请输入要删除元素的位序：");
		scanf_s("%d", &i);
		ListDelete(L, i, e);
		printf("被删除的元素为：");
		printf("%d\n", (int)e);
		printf("删除后的链性表为：");
		ListTraverse(L);
	}

	ch = getchar(); //读走缓冲区的\n
	printf("是否需要插入数据元素（是y 否n）");
	if (getchar() == 'y')
	{
		printf("请输入要插入的元素：");
		scanf_s("%d", &e);
		printf("请输入要插入元素的位序：");
		scanf_s("%d", &i);
		ListInsert(L, i, e);
		printf("插入后的链性表为：");
		ListTraverse(L);
		DestoryList(L);
	}*/
	DestoryList(La);
	DestoryList(Lb);
	return OK;
}