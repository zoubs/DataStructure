#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;
#define max 100

int* creatarr(int& n);   //创建数组
void copyarr(int* a, int* b, int n);   //拷贝数组
void printarr(int* a, int n);  //输出数组
void HeapSort(int* a, int n);  //堆排序
void QuickSort(int* a, int low, int high);    //快速排序
void MSort(int* SR, int* TR1, int s, int t);  //二路归并排序
void ShellSort(int* a, int n, int* dlta, int len); //希尔排序
void Insert(int* a, int n);   //插入排序
void Select(int* a, int n);   //选择排序
void nop(int* a, int n);      //冒泡排序

//******************************************************************
int main()
{
	int* a, *b;
	int n = 0;   //数组长度
	int dlta[3] = { 5,3,1 };
	b = creatarr(n);
	cout << "原数组如下：\n";
	printarr(b, n);

	a = new int[n];
	if (!a)
	{
		cout << "空间分配失败";
		exit(0);
	}

	copyarr(a, b, n);
	Select(a, n);
	cout << "选择排序结果如下：\n";
	printarr(a, n);

	copyarr(a, b, n);
	nop(a, n);
	cout << "冒泡排序结果如下：\n";
	printarr(a, n);

	copyarr(a, b, n);
	Insert(a, n);
	cout << "插入排序结果如下：\n";
	printarr(a, n);

	copyarr(a, b, n);
	ShellSort(a, n, dlta, 3);
	cout << "希尔排序结果如下：\n";
	printarr(a, n);

	copyarr(a, b, n);
	MSort(a, a, 0, n - 1);
	cout << "归并排序结果如下：\n";
	printarr(a, n);

	copyarr(a, b, n);
	QuickSort(a, 0, n - 1);
	cout << "快速排序结果如下：\n";
	printarr(a, n);

	copyarr(a, b, n);
	HeapSort(a, n - 1);
	cout << "堆排序结果如下：\n";
	printarr(a, n);
	//7 6 5 4 3 2 1
	system("pause");
}
//******************************************************************
void nop(int* a, int n)   //冒泡排序
{
	int i, j, count, sumcmp = 0, sumswap = 0;
	for (i = 0; i < n-1; i++)
	{
		count = 0; //记录每次冒泡交换次数
		for (j = 0; j < n-i-1; j++)
		{
			sumcmp++;
			if (a[j] > a[j + 1])
			{
				sumswap++;
				swap(a[j], a[j + 1]);
				count++;
				
			}
		}
		if (count == 0)
		{
			break;
		}
	}
}
//******************************************************************
void Select(int* a, int n)  //选择排序
{
	int i, j, min, count = 0, sum = 0;   //count交换次数，sum比较次数
	for (i = 0; i < n; i++)
	{
		for (min = i, j = i; j < n; j++)
		{
			sum++;
			if (a[j] < a[min])
			{
				min = j;
			}
		}
		count++;
		swap(a[i], a[min]);
	}
}
//******************************************************************
void Insert(int* a, int n)  //插入排序
{
	int i, j, temp, kcn = 0, rmn = 0;   //lcn比较次数，rmn移动次数
	for (i = 1; i < n; i++)
	{
		kcn++;
		if (a[i] < a[i - 1])   //没有逆序，不插入
		{
			temp = a[i];
			a[i] = a[i - 1];
			rmn += 2;
			for (j = i - 2; j > -1; j--)
			{
				kcn++;
				if (temp >= a[j])
				{
					break;
				}
				else
				{
					rmn++;
					a[j + 1] = a[j];
				}
			}
			a[j + 1] = temp;
			rmn++;
		}
	}
}
//******************************************************************
void ShellInsert(int* a, int dk, int n)
{
	int i, j, temp, kcn = 0, rmn = 0;
	for (i = dk; i < n; i++)
	{
		kcn++;
		if (a[i] < a[i - dk])    //说明出现逆序
		{
			temp = a[i];   //暂存
			a[i] = a[i - dk];
			rmn += 2;
			for (j = i - 2*dk; j >= 0; j -= dk)  //找位置
			{
				kcn++;
				if (temp < a[j])
				{
					a[j + dk] = a[j];
				}
				else
				{
					break;
				}
			}
			rmn++;
			a[j + dk] = temp;
		}
	}
}
void ShellSort(int* a, int n, int* dlta, int len)   //dlta为增量数组，len为其长度
{
	int i;
	for (i = 0; i < len; i++)
	{
		ShellInsert(a, dlta[i], n);
	}
}
//******************************************************************
void Merge(int* SR, int*& TR, int i, int m, int n)   //将有序的SR[i...m]和SR[m+1...n]归并为有序的TR[i...n]
{
	int j, k;
	for (j = m + 1, k = i; i <= m && j <= n; k++)    //将SR中元素，从小到大并入TR中
	{
		if (SR[i] <= SR[j])
		{
			TR[k] = SR[i++];
		}
		else
		{
			TR[k] = SR[j++];
		}
	}
	if (i <= m)  //SR[i...m]剩余
	{
		for (; k <= n; k++)
		{
			TR[k] = SR[i++];
		}
	}
	if (j <= n)   //SR[m + 1...n]剩余
	{
		for (; k <= n; k++)
		{
			TR[k] = SR[j++];
		}
	}
}
void MSort(int* SR, int* TR1, int s, int t)
{
	int m;
	int TR2[max];
	if (s == t)
	{
		TR1[s] = SR[s];
	}
	else
	{
		m = (s + t) / 2;
		MSort(SR, TR2, s, m);
		MSort(SR, TR2, m + 1, t);
		Merge(TR2, TR1, s, m, t);
	}
}
//******************************************************************
int Partition(int* a, int low, int high)    //交换数组中子表r[low...high]的记录，使枢轴记录到位，并返回其位置
{
	int i = low, j = high;
	int pivot = a[low];
	while (j!=i)
	{
		while (i < j && a[j] >= pivot)
		{
			j--;
		}
		if (i < j)
		{
			a[i++] = a[j];
		}
		while (i < j && a[i] <= pivot)
		{
			i++;
		}
		if (i < j)
		{
			a[j--] = a[i];
		}
	}
	a[i] = pivot;
	return i;
}
void QuickSort(int* a, int low, int high)     //对数组a子序列a[low...high]进行快速排序
{
	int pivotloc;
	if (low < high)
	{
		pivotloc = Partition(a, low, high);
		QuickSort(a, low, pivotloc - 1);
		QuickSort(a, pivotloc + 1, high);
	}
}
//******************************************************************
void HeapAdjust(int* a, int s, int m)      //已知a[s...m]中的关键字除a[s]之外均满足堆的定义
{
	int temp = a[s];
	int j;
	for (j = 2 * s; j <= m; j *= 2)
	{
		if (j < m && a[j] <a[j+1])
		{
			j++;
		}
		if (temp >= a[j])  //已经是大顶堆
		{
			break;
		}
		a[s] = a[j];
		s = j;
	}
	a[s] = temp;
}
void HeapSort(int* a, int n)
{
	int i;
	for (i = n / 2; i >= 0; i--)   //把a[0...n]建成大顶堆
	{
		HeapAdjust(a, i, n);
	}
	//printarr(a, n + 1);
	for (i = n; i > 0; i--)
	{
		swap(a[0], a[i]);
		HeapAdjust(a, 0, i - 1);
	}
}
//******************************************************************
void printarr(int* a, int n)
{
	int i;
	if (n == 0)
	{
		cout << "数组为空";
	}
	for (i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
//******************************************************************
int* creatarr( int &n)
{
	int* a;
	int i;
	cout << "请输入数组元素个数：";
	cin >> n;
	a = new int[n];
	if (!a)
	{
		cout << "空间分配失败";
		exit(0);
	}
	cout << "请依次输入元素：\n";
	for (i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	return a;
}
//******************************************************************
void copyarr(int* a, int* b, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		a[i] = b[i];
	}
}
//******************************************************************

