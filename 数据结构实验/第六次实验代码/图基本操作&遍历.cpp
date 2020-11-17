#include<iostream>
#include<stdio.h>
using namespace std;

#define INFINITY INT_MAX   //定义最大值
#define MAX_V 20    //最大顶点数目
#define Stack_Init_Size  200
#define STACKINCREMENT   40


#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
typedef char GElemType;
typedef int QElemType;
typedef int Status;
typedef struct
{
	int code;   //顶点编号
	GElemType info;  //顶点其他信息
}VertexType;
typedef enum 
{
	 UDG, DG, UDN, DN       //无向图、有向图、无向网、有向网
}GraphKind;
typedef struct
{
	int arcs[MAX_V][MAX_V];   //邻接矩阵
	int vexnum, arcnum;      //图包含的顶点数与边的个数
	VertexType vexs[MAX_V];  //存放顶点信息
	GraphKind type;          //图的种类标志，分为无向图、有向图、无向网、有向网
}MGraph;


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

Status LocateVex(MGraph G, GElemType v)  //寻找顶点在图中的位置
{
	int i;
	for (i = 0; i < G.vexnum; i++)
	{
		if (G.vexs[i].info == v)
		{
			return i;
		}
	}
	return -1;
}
Status CreateUDN(MGraph& G)    //无向网
{
	G.type = UDN;
	int i, j, k;
	char ch;
	GElemType v1, v2;
	int weight;    //权值
	cout << "请输入图的信息（顶点数、边数）：";
	cin >> G.vexnum >> G.arcnum;
	ch = getchar();
	cout << "请输入顶点信息：";
	for (i = 0; i < G.vexnum; i++)    //初始化顶点信息
	{
		cin >> G.vexs[i].info;
		G.vexs[i].code = i;
	}
	for (i = 0; i < G.vexnum; i++)     //初始化邻接矩阵
	{
		for (j = 0; j < G.vexnum; j++)    //初始化边的信息最大值
		{
			G.arcs[i][j] = INFINITY;
		}
	}
	cout << "请输入边以及依附的顶点及权值：";
	for (k = 0; k < G.arcnum; k++)     //构造邻接矩阵
	{
		cin >> v1 >> v2 >> weight;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (i < 0)
		{
			cout << "顶点1不在图中，请重新输入" << endl;
			k--;
		}
		else if (j < 0)
		{
			cout << "顶点2不在图中，请重新输入" << endl;
			k--;
		}
		else
		{
			G.arcs[i][j] = weight;
			G.arcs[j][i] = G.arcs[i][j];//无向网，对称
		}
	}
	return OK;
}
Status CreateUDG(MGraph& G)     //无向图
{
	G.type = UDG;
	int i, j, k;
	char ch;
	GElemType v1, v2;
	cout << "请输入顶点个数以及边的条数：";
	cin >> G.vexnum >> G.arcnum;
	ch = getchar();
	cout << "请输入顶点的信息：";
	for (i = 0; i < G.vexnum; i++)    //初始化顶点信息
	{
		cin >> G.vexs[i].info;    //顶点信息
		G.vexs[i].code = i;    //顶点编号
	}
	for (i = 0; i < G.vexnum; i++)   //初始化邻接矩阵
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = 0;
		}
	}
	cout << "请依次输入边依附的顶点：";
	for (k = 0; k < G.arcnum; k++)
	{
		cin >> v1 >> v2;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (i < 0)
		{
			cout << "顶点1不在图中，请重新输入" << endl;
			k--;
		}
		else if (j < 0)
		{
			cout << "顶点2不在图中，请重新输入" << endl;
			k--;
		}
		else
		{
			G.arcs[i][j] = 1;
			G.arcs[j][i] = 1;    //无向图，对称
		} 
	}
	return OK;
}
Status CreateDN(MGraph& G)    //有向网
{
	G.type = DN;
	int i, j, k;
	char ch;
	int weight;
	GElemType v1, v2;
	cout << "请输入顶点个数以及边的条数：";
	cin >> G.vexnum >> G.arcnum;
	ch = getchar();
	cout << "请输入顶点信息：";
	for (i = 0; i < G.vexnum; i++)   //初始化顶点信息
	{
		cin >> G.vexs[i].info;
		G.vexs[i].code = i;
	}
	for (i = 0; i < G.vexnum; i++)    //初始化邻接矩阵
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = INFINITY;
		}
	}
	cout << "请依次输入边依附的两个顶点及权值（v1->v2）：";
	for (k = 0; k < G.arcnum; k++)
	{
		cin >> v1 >> v2 >> weight;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (i < 0)
		{
			cout << "顶点1不在图中，请重新输入" << endl;
			k--;
		}
		else if (j < 0)
		{
			cout << "顶点2不在图中，请重新输入" << endl;
			k--;
		}
		else
		{
			G.arcs[i][j] = weight;
		}
	}
	return OK;
}
Status CreateDG(MGraph& G)    //有向图
{
	G.type = DG;
	int i, j, k;
	char ch;
	GElemType v1, v2;
	cout << "请输入顶点个数以及边的条数：";
	cin >> G.vexnum >> G.arcnum;
	ch = getchar();
	cout << "请输入顶点信息：";
	for (i = 0; i < G.vexnum; i++)   //初始化顶点信息
	{
		cin >> G.vexs[i].info;
		G.vexs[i].code = i;
	}
	for (i = 0; i < G.vexnum; i++)    //初始化邻接矩阵
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = 0;
		}
	}
	cout << "请依次输入边依附的两个顶点（v1->v2）：";
	for (k = 0; k < G.arcnum; k++)
	{
		cin >> v1 >> v2;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (i < 0)
		{
			cout << "顶点1不在图中，请重新输入" << endl;
			k--;
		}
		else if (j < 0)
		{
			cout << "顶点2不在图中，请重新输入" << endl;
			k--;
		}
		else
		{
			G.arcs[i][j] = 1;
		}
	}
	return OK;
}
Status CreateGraph(MGraph& G)         //选择你要创建的图的类型（有向图1，有向网2，无向图3，无向网4）
{
	cout<<"选择你要创建的图的类型（有向图1，有向网2，无向图3，无向网4）：";
	int a;
	cin >> a;
	switch (a) 
	{
	case 1:return CreateDG(G);
	case 2:return CreateDN(G);
	case 3:return CreateUDG(G);
	case 4:return CreateUDN(G);
	default:return CreateGraph(G);
	}
}
Status DestroyGraph(MGraph& G)
{
		free(G.arcs);
		free(G.vexs);
		return OK;
}
char GetVex(MGraph G, int i)     //返回顶点值
{
	if (i > G.vexnum || i < 1)
	{
		cout << "图中无该顶点" << endl;
		return NULL;
	}
	else
	{
		cout << "该顶点的值为：" << G.vexs[i - 1].info << endl;
		return G.vexs[i - 1].info;
	}
}
Status PutVex(MGraph& G, int i, GElemType value)      //将顶点值改为value
{
	if (i > G.vexnum || i < 1)
	{
		cout << "图中不存在该结点" << endl;
		return ERROR;
	}
	else
	{
		G.vexs[i - 1].info = value;
		return OK;
	}
}
Status FirstAdjVex_text(MGraph G, GElemType v)    //返回v的第一个邻接顶点
{
	int i, j;
	if (G.type == UDG || G.type == DG)   //无向图或有向图
	{
		i = LocateVex(G, v);
		if (i == -1)
		{
			cout << "该顶点不在图中" << endl;
			return -1;
		}
		else
		{
			for (j = 0; j < G.vexnum; j++)
			{
				if (G.arcs[i][j] == 1)
				{
					cout << "第一个邻接点为：" << G.vexs[j].info<<"编号为："<< j+1 << endl;
					return j;
				}
			}
			cout << "顶点" << v << "没有邻接点" << endl;
			return -1;
		}
	}
	else if (G.type == UDN || G.type == DN)     //有向网、无向网
	{
		i = LocateVex(G, v);
		if (i == -1)
		{
			cout << "该顶点不在图中" << endl;
			return -1;
		}
		for (j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] != INFINITY)
			{
				cout << "第一个邻接点为：" << G.vexs[j].info << "编号为：" << j + 1 << endl;
				return j;
			}
		}
		cout << "顶点" << v << "没有邻接点" << endl;
		return -1;
	}
}
int NextAdiVex_text(MGraph G, GElemType v, GElemType w)
{
	int i, j, k;
	i = LocateVex(G, v);
	k = LocateVex(G, w);
	if (i == -1)
	{
		cout << "顶点" << v << "不在图中" << endl;
		return -1;
	}
	if (k == -1)
	{
		cout << "顶点" << w << "不在图中" << endl;
		return -1;
	}
	if (G.type == DN || G.type == UDN)
	{
		for (j = k + 1; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] != INFINITY)
			{
				cout << "顶点" << v << "相对于顶点" << w << "的下一个邻接点为：" << G.vexs[j].info << endl;
				return j;
			}
		}
		cout << w << "是" << v << "的最后一个邻接点" << endl;
		return -1;
	}
	else
	{
		for (j = k + 1; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] == 1)
			{
				cout << "顶点" << v << "相对于顶点" << w << "的下一个邻接点为：" << G.vexs[j].info << endl;
				return j;
			}
		}
		cout << w << "是" << v << "的最后一个邻接点" << endl;
		return -1;
	}
}

