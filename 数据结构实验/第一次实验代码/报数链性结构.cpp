#include <stdio.h>
#include <stdlib.h>

typedef struct person
{
	int num;  //人的信息
	struct person* next;
}P,*L;
int main()
{
	L head,p,temp;
	int m, n,i;
	scanf_s("%d %d", &n, &m);
	if (m >= n || m <= 0 || n <= 0) //判断输入是否合法
	{
		printf("输入不合法");
		return -1;
	}
	head = (L)malloc(sizeof(P));
	if (!head)
	{
		printf("空间分配失败");
		return - 1;
	}
	p = head;
	for (i = 0; i < n; i++)
	{
		temp = (L)malloc(sizeof(P));
		if (temp)   //构建链表并初始化人物信息
		{
			temp->next = NULL;
			temp->num = i + 1;
			p->next = temp;
			p = temp;
		}
	}
	L q;
	p = head->next;
	q = head;
	int j = 1; //计数
	while (head->next->next) //剩下一个人的时候结束循环
	{
		if (j == m) //报到 m 的人出列并将报数清零
		{
			q->next = p->next;
			printf("%d ", p->num);
			j = 0;
			p = q->next;
		}
		else  //下一位报数
		{
			q = p;
			p = p->next;
		}
		if (!p) //报数到尾之后回到头处
		{
			p = head->next;
			q = head;
		}
		j++;
	}
	printf("%d", head->next->num); //打印最后一人的信息
	return 0;
}