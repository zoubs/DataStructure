#include<iostream>
#include<iomanip>
using namespace std;
int main() 
{
	int m, n,flag = 0;
	cout<<"请输入矩阵行数和列数：";
	cin >> m >> n;
	int T[10][10];
	int F[10][10] = { 0 };
	int i, j, k, min, max;
	cout<<"请依次输入元素："<<endl;
	for (i = 0; i < m; i++) 
	{
		for (k = 0; k < n; k++) 
		{
			cin >> T[i][k];
		}
	}
	for (i = 0; i < m; i++)
	{
		for (k = 0; k < n; k++)
		{
			cout<<setw(5)<<left<< T[i][k];
		}
		cout << endl;
	}

	/*
	判断矩阵的鞍点,不清楚鞍点准确的定义，比如
	1 1 1
	1 1 1
	1 1 1
	我是按所有元素都是鞍点输出的
	*/
	for (i = 0; i < m; i++)   //找行最小值并标记
	{
		min = T[i][0];
		for (j = 0; j < n; j++)
		{
			if (min > T[i][j])
			{
				min = T[i][j];
			}
		}
		for (j = 0; j < n; j++)
		{
			if (min == T[i][j])
			{
				F[i][j] = 1;
			}
		}
	}
	for (i = 0; i < n; i++)    ////找列最大值，并清空非列最大值的标记
	{
		max = T[0][i];
		for (j = 0; j < m; j++)
		{
			if (max < T[j][i])
			{
				max = T[j][i];
			}
		}
		for (j = 0; j < m; j++)
		{
			if (max != T[j][i])
			{
				F[j][i] = 0;
			}
		}
	}
	for (i = 0; i < m; i++)
	{
		for (k = 0; k < n; k++)
		{
			cout << setw(5) << left << F[i][k];
		}
		cout << endl;
	}
	for (i = 0; i < m; i++) 
	{
		for (k = 0; k < n; k++)
		{
			if (F[i][k] == 1)
			{
				flag = 1;
				cout << "第" << i + 1 << "行第" << k + 1 << "列是鞍点，值为：" << T[i][k] << endl;
			}
		}
	}
	if (flag == 0)
	{
		cout << "该矩阵没有鞍点";
	}
	return 0;
}