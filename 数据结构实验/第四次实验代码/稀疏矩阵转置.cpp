#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
typedef int Status;
typedef int ElemType;
typedef struct
{
	int i, j;
	ElemType e;
}Triple;
typedef struct
{
	Triple data[MaxSize + 1];     //data[0]未用
	int mu, nu, tu;               //行数、列数、非零元个数
}TSMatrix;
Status TranspaseSMatrix(TSMatrix M, TSMatrix& T)
{   //稀疏矩阵转置函数
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	int col, p, q;
	if (T.tu)
	{
		q = 1;
		for (col = 1; col <= M.nu; col++)
		{
			for (p = 1; p <= M.tu; p++)
			{
				if (M.data[p].j == col)
				{
					T.data[q].i = M.data[p].j;
					T.data[q].j = M.data[p].i;
					T.data[q].e = M.data[p].e;
					q++;
				}
			}
		}
		return OK;
	}
	else
	{
		printf("三元组为空\n");
		return FALSE;
	}
}
Status main()
{
	int k = 0;
	TSMatrix M, T;
	printf("请依次输入稀疏矩阵的行数、列数、非零元个数：");
	scanf_s("%d %d %d", &M.mu, &M.nu, &M.tu);
	printf("请依次输入矩阵的非零元（行，列，元素值  用空格隔开）：\n");
	for (k = 1; k <= M.tu; k++)
	{
		scanf_s("%d %d %d", &M.data[k].i, &M.data[k].j, &M.data[k].e);
	}
	TranspaseSMatrix(M, T);
	printf("转置后的稀疏矩阵为：\n");
	for (k = 1; k <= M.tu; k++)
	{
		printf("%d %d %d\n", T.data[k].i, T.data[k].j, T.data[k].e);
	}
	return OK;
}