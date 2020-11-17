#pragma warning (disable : 4996)
#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#define source "MinimumSpanningTree.txt"   //源文件地址
#define MAX_NAME 20    //顶点名字的最大长度为20
#define maxx INT_MAX

typedef struct MyGraph
{
	int type;            //0，表示无向网，1表示有向网
	int arcnum;          //边的个数
	int vexnum;          //顶点个数
	char** vexname;      //存放顶点名的二维数组
	float** Arcs;           //邻接矩阵，A[i][j]表示i号顶点与j号顶点之间边的权值，若i,j之间没有边，则A[i][j]取值无穷大
}GH;

typedef struct help
{
	int index;       //下标
	float weight;    //权重
}HELP;               //辅助数组

float SUM = 0;
int findvex(char* s, GH* G);//确定顶点s对应的序号，参数：顶点名称s，图G
void creatgraph(GH* G);//以邻接矩阵的形式创建图，参数：图G
void showgraph(GH* G);//以邻接表的形式显示图,参数：图G
void initi(GH* T, GH* G);//初始化最小生成树,参数：图T 图G
void add(int a, int b, GH* T, GH* G);//将（a,b）这条边加入到图T中去，参数：顶点下标a，b，图T 图G
void prim(GH* G);//普里姆算法，参数：图G

int main()
{
	GH G;
	char vex[20];
	creatgraph(&G);//创建图
	showgraph(&G);//显示图
	prim(&G);//普里姆算法
	cout << "最小生成树权值之和为：" << SUM << endl;
	return 0;
}

//**********************************************************
void creatgraph(GH *G)
{
	fstream fin;
	fin.open(source, ios::in);
	if (fin.fail())
	{
		cout << "文件打开失败";
		exit(0);
	}
	int i, j, M;
	int len;
	float weight;
	char s1[20], s2[20];
	fin >> M;  //顶点个数
	G->vexnum = M;
	G->vexname = (char**)malloc(M * sizeof(char*));    //分配M个存储顶点名字的向量指针
	if (!G->vexname)
	{
		cout << "空间分配失败";
		exit(0);
	}
	G->Arcs = (float**)malloc(M * sizeof(float*));      //分配M个存储邻接矩阵的向量指针
	if (!G->Arcs)
	{
		cout << "空间分配失败";
		exit(0);
	}
	G->type = 0;
	G->arcnum = 0;

	for (i = 0; i < M; i++)   //初始化顶点信息和边
	{
		fin >> s1;
		G->vexname[i] = (char*)malloc(strlen(s1) * sizeof(char));
		if (!G->vexname[i])
		{
			cout << "空间分配失败";
			exit(0);
		}
		len = strlen(s1);
		strcpy(G->vexname[i],s1);
		G->Arcs[i] = (float*)malloc(M * sizeof(float));
		if (!G->Arcs[i])
		{
			cout << "空间分配失败";
			exit(0);
		}
		for (j = 0; j < M; j++)   //初始化边
		{
			G->Arcs[i][j] = maxx;
		}   
	}
	while (!fin.eof())
	{
		fin >> s1 >> s2 >> weight;
		if (fin.eof())
		{
			break;
		}
		i = findvex(s1, G);
		j = findvex(s2, G);
		G->Arcs[i][j] = weight;
		if (G->type == 0)  //无向网
		{
			G->Arcs[j][i] = weight;
		}
		G->arcnum++;
	}

}
//**********************************************************
int findvex(char* s, GH* G)  //确定顶点s对应的序号，参数：顶点名称s，图G
{
	int i;
	for (i = 0; i < G->vexnum; i++)
	{
		if (strcmp(s, G->vexname[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}
//**********************************************************
void showgraph(GH* G)//以邻接表的形式显示图,参数：图G
{
	int i, j;
	SUM = 0;
	for (i = 0; i < G->vexnum; i++)
	{
		cout << endl << G->vexname[i];
		for (j = 0; j < G->vexnum; j++)
		{
			if (G->Arcs[i][j] < maxx)
			{
				SUM += G->Arcs[i][j];
				cout << "---" << G->vexname[j] <<"("<< G->Arcs[i][j]<<")";
			}
		}
	}
	SUM = SUM / 2;
	cout << endl;
}
//**********************************************************
void prim(GH* G)//普里姆算法求最小生成树
{
	HELP* H;
	int i;
	int M;
	int n = 0;
	int temp, i1 = 0;//寻找辅助数组中权值最小的
	GH T;

	initi(&T, G);

	M = G->vexnum;

	H = (HELP*)malloc(M * sizeof(HELP));
	if (!H)
	{
		cout << "空间分配失败";
		exit(0);
	}

	for (i = 0; i < M; i++)
	{
		H[i].index = 0;
		H[i].weight = G->Arcs[H[i].index][i];
	}        //初始化选0做起点
	H[0].weight = 0;
	n++;

	while (n <= M)
	{

		for (i = 0; i < M; i++)
		{
			if (H[i].weight != 0) //选中某一个非0的weight和i
			{
				i1 = i;
				temp = H[i].weight;
				break;
			}
		}

		for (i = 0; i < M; i++)
		{
			if (H[i].weight < temp && H[i].weight != 0) //找最小值
			{
				temp = H[i].weight;
				i1 = i;
			}
		}
		add(H[i1].index, i1, &T, G);//将这个最小值的两个顶点对应的边放入T

		H[i1].weight = 0;//重置这个最小值的weight为0，表示已经选过

		for (i = 0; i < M; i++)
		{
			if (H[i].weight > G->Arcs[i1][i])
			{
				H[i].index = i1;
				H[i].weight = G->Arcs[i1][i];
			}
		}
		n++;
	}

	cout << "用prim算法得到最小生成树为：\n";
	showgraph(&T);     //用邻接表的形式显示最小生成树
	//cout << "最小生成树的权值为：" << SUM << endl;
}
//**********************************************************
void initi(GH* T, GH* G)
{
	int i, j, M;
	char s1[20];
	M = G->vexnum;
	T->arcnum = 0;
	T->type = G->type;
	T->vexnum = M;
	T->vexname = (char**)malloc(M * sizeof(char*));
	if (!T->vexname)
	{
		cout << "空间分配失败";
		exit(0);
	}
	T->Arcs = (float**)malloc(M * sizeof(float*));
	if (!T->Arcs)
	{
		cout << "空间分配失败";
		exit(0);
	}

	for (i = 0; i < M; i++)
	{
		strcpy(s1 ,G->vexname[i]);
		T->vexname[i] = (char*)malloc(strlen(s1) * sizeof(char));
		if (!T->vexname[i])
		{
			cout << "空间分配失败";
			exit(0);
		}
		strcpy(T->vexname[i],s1);
		T->Arcs[i] = (float*)malloc(M * sizeof(float));
		if (!T->Arcs[i])
		{
			cout << "空间分配失败";
			exit(0);
		}
		for (j = 0; j < M; j++)//初始化
		{
			T->Arcs[i][j] = maxx;
		}

	}
}
//**********************************************************
void add(int a, int b, GH* T, GH* G)
{
	T->Arcs[a][b] = G->Arcs[a][b];      //无向图则将这两个数据更新
	T->Arcs[b][a] = G->Arcs[b][a];
	T->arcnum++;
}