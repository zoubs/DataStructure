#pragma warning (disable:4996)
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


#define maxx INT_MAX
#define source "MinimumSpanningTree.txt"
typedef struct arcnode
{
	int index;//邻接点序号
	float weight;//权值
	struct arcnode* next;
}AR;

typedef struct MyGraph
{
	int type;//0，表示无向图，1表示有向图
	int arcnum, vexnum;//图中边的个数以及顶点个数
	char** vexname;//存放顶点名的二维数组
	AR* N;//存放邻接表头结点的数组
}GH;


int findvex(char* s, GH* G);//确定顶点s对应的序号,参数：顶点s，图G
void creatgraph(GH* G);//以邻接表的形式创建图,参数：图G
void showgraph(GH* G);//以邻接表的形式显示图,参数：图G
void initi(int* help, int M);//初始化数组，参数：辅助数组help,数组长度M
void kruskal(int* help, GH* G);//克鲁斯卡尔算法，参数：辅助数组help,图G
void ini(GH* T, GH* G);//初始化最小生成树的图，参数：最小生成树的图T，图G
void add(int x, int y, GH* T, float t);//往最小生成树的图中加边，参数：两个顶点x，y，最小生成树的图T，以及权值t

int main()
{
	GH G;
	int* help;
	creatgraph(&G);//创建图
	showgraph(&G);//显示图
	help = (int*)malloc(G.vexnum * sizeof(int));//为辅助数组开辟空间
	initi(help, G.vexnum);//初始化辅助数组
	kruskal(help, &G);//克鲁斯卡尔算法，参数：辅助数组help,图G
	return 0;
}
int findvex(char* s, GH* G)//确定顶点s对应的序号,参数：顶点s，图G
{
	int i;
	for (i = 0; i < G->vexnum; i++)
	{
		if (strcmp(s, G->vexname[i]) == 0)
			return i;
	}
	printf("read file error\n");
	exit(-1);
}

void creatgraph(GH* G)//以邻接表的形式创建图,参数：图G
{
	char filename[30];
	AR* p;
	int i, j, M;
	float weight;
	FILE* fp;
	char s1[20], s2[20];
	if ((fp = fopen(source, "rb")) == NULL)
	{
		printf("open error\n");
		exit(0);
	}
	fscanf(fp, "%d", &(G->vexnum));
	M = G->vexnum;
	G->type = 0;
	G->arcnum = 0;
	G->N = (AR*)malloc(M * sizeof(AR));
	G->vexname = (char**)malloc(M * sizeof(char*));

	for (i = 0; i < M; i++)
	{
		G->N[i].next = NULL;
		fscanf(fp, "%s", s1);
		G->vexname[i] = (char*)malloc(strlen(s1) * sizeof(char));
		strcpy(G->vexname[i], s1);

	}

	while (fscanf(fp, "%s%s%f", s1, s2, &weight) != EOF)
	{
		i = findvex(s1, G);
		j = findvex(s2, G);
		p = (AR*)malloc(sizeof(AR));
		p->index = j;
		p->weight = weight;
		p->next = G->N[i].next;
		G->N[i].next = p;

		if (!G->type)
		{
			p = (AR*)malloc(sizeof(AR));
			p->index = i;
			p->weight = weight;
			p->next = G->N[j].next;
			G->N[j].next = p;
		}
		(G->arcnum)++;
	}
}
void showgraph(GH* G)//以邻接表的形式显示图,参数：图G
{
	int i;
	AR* p;
	for (i = 0; i < G->vexnum; i++)
	{
		printf("\n%s ", G->vexname[i]);
		p = G->N[i].next;
		while (p)
		{
			printf("--%s(%4.2f) ", G->vexname[p->index], p->weight);
			p = p->next;
		}
	}
	printf("\n");
}
void initi(int* help, int M)//初始化数组，参数：辅助数组help,数组长度M
{
	int i;
	for (i = 0; i < M; i++)
	{
		help[i] = i;
	}
}
void kruskal(int* help, GH* G)//克鲁斯卡尔算法，参数：辅助数组help,图G
{
	int i, j, m = -1, n = -1, M, k;
	int count = 0;
	int* visit;
	float temp;
	GH T;
	AR* p;
	M = G->vexnum;
	ini(&T, G);

	visit = (int*)malloc(M * sizeof(int));
	for (i = 0; i < M; i++)//初始化visit
	{
		visit[i] = 0;
	}

	temp = maxx;
	while (count < G->arcnum)
	{

		temp = maxx;//重置temp

		for (i = 0; i < G->vexnum; i++)//遍历所有的边，找最小权值
		{
			p = G->N[i].next;
			while (p)
			{
				if (p->weight < temp)
				{
					if (visit[i] == 0 || visit[p->index] == 0)
					{
						temp = p->weight;
						m = i;
						n = p->index;
					}
				}
				p = p->next;
			}
		}

		visit[m] = 1;
		visit[n] = 1;//将这两个顶点置为已访问

		if (help[m] != help[n])//不构成回路
		{
			add(m, n, &T, temp);
			k = help[m];
			for (i = 0; i < G->vexnum; i++)
			{
				if (help[i] == k)
					help[i] = help[n];
			}
		}

		count++;
	}
	printf("\n最小生成树（克鲁斯卡尔算法）：\n");
	showgraph(&T);

}
void ini(GH* T, GH* G)//初始化最小生成树的图，参数：最小生成树的图T，图G
{
	char s1[20];
	int i, M;
	T->arcnum = 0;
	M = G->vexnum;
	T->vexnum = G->vexnum;
	T->type = G->type;
	T->vexname = (char**)malloc(sizeof(char*) * M);
	T->N = (AR*)malloc(M * sizeof(AR));//开辟头节点的空间

	for (i = 0; i < G->vexnum; i++)
	{
		T->N[i].next = NULL;
		strcpy(s1, G->vexname[i]);
		T->vexname[i] = (char*)malloc(strlen(s1) * sizeof(char));
		strcpy(T->vexname[i], s1);
	}
}
void add(int x, int y, GH* T, float temp)
{
	AR* p;

	p = (AR*)malloc(sizeof(AR));

	p->index = y;
	p->weight = temp;
	p->next = T->N[x].next;
	T->N[x].next = p;
	if (!T->type)
	{
		p = (AR*)malloc(sizeof(AR));
		p->index = x;
		p->weight = temp;
		p->next = T->N[y].next;
		T->N[y].next = p;
	}
	(T->arcnum)++;
	//printf("T中边数为：%d\n",T->arcnum);
}
