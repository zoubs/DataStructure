#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

#define source "xingcheluxian.txt"
#define MAX 100000000   //道路最大长度
typedef struct
{
	int length;  //路径长度
	int type;    //路径类型
}road;

typedef struct
{
	int vexnum;    //顶点数目
	int arcnum;    //边的数目
	road** arcs;    //邻接矩阵
}Graph, * GH;

void CreatGraph(GH G);   //创建图
void Dijkstra(GH G, int s);     //寻找最短路径
int MIN(GH G, bool* flag, int* fatigue);     //寻找到某个结点疲劳度最小，且该结点未被选中
void showpath(int* path, int* fatigue, GH G, int s);  //输出路径

int main()
{
	GH G;
	G = (GH)malloc(sizeof(Graph));
	if (!G)
	{
		cout << "空间分配失败";
		exit(0);
	}
	CreatGraph(G);
	Dijkstra(G, 1);
	for (int i = 0; i < G->vexnum; i++)
	{
		free(G->arcs[i]);
	}
	free(G->arcs);
	free(G);
	system("pause");
	return 0;
}
//**************************************************************
void CreatGraph(GH G)
{
	fstream file;
	file.open(source, ios::in);
	if (file.fail())
	{
		cout << "文件打开失败";
		exit(0);
	}
	file >> G->vexnum;
	file >> G->arcnum;   //初始化顶点数和边数
	if (G->vexnum <= 0)
	{
		cout << 0;
		return;
	}
	G->arcs = (road**)malloc(G->vexnum * sizeof(road*));
	if (!G->arcs)
	{
		cout << "空间分配失败";
		exit(0);
	}
	int i, j;
	for (i = 0; i < G->vexnum; i++)
	{
		G->arcs[i] = (road*)malloc(G->vexnum * sizeof(road));
		if (!G->arcs[i])
		{
			cout << "空间分配失败";
			exit(0);
		}
	}
	for (i = 0; i < G->vexnum; i++)   //初始化邻接矩阵
	{
		for (j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j].length = MAX;
			G->arcs[i][j].type = 0;
		}
	}
	int k, t, len;
	for (k = 0; k < G->arcnum; k++)
	{
		file >> t >> i >> j >> len;   //读入数据
		G->arcs[i - 1][j - 1].length = len;
		G->arcs[j - 1][i - 1].length = len;
		G->arcs[i - 1][j - 1].type = t;
		G->arcs[j - 1][i - 1].type = t;
	}
	/*for (i = 0; i < G->vexnum; i++)
	{
		for (j = 0; j < G->vexnum; j++)
		{
			cout <<setw(10) <<G->arcs[i][j].length << "-" << G->arcs[i][j].type << "   ";
		}
		cout << endl;
	}*/
	file.close();
}
//**************************************************************
void Dijkstra(GH G, int s)
{
	int* path, * dist, * fatigue, * pre;
	bool *flag;   //定义辅助数组
	if (G->vexnum <= 0)
	{
		return;
	}
	if (s <= 0 || s > G->vexnum)
	{
		cout << "起始点信息不合法";
		return;
	}
	path = (int*)malloc(G->vexnum * sizeof(int));
	dist = (int*)malloc(G->vexnum * sizeof(int));
	fatigue = (int*)malloc(G->vexnum * sizeof(int));
	pre = (int*)malloc(G->vexnum * sizeof(int));  //记录走的上条路是不是小道
	flag = (bool*)malloc(G->vexnum * sizeof(bool));
	if (!path || !dist || !flag || !fatigue || !pre)
	{
		cout << "空间分配失败";
		exit(0);
	}
	int i, j;
	for (i = 0; i < G->vexnum; i++)    //初始化辅助数组
	{
		flag[i] = false;   //代表该点未加入最短路径点集
		dist[i] = G->arcs[s - 1][i].length;
		if (dist[i] < MAX)     //有路
		{
			if (G->arcs[s - 1][i].type == 1)   //小路
			{
				fatigue[i] = G->arcs[s - 1][i].length * G->arcs[s - 1][i].length;
				pre[i] = 1;
			}
			else
			{
				fatigue[i] = G->arcs[s - 1][i].length;
				pre[i] = 0;
			}
			path[i] = s - 1;
		}
		else
		{
			pre[i] = -1;
			path[i] = -1;
			fatigue[i] = MAX;
		}
	}
	/*for (i = 0; i < G->vexnum; i++)
	{
		cout << setw(3) << dist[i] << "*" << fatigue[i] << "*" << path[i] << "*" << pre[i] << endl;
	}*/

	flag[s - 1] = true;   //起始点设为被选中状态
	int sum = 0;    //记录总疲劳度
	int count = 0;  //记录连着走了多少小道
	   
	int k, minfati, temp;
	for (i = 0; i < G->vexnum; i++)
	{
		k = MIN(G, flag, fatigue);   ////寻找到某个结点疲劳度最小
		flag[k] = true;  //选中
		minfati = fatigue[k];
		sum += minfati;    //记录疲劳度
		for (j = 0; j < G->vexnum; j++)   //更新fatigue数组
		{
			if (flag[j] == false)
			{
				if (pre[k] == 1)   //走的小路到的k
				{
					count += dist[k];   //已经连续走的小路长度
					if (G->arcs[k][j].type == 1)   //从k到j为小路
					{
						temp = (count + G->arcs[k][j].length) * (count + G->arcs[k][j].length) - count * count;   //若选择这条路，疲劳度的增加量
						if (fatigue[j] > minfati + temp)    //j经过k到源点比原来更近
						{
							fatigue[j] = minfati + temp;
							path[j] = k;
							pre[j] = 1;
						}
					}
					else if (G->arcs[k][j].type == 0)  //大路
					{
						if (fatigue[j] > minfati + G->arcs[k][j].length)  //j经过k到源点比原来更近 
						{
							fatigue[j] = minfati + G->arcs[k][j].length;
							path[j] = k;
							pre[j] = 0;
						}
					}
				}
				else if(pre[k] == 0)  //走大路到的k
				{
					count = 0;  //连续小道数清零
					if (G->arcs[k][j].type == 1)   //从k到j为小路
					{
						temp = (G->arcs[k][j].length) * (G->arcs[k][j].length);   //若选择这条路，疲劳度的增加量
						if (fatigue[j] > minfati + temp)    //j经过k到源点比原来更近
						{
							fatigue[j] = minfati + temp;
							path[j] = k;
							pre[j] = 1;
						}
					}
					else if (G->arcs[k][j].type == 0)   //从k到j为大路
					{
						if (fatigue[j] > minfati + G->arcs[k][j].length)  //j经过k到源点比原来更近 
						{
							fatigue[j] = minfati + G->arcs[k][j].length;
							path[j] = k;
							pre[j] = 0;
						}
					}
				}
			}
		}
	}
	showpath(path, fatigue, G, s);
	free(dist);
	free(flag);
	free(path);
	free(fatigue);
	free(pre);
}
//**************************************************************
int MIN(GH G, bool* flag, int* fatigue)    //寻找到某个结点疲劳度最小，且该结点未被选中
{
	int mindex = 0, min = MAX;
	int i;
	
	for (i = 0; i < G->vexnum; i++)
	{
		if (fatigue[i] <= min && flag[i] == false)
		{
			min = fatigue[i];
			mindex = i;
		}
	}
	return mindex;
}
//**************************************************************
void showpath(int* path, int *fatigue, GH G, int s)
{
	int* Stack;
	int n = G->vexnum;
	if (n <= 0)
	{
		return;
	}
	Stack = (int*)malloc((n+1) * sizeof(int));
	if (!Stack)
	{
		cout << "空间分配失败";
		exit(0);
	}
	int top, i, p;
	top = -1;
	for (i = n-1; i >= 0; i--)
	{
		if (i != s - 1)
		{
			if (path[i] == s - 1)
			{
				cout << s << "号路口到" << i + 1 << "号路口的最优路线：\n";
				cout << s << "->" << i + 1 << "\n";
				cout << "疲劳值为：" << fatigue[i] << endl;;
			}
			else if (path[i] == -1)
			{
				cout << s << "号路口到" << i + 1 << "号路口无路径" << endl;
			}
			else
			{
				p = path[i];
				while (p != s - 1)
				{
					Stack[++top] = p;   //路径p入栈
					p = path[p];
				}
				cout << s << "号路口到" << i + 1 << "号路口的最优路线：\n";
				cout << s << "->";
				while (top > -1)
				{
					p = Stack[top--];   //路径出栈
					cout << p + 1 << "->";
				}
				cout << i + 1 << "\n";
				cout << "疲劳值为：" << fatigue[i] << endl;
			}
		}
	}
}
//**************************************************************