#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

#define source "maze.txt"

#define N 100
int min = N;
int row, col;   //迷宫的行列

typedef struct
{
	int i;
	int j;
	int de;
}PA;

int** creatmaze();      //创建迷宫
void showpath(PA* p, int n);     //显示路径
void maze(int** mg, int x1, int y1, int x2, int y2, PA* p, PA* t);         //非递归算法

int main()
{
	int** mg;
	mg = creatmaze();
	PA p[N + 1];
	PA t[N + 1];
	int  start_x, start_y, end_x, end_y;
	cout << "请输入迷宫的入口坐标(坐标从1开始)：";
	cin >> start_x >> start_y;
	cout << "请输入迷宫的出口坐标(坐标从1开始)：";
	cin >> end_x >> end_y;
	if (start_x > row || start_y > col || end_x > row || start_y > col)
	{
		cout << "输入的坐标不合法";
		exit(0);
	}
	maze(mg, start_x, start_y, end_x, end_y, p, t);
	free(mg);
	system("pause");
	return 0;
}

//*****************************************************************
int** creatmaze()
{
	fstream file;
	file.open(source, ios::in);
	if (file.fail())
	{
		cout << "文件打开失败";
		exit(0);
	}
	int i, j;
	//file >> row >> col;   //读行列
	row = 10;
	col = 10;
	if (row <= 0 || col <= 0)
	{
		exit(0);
	}
	int** mg;
	mg = (int**)malloc(row * sizeof(int*));
	if (!mg)
	{
		cout << "空间分配失败";
		exit(0);
	}
	for (i = 0; i < row; i++)
	{
		mg[i] = (int*)malloc(col * sizeof(int));
		if (!mg[i])
		{
			cout << "空间分配失败";
			exit(0);
		}
		for (j = 0; j < col; j++)
		{
			file>>mg[i][j];
		}
	}
	return mg;
}
//*****************************************************************
void showpath(PA* p, int n)
{
	int k;
	for (k = 1; k <= n; k++)
	{
		cout << "<" << p[k].i << "," << p[k].j << ">";
	}
	cout << endl;
}
//*****************************************************************
void maze(int** mg, int x1, int y1, int x2, int y2, PA* p, PA* t)
{
	int top = 1;
	int de;
	int sum = 0;
	int i, j, k;
	t[top].i = x1;
	t[top].j = y1;
	t[top].de = 0;
	mg[t[top].i][t[top].j] = 1;
	cout << endl <<"迷宫结果如下：" << endl;
	while (t[1].de <= 4)
	{
		de = t[top].de;
		de++;
		if (t[top].i == x2 && t[top].j == y2)
		{
			showpath(t, top);
			if (top + 1 < min) 
			{       //比较输出最短路径
				for (k = 0; k <= top; k++)
				{
					p[k] = t[k];
				}
				min = top + 1;
			}
			sum++;
			mg[t[top].i][t[top].j] = 0;
			top--;
			i = t[top].i;
			j = t[top].j; 
			de = t[top].de;
		}
		else
		{
			for (; de <= 4; de++)
			{
				switch (de)
				{
				case 1:
					i = t[top].i;  
					j = t[top].j + 1;
					break;
				case 2:
					i = t[top].i + 1; 
					j = t[top].j; 
					break;
				case 3:
					i = t[top].i;  
					j = t[top].j - 1; 
					break;
				case 4:
					i = t[top].i - 1;
					j = t[top].j; 
					break;
				}
				if (mg[i][j] == 0) 
				{
					break; 
				}
			}
			if (de <= 4)
			{
				mg[i][j] = 1;
				t[top].de = de;
				top++;
				t[top].i = i;
				t[top].j = j;
				t[top].de = 0;
			}
			else
			{
				mg[t[top].i][t[top].j] = 0;
				if (top > 1)
				{
					top--;
				}
				else
				{
					break;
				}
			}
		}
	}
	cout << "共有" << sum << "条可行路径\n";
	if (sum)
	{
		cout << "最短路径的长度:  " << min << endl;
		cout << "最短路径如下:";
		for (k = 1; k < min; k++)
		{
			cout << "<" << p[k].i << "," << p[k].j << ">";
		}
		cout << endl;
	}
}
//*****************************************************************