int InsertVex(MGraph& G, GElemType v)
{
	int i, j;
	i = LocateVex(G, v);
	if (i != -1) 
	{
		cout<<"已存在该顶点\n";
		return -1;
	}
	j = G.vexnum;
	G.vexs[j].info = v;
	G.vexs[j].code = j;
	if (G.type == UDG || G.type == DG)  //有向图、无向图
	{
		for (i = 0; i <= j; i++)
		{
			G.arcs[j][i] = 0;
			G.arcs[i][j] = 0;
		}
	}
	else
	{
		for (i = 0; i <= j; i++)
		{
			G.arcs[j][i] = INFINITY;
			G.arcs[i][j] = INFINITY;
		}
	}
	cout << "顶点" << v << "已添加"<<endl;
	G.vexnum++;   //顶点数加一
	return OK;
}
int DeleteVex(MGraph& G, GElemType v)
{
	int i, j, k;
	i = LocateVex(G, v);
	if (i == -1)
	{
		cout << "顶点" << v << "不在图中" << endl;
		return -1;
	}
	for (j = i; j < G.vexnum - 1; j++)
	{
		G.vexs[j] = G.vexs[j + 1];
	}
	if (G.type == DG)     //有向图
	{
		for (k = 0; k < G.vexnum; k++)
		{
			if (G.arcs[i][k] != 0)
			{
				G.arcnum--;
			}
			if (G.arcs[k][i] != 0)
			{
				G.arcnum--;
			}
		}
	}
	else if (G.type == UDG)   //无向图
	{
		for (k = 0; k < G.vexnum; k++)
		{
			if (G.arcs[i][k] != 0)
			{
				G.arcnum--;
			}
		}
	}
	else if (G.type == DN)   //有向网
	{
		for (k = 0; k < G.vexnum; k++)
		{
			if (G.arcs[i][k] != INFINITY)
			{
				G.arcnum--;
			}
			if (G.arcs[k][i] != INFINITY)
			{
				G.arcnum--;
			}
		}
	}
	else             //无向网
	{
		for (k = 0; k < G.vexnum; k++)
		{
			if (G.arcs[i][k] != INFINITY)
			{
				G.arcnum--;
			}
		}
	}
	for (j = i; j < G.vexnum - 1; j++)
	{
		for (k = 0; k < G.vexnum; k++)
		{
			G.arcs[j][k] = G.arcs[j + 1][k];
			G.arcs[k][j] = G.arcs[k][j + 1];
		}
	}
	cout << "顶点" << v << "已删除"<<endl;
	G.vexnum--;
	return OK;
}
int InsertArc(MGraph& G, GElemType v, GElemType w)
{
	int i, j;
	int weight;
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if (i == -1)
	{
		cout << "顶点" << v << "不在图中" << endl;
		return -1;
	}
	if (j == -1)
	{
		cout << "顶点" << v << "不在图中" << endl;
		return -1;
	}
	if (G.type == DG)  //有向图
	{
		G.arcs[i][j] = 1;
	}
	else if (G.type == UDG)  //无向图
	{
		G.arcs[i][j] = 1;
		G.arcs[j][i] = 1;
	}
	else if (G.type == DN)   //有向网
	{
		cout << "请输入该条边的权值：";
		cin >> weight;
		G.arcs[i][j] = weight;
	}
	else if (G.type == UDN)   //无向网
	{
		cout << "请输入该条边的权值：";
		cin >> weight;
		G.arcs[i][j] = weight;
		G.arcs[j][i] = weight;
	}
	cout << "添加边完毕"<<endl;
	return OK;
}
int DeleteArc(MGraph& G, GElemType v, GElemType w)
{
	int i, j;
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if (i == -1)
	{
		cout << "顶点" << v << "不在图中" << endl;
		return -1;
	}
	if (j == -1)
	{
		cout << "顶点" << v << "不在图中" << endl;
		return -1;
	}
	if (G.type == DG)  //有向图
	{
		G.arcs[i][j] = 0;
	}
	else if (G.type == UDG)  //无向图
	{
		G.arcs[i][j] = 0;
		G.arcs[j][i] = 0;
	}
	else if (G.type == DN)   //有向网
	{
		G.arcs[i][j] = INFINITY;
	}
	else if (G.type == UDN)   //无向网
	{
		G.arcs[i][j] = INFINITY;
		G.arcs[j][i] = INFINITY;
	}
	cout << "删除边完毕" << endl;
	return OK;
}
int NextAdiVex(MGraph G, GElemType v, GElemType w)
{
	int i, j, k;
	i = LocateVex(G, v);
	k = LocateVex(G, w);
	if (G.type == DN || G.type == UDN)
	{
		for (j = k + 1; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] != INFINITY)
			{
				return j;
			}
		}
		return -1;
	}
	else
	{
		for (j = k + 1; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] == 1)
			{
				return j;
			}
		}
		return -1;
	}
}
int FirstAdjVex(MGraph G, GElemType v)    //返回v的第一个邻接顶点
{
	int i, j;
	if (G.type == UDG || G.type == DG)   //无向图或有向图
	{
		i = LocateVex(G, v);
		for (j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] == 1)
			{
				return j;
			}
		}
		return -1;
		
	}
	else if (G.type == UDN || G.type == DN)     //有向网、无向网
	{
		i = LocateVex(G, v);
		for (j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] != INFINITY)
			{
				return j;
			}
		}
		return -1;
	}
}

