#include <stdio.h>
# include<stdlib.h>

typedef struct student
{
	int num;
	struct student * next;
} ST,*st;
int main()
{
	int m,n,i,p,q;
	int k,t;
	st head,base,temp,P;
	scanf("%d",&n);
	scanf("%d",&m);
	head = (ST*)malloc(sizeof(ST));
	head->num = 0;
	head->next = NULL;
	temp = head;
	for(i=1;i<=n;i++)  //初始化 
	{
		base = (st)malloc(sizeof(ST));
		base->num = i;
		base->next = NULL;
		temp->next = base;
		temp = base;
	}
	int j; 
	for(t=0;t<m;t++)
	{
		k=1;
		temp = head;
		P = head->next;
		scanf("%d %d",&p,&q);
		while(P->num != p) //P指向需要移动的同学位置 ,temp指向其前面一位同学的位置 
		{
			temp = P;
			P = P->next;
			k++;
		}  
		temp->next = P->next;  //需要移动的同学出列 
		if(q>0)          //向后移动，q为移动位数 
		{
			for(i=0;i<q;i++)  //移动后的位置 
			{
				temp = temp->next; 
			}
			P->next = temp->next; //进入队列 
			temp->next = P; 
		}
		else if(q<0)     // 向前移动 
		{
			temp = head;
			j = k + q;
			for(i=1;i<j;i++) // j为移动后的位置  
			{
				temp = temp->next;
			}
			P->next = temp->next; //进入队列 
			temp->next = P;
		}
	}
	P = head->next;
	while(P)  
	{
		printf("%d ",P->num);
		P = P->next;
	}
	return 0;
} 
