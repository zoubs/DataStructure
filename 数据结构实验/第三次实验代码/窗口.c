#include <stdio.h>
#include <stdlib.h>
typedef struct win
{
	int x1;
	int y1;
	int x2;
	int y2;
	int num;
	struct win * next;
}WIN,*p;
struct point
{
	int x;
	int y;
};
int main ()
{
	p head,t,s,r;
	int N,M,i,x,y,IN;
	head = (p)malloc(sizeof(WIN));
	head->next = NULL;
	head->x1 = 0;
	head->x2 = 0;
	head->y1 = 0;
	head->y2 = 0;
	head->num = 0;
	scanf("%d %d",&N,&M);
	for(i=0;i<N;i++)  //初始化，顶层的更靠近头节点 
	{
		s = (p)malloc(sizeof(WIN));
		scanf("%d %d %d %d",&(s->x1),&(s->y1),&(s->x2),&(s->y2));
		s->num = i+1;
		s->next = head->next;
		head->next = s;
	}
	t = head->next;
	r = head;
	struct point B[M];
	for(i=0;i<M;i++)
	{
		scanf("%d %d",&B[i].x,&B[i].y);
	}
	for(i=0;i<M;i++)
	{
		IN = (B[i].x >= t->x1 && B[i].x <= t->x2 && B[i].y >= t->y1 && B[i].y <= t->y2) ? 1 : 0;  //判断是否落在当前窗口 
		while(t!=NULL && !IN)  //未落在当前窗口里则进入循环 
		{
			r = t;
			t = t->next;
			if(t!=NULL)
			{
				IN = (B[i].x >= t->x1 && B[i].x <= t->x2 && B[i].y >= t->y1 && B[i].y <= t->y2) ? 1 : 0;////判断是否落在当前窗口  
			}
		}
		if(!t)
		{	
			printf("IGNORED\n"); 
		}
		else 
		{
			printf("%d\n",t->num);
			r->next = t->next;
			t->next = head->next;   //改变窗口层数 
			head->next = t;
		}
		t = head->next;
		r = head;
	}
	return 0;
} 
