#include <iostream>
#include <fstream>
#include<iomanip>
using namespace std;

#define INFINITY 10000   //定义最大值
#define MAX_V 20    //最大顶点数目
typedef char GElemType;

typedef enum
{
	UDG, DG, UDN, DN       //无向图、有向图、无向网、有向网
}GraphKind;
typedef struct
{
	int code;   //顶点编号
	GElemType info;  //顶点其他信息
}VertexType;
typedef struct
{
	int arcs[MAX_V][MAX_V];   //邻接矩阵
	int vexnum, arcnum;      //图包含的顶点数与边的个数
	VertexType vexs[MAX_V];  //存放顶点信息
	GraphKind type;          //图的种类标志，分为无向图、有向图、无向网、有向网
}MGraph;

int LocateVex(MGraph G, GElemType v)  //寻找顶点在图中的位置
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
int Closest(MGraph G, int* dist, bool* flag)
{
	int i, min = MAX_V - 1;
	for (i = 0; i < G.vexnum; i++)
	{
		if (!flag[i])
		{
			if (dist[i] <= dist[min])
			{
				min = i;
			}
		}
	}
	return min;
}
void MyGraph(MGraph& G)
{
	fstream f;
	int i, j;
	int weight;
	GElemType v1, v2;
	string filename;
	cout << "请输入文件名：";
	cin >> filename;
	f.open(filename, ios::in);
	if ( f.fail() )
	{
		cout << "文件打开失败";
		exit(0);
	}
	f >> G.vexnum;
	for (i = 0; i < G.vexnum; i++)      //初始化顶点
	{
		f >> G.vexs[i].info;
		G.vexs[i].code = i;
		for (j = 0; j < G.vexnum; j++)     //初始化邻接矩阵
		{
			G.arcs[i][j] = INFINITY;
		}
	}
	G.arcnum = 0;
	while (!f.eof())
	{
		f >> v1;
		f >> v2;
		f >> weight;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (i < 0)
		{
			cout << "顶点" << v1 << "不在图中";
			exit(0);
		}
		if (j < 0)
		{
			cout << "顶点" << v2 << "不在图中";
			exit(0);
		}
		G.arcs[i][j] = weight;
		if (G.type == UDN)
		{
			G.arcs[j][i] = weight;
		}
		G.arcnum++;
	}
}

void showpath(MGraph G, int* path, int* dist, int s)   //s为源点
{
	int i, p;
	int S[MAX_V];
	int top = -1;
	cout << "顶点" << G.vexs[s].info << "到其他顶点的最短路径如下：" << endl;
	for (i = 0; i < G.vexnum; i++)
	{
		if (i != s)
		{
			
			if (path[i] == s)
			{
				cout << G.vexs[i].info << " : ";
				cout << G.vexs[s].info << "->" << G.vexs[i].info;
				cout << endl << "长度为：" << dist[i] << endl;
			}
			else if (path[i] == -1)  //无路径
			{
				cout << G.vexs[s].info << "到" << G.vexs[i].info << "无路径" << endl;
			}
			else
			{
				p = path[i];
				while (p != s)
				{
					top++;
					S[top] = p;    //压栈
					p = path[p];
				}

				cout << G.vexs[i].info << " : ";
				cout << G.vexs[s].info << "->";

				while (top > -1)   //输出路径
				{
					p = S[top];
					top--;
					cout << G.vexs[p].info<< "->";
				}
				cout << G.vexs[i].info;
				cout << endl <<"长度为：" << dist[i] << endl;
			}
		}
	}
}

void shortestpath_DIJ(MGraph G, int s)    //s为起始点编号
{
	int dist[MAX_V], path[MAX_V] ;
	bool flag[MAX_V];   //设置三个辅助数组
	int i, j, k, mindist;
	for (i = 0; i < G.vexnum; i++)   //初始化辅助数组
	{
		flag[i] = false;
		dist[i] = G.arcs[s][i];
		if (dist[i] < INFINITY)
		{
			path[i] = s;
		}
		else
		{
			path[i] = -1;
		}
	}
	flag[s] = true;   //选中起始点
	for (i = 0; i < G.vexnum - 1; i++)   
	{//首先寻找这轮中离源点最近的顶点k
		k = Closest(G, dist, flag);
		flag[k] = true;     //选中
		mindist = dist[k];
		if (mindist < INFINITY)
		{//根据此次选中的顶点，更新其他顶点到源点的距离
			for (j = 0; j < G.vexnum; j++)
			{
				if (flag[j] == false && dist[j] > mindist + G.arcs[k][j])
				{
					dist[j] = mindist + G.arcs[k][j];
					path[j] = k;
				}
			}
		}
	}
	showpath(G, path, dist, s);
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


int main()
{
	MGraph G;
	G.type = DN;
	MyGraph(G);
	shortestpath_DIJ(G, 0);
	//DFSTraverse(G);
	//shortestpath.txt
	return 0;
}