void DFS(MGraph G, int v, bool* visited)
{
	visited[v] = true;
	int w;
	cout << G.vexs[v].info << "  ";
	w = FirstAdjVex(G, G.vexs[v].info);
	while (w >= 0)
	{
		if (!visited[w])
		{
			DFS(G, w, visited);
		}
		w = NextAdiVex(G, G.vexs[v].info, G.vexs[w].info);
	}
}

void DFSTraverse(MGraph G)  //深度优先遍历
{
	int i;
	bool visited[MAX_V];     //访问标记数组
	for (i = 0; i < G.vexnum; i++)  //初始化
	{
		visited[i] = false;
	}
	cout << "深度优先遍历结果为：";
	for (i = 0; i < G.vexnum; i++)
	{
		if (!visited[i])
		{
			DFS(G, i, visited);
		}
	}
	cout << endl;
}

int BFSTraverse(MGraph G)   //广度优先遍历
{
	int v, u, w;
	LinkQueue Q;
	bool visited[MAX_V];
	for (v = 0; v < G.vexnum; v++)
	{
		visited[v] = false;
	}
	InitQueue(Q);   //初始化队列
	cout << "广度优先遍历结果为：";
	for (v = 0; v < G.vexnum; v++)
	{
		if (!visited[v])
		{
			visited[v] = true;
			cout << G.vexs[v].info << "   ";
			EnQueue(Q, v);   //入队
			while (!QueueEmpty(Q))
			{
				DeQueue(Q, u);
				for (w = FirstAdjVex(G, G.vexs[u].info);w>=0;w = NextAdiVex(G, G.vexs[u].info, G.vexs[w].info))
				{
					if (!visited[w])   //若未被访问
					{
						visited[w] = true;
						cout << G.vexs[w].info << "   ";
						EnQueue(Q, w);
					}
				}
			}
		}
	}
	cout << endl;
}
int main()
{
	MGraph G;
	CreateGraph(G);
	DFSTraverse(G);
	BFSTraverse(G);
	DeleteVex(G, 'C');
	DFSTraverse(G);
	BFSTraverse(G);
	/*
	A B
	A D
	B C
	C D
	C E
	*/
	return 0;
}