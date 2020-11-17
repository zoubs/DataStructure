#include<iostream>
#include<ctime>
#include<fstream>
using namespace std;

#define test0 "test0.txt"
#define test1 "test1.txt"
#define test2 "test2.txt"
#define test3 "test3.txt"
#define test4 "test4.txt"
#define test5 "test5.txt"
#define test6 "test6.txt"
#define test7 "test7.txt"
#define test8 "test8.txt"
#define test9 "test9.txt"
#define max 20000

int TR2[max];
typedef struct Node
{
	int data;
	struct Node* next;
}Node;
string Source[10] = { 
					"test0.txt",
					"test1.txt",
					"test2.txt",
					"test3.txt",
					"test4.txt",
					"test5.txt",
					"test6.txt",
					"test7.txt",
					"test8.txt",
					"test9.txt" 
};
void CreatSource();   //生成10个随机样本
int* creatarr(int& n, fstream& file);   //创建数组
void copyarr(int* a, int* b, int n);   //拷贝数组
void printarr(int* a, int n);  //输出数组
void HeapSort(int* a, int n);  //堆排序
void QuickSort(int* a, int low, int high);    //快速排序
void MSort(int* SR, int* TR1, int s, int t);  //二路归并排序
void ShellSort(int* a, int n, int* dlta, int len); //希尔排序
void Insert(int* a, int n);   //插入排序
void Select(int* a, int n);   //选择排序
void nop(int* a, int n);      //冒泡排序
void Radix_Sort(int* L, int n);  //基数排序

int main()
{
	//CreatSource();
	fstream file;
	int* arr[10], *b;
	int dlta[5] = { 9,5,3,2,1 };
	b = new int[20000];
	if (!b)
	{
		cout << "空间分配失败";
		exit(0);
	}
	clock_t start, end;  //记录运行时间
	int i, j, n;
	n = 20000;
	for (i = 0; i < 10; i++) //读出十个样本中的数据
	{
		file.open(Source[i], ios::in);
		if (file.fail())
		{
			cout << "文件打开失败";
			exit(0);
		}
		arr[i] = creatarr(n, file);
		file.close();
	}
	
	cout << "冒泡排序耗时:" << endl;
	for (i = 0; i < 10; i++)
	{
		copyarr(b, arr[i], n);
		start = clock();
		nop(b, n);
		end = clock();
		cout << "样本" << i+1 << ": " << (end - start) << " ms" << endl;
	}
	
	cout << "选择排序耗时:" << endl;
	for (i = 0; i < 10; i++)
	{
		copyarr(b, arr[i], n);
		start = clock();
		Select(b, n);
		end = clock();
		cout << "样本" << i + 1 << ": " << (end - start) << " ms" << endl;
	}
	
	cout << "插入排序耗时:" << endl;
	for (i = 0; i < 10; i++)
	{
		copyarr(b, arr[i], n);
		start = clock();
		Insert(b, n);
		end = clock();
		cout << "样本" << i + 1 << ": " << (end - start) << " ms" << endl;
	}
	
	cout << "希尔排序耗时:" << endl;
	for (i = 0; i < 10; i++)
	{
		copyarr(b, arr[i], n);
		start = clock();
		ShellSort(b, n, dlta, 5);
		end = clock();
		cout << "样本" << i + 1 << ": " << (end - start) << " ms" << endl;
	}
	
	cout << "二路归并排序耗时:" << endl;
	for (i = 0; i < 10; i++)
	{
		copyarr(b, arr[i], n);
		start = clock();
		MSort(b, TR2, 0, n - 1);
		end = clock();
		cout << "样本" << i + 1 << ": " << (end - start) << " ms" << endl;
	}
	
	cout << "快速排序耗时:" << endl;
	for (i = 0; i < 10; i++)
	{
		copyarr(b, arr[i], n);
		start = clock();
		QuickSort(b, 0, n-1);
		end = clock();
		cout << "样本" << i + 1 << ": " << (end - start) << " ms" << endl;
	}
	
	cout << "堆排序耗时:" << endl;
	for (i = 0; i < 10; i++)
	{
		copyarr(b, arr[i], n);
		start = clock();
		HeapSort(b, n - 1);
		end = clock();
		cout << "样本" << i + 1 << ": " << (end - start) << " ms" << endl;
	}
	
	cout << "基数排序耗时:" << endl;
	for (i = 0; i < 10; i++)
	{
		copyarr(b, arr[i], n);
		start = clock();
		Radix_Sort(b, n);
		end = clock();
		cout << "样本" << i + 1 << ": " << (end - start) << " ms" << endl;
	}
	system("pause");
	return 0;
}

//******************************************************************
void CreatSource()
{
	fstream file;
	int j, a;
	/*for (i = 0; i < 10; i++)   //10个样本
	{
		file.open(test[i], ios::out);
		if (file.fail())
		{
			cout << "文件打开失败";
			exit(0);
		}
		srand(time(0));
		for (j = 0; j < 20000; j++)
		{
			a = rand() % 20000;
			file << a << " ";
		}
		file.close();
	}*/
	file.open(test1, ios::out);
	if (file.fail())
	{
		cout << "文件打开失败";
		exit(0);
	}
	srand(time(0));
	for (j = 19999; j>=0; j--)
	{
		a = rand() % 20000;
		file << a << " ";
	}
	file.close();
}
//******************************************************************
void nop(int* a, int n)   //冒泡排序
{
	int i, j, count, sumcmp = 0, sumswap = 0;
	for (i = 0; i < n - 1; i++)
	{
		count = 0; //记录每次冒泡交换次数
		for (j = 0; j < n - i - 1; j++)
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
			for (j = i - 2 * dk; j >= 0; j -= dk)  //找位置
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
	while (j != i)
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
		if (j < m && a[j] < a[j + 1])
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
int* creatarr(int& n,fstream& file)
{
	int* a;
	int i;
	a = new int[n];
	if (!a)
	{
		cout << "空间分配失败";
		exit(0);
	}
	for (i = 0; i < n; i++)
	{
		file >> a[i];
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
int GetData(int data, int n)    //获得data的第i位的值
{
	int i = 1;
	if (n == 1)
		data = data % 10;
	else
	{
		for (i; i <= n - 1; i++)
		{
			data = data / 10;
		}
		data = data % 10;
	}
	return data;
}
//******************************************************************
void Radix_Sort(int* L, int n)   //基数排序
{
	int i, mod, times = 5, t = 0, k = 1;
	Node* head[10], * rear[10], * temp;   //基数链头、尾指针
	for (i = 0; i < 10; i++)
	{
		head[i] = new Node;
		head[i]->data = 0;
		head[i]->next = NULL;
		rear[i] = head[i];
	}
	while (k <= times)
	{
		for (i = 0; i < n; i++)    //分配
		{
			//head[i]->data = 1;
			mod = GetData(L[i], k);
			temp = new Node;
			temp->data = L[i];
			temp->next = rear[mod]->next;
			rear[mod]->next = temp;
			rear[mod] = rear[mod]->next;
		}
		t = 0;
		for (i = 0; i < 10; i++)   //回收
		{

			temp = head[i]->next;
			while (temp)
			{
				L[t++] = temp->data;
				temp = temp->next;
			}
			temp = head[i]->next;
			while (temp)
			{
				head[i]->next = temp->next;
				delete temp;
				temp = head[i]->next;
			}
			rear[i] = head[i];
		}
		k++;
	}
}
//******************************************************************