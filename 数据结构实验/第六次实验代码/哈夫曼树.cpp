#include<iostream>
using namespace std;

typedef struct
{
	 int weight;
	 int parent, lchild, rchild;
}HTNode,*HufTree;
typedef char** HuffmanCode;

void Select(HufTree HT, int i, int &s1, int &s2)
{//在1~i-1单元中，选择parent为0且weight最小的两个结点
	int j;
	int mindex1 = 0, mindex2 = 0;
	HT[0].weight = 999;
	for (j = 1; j <= i - 1; j++)
	{
		if (HT[j].parent == 0)
		{
			if (HT[mindex1].weight > HT[j].weight)
			{
				mindex1 = j;
			}
		}
	}
	for (j = 1; j <= i - 1; j++)
	{
		if (HT[j].parent == 0)
		{
			if ((HT[mindex2].weight > HT[j].weight) && (j != mindex1))
			{
				mindex2 = j;
			}
		}
	}
	s1 = mindex1;
	s2 = mindex2;
}
void HufCode(int n, int* w, HufTree &HT, HuffmanCode &HC)
{
	//n表示叶结点数量
	//w是用来存放叶结点权值的一维数组名
	//HT用来表示存储哈夫曼树的一维数组名
	//HC是用来存储哈夫曼编码的码表
	int m,i;
	int s1, s2, start, c, f;
	char* cd;
	HufTree p;
	if (n <= 1)
	{//只有一个节点，直接返回
		return;
	}
	m = 2 * n - 1;
	HT = (HufTree)malloc((m+1) * sizeof(HTNode));   //0号单元未用
	if (HT == NULL)
	{
		cout << "空间分配失败";
		exit(0);
	}
	for (i = 1; i <= n; i++)
	{
		HT[i].weight = w[i-1];
		HT[i].lchild = 0;
		HT[i].rchild = 0;
		HT[i].parent = 0;
	}
	for (; i <= m; i++)
	{
		HT[i] = { 0,0,0,0 };
	}
	
	for (i = n + 1; i <= m; i++)   //建哈夫曼树
	{
		Select(HT, i, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//从叶子到根逆向求每个字符的编码
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));   //分配n个字符编码的头向量
	if (HC == NULL)
	{
		cout << "空间分配失败";
		exit(0);
	}
	cd = (char*)malloc(n * sizeof(char));  //求编码的工作空间
	if (cd == NULL)
	{
		cout << "空间分配失败";
		exit(0);
	}
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++)
	{
		start = n - 1;   //编码结束符位置
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if (HT[f].lchild == c)
			{
				start--;
				cd[start] = '0';
			}
			else
			{
				start--;
				cd[start] = '1';
			}
			
		}	
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		if (HC[i] == NULL)
		{
			printf("空间分配失败");
			exit(0);
		}
		strcpy_s(HC[i], n-start, &cd[start]);
	}
	free(cd);
}
int main()
{
	int n, i;
	int w[100];
	HuffmanCode HC;
	HufTree HT;
	cout << "请输入叶子节点数：";
	cin >> n;
	
	cout << "请依次输入各个结点权值（空格隔开）：";
	for (i = 0; i < n; i++)
	{
		cin >> w[i];
	}
	if (n == 1)
	{
		cout << "只有一个结点，其编码为：0" << endl;
		return 0;
	}
	else if (n > 1)
	{
		HufCode(n, w, HT, HC);
		for (i = 1; i <= n; i++)
		{
			cout << "第" << i << "个结点哈夫曼编码为：" << HC[i] << endl;
		}
		return 0;
	}
}