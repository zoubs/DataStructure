#include<iostream>
#include<fstream>

using namespace std;

//#define source "pyq.txt"
//并查集的思想，将所有是朋友的连在一棵树上即可
int find(int x, int* fa);   //返回x的跟集

int main()
{
	int stu, club, i, j, k, a, b;
	cin >> stu >> club;
	int* ST, * pyq;
	if (stu <= 0)
	{
		cout << 0;
		return 0;
	}
	ST = (int*)malloc(stu * sizeof(int));   //构造并查集
	if (!ST)
	{
		cout << "空间分配失败";
		exit(0);
	}
	pyq = (int*)malloc(stu * sizeof(int));   //统计朋友圈点集的个数
	if (!pyq)
	{
		cout << "空间分配失败";
		exit(0);
	}
	for (i = 0; i < stu; i++)   //初始化并查集
	{
		ST[i] = i;
		pyq[i] = 1;
	}
	for (j = 0; j < club; j++)
	{
		cin >> k;  //该俱乐部人数
		if (k > 0)
		{
			cin >> a;
			for (i = 1; i < k; i++)
			{
				int x, y;
				cin >> b;
				x = find(a - 1, ST);
				y = find(b - 1, ST);
				if (x != y)
				{
					if (pyq[x] > pyq[y])    //为使树组织的层数最低，将层数低的插入到层数高的树
					{
						ST[y] = x;
						pyq[x] += pyq[y];
					}
					else
					{
						ST[x] = y;
						pyq[y] += pyq[x];
					}
				}
			}
		}
	}
	int t = pyq[0];
	for (i = 1; i < stu; i++)
	{
		if (t < pyq[i])
		{
			t = pyq[i];
		}
	}
	cout << t;
	free(ST);
	free(pyq);
	cout << endl;
	system("pause");
	return 0;
}

int find(int x, int* fa)  //返回x的根集
{
	if (fa[x] != x)
	{
		fa[x] = find(fa[x], fa);
	}
	return fa[x];
}