#include<iostream>
#include<fstream>
using namespace std;

#define FILEPATH "Common_Key.txt"    //文件路径
#define BORROW 1     //借钥匙
#define BACK 0       //还钥匙

typedef struct teacher
{
	int num;   //钥匙编号
	int start;  //拿走钥匙的时间
	int end;    //还钥匙的时间
	bool borrow;  //借标记位，用于排序，标记是否已进入事件队列
	bool back;    //还标记位，用于排序，标记是否已进入事件队列
}TCH;
typedef struct Event
{
	int type;    //类型：还 or 借
	int index;    //结构体数组TCH的下标
}Event;   //事件队列
int front = 0, rear = 0;   //事件队列头尾指针

void KeyBox(Event* Eve, TCH* Key, int* Box, int N);       //处理钥匙盒状态  
void EnQu(Event* Eve,int kind, int index);
void DeQu(Event* Eve, int& kind, int &index);
void Traverse(Event* Eve,TCH* Key)
{
	int i = front;
	for (; i < rear; i++)
	{
		if (Eve[i].type)
		{
			cout << "借" << Key[Eve[i].index].num << " ";
		}
		else
		{
			cout << "还" << Key[Eve[i].index].num << " ";
		}
	}
	cout << endl;
}

int main()
{
	fstream file;
	file.open(FILEPATH, ios::in);   //读文件
	if (file.fail())
	{
		cout << "文件打开失败" << endl;
		exit(0);
	}
	int K, N, i, j, time;    //time临时寄存使用时间
	TCH* Key;
	Event * Even;
	int* Box;
	file >> N >> K;
	Key = (TCH*)malloc(K * sizeof(TCH));
	if (K < 1)
	{
		return 0;
	}
	if (!Key)
	{
		cout << "空间分配失败" << endl;
		exit(0);
	}
	Even = (Event*)malloc((2*K+1) * sizeof(Event));   //事件队列
	if (!Even)
	{
		cout << "空间分配失败" << endl;
		exit(0);
	}
	Box = (int*)malloc(N * sizeof(int));    //代表钥匙盒
	if (N < 1)
	{
		return 0;
	}
	if (!Box)
	{
		cout << "空间分配失败" << endl;
		exit(0);
	}
	for (i = 0; i < N; i++)    //初始化钥匙盒状态
	{
		Box[i] = i + 1;
	}
	for (i = 0; i < K; i++)
	{
		file >> Key[i].num>>Key[i].start;
		file >> time;
		Key[i].end = Key[i].start + time;
		Key[i].borrow = false;
		Key[i].back = false;
	}
	
	int Fir_borrow, Fir_back, index1 = 0, index2 = 0;   //Fir_borrow,Fir_back分别记录最早借钥匙时间与还钥匙时间,index1,index2分别对应其结构体数组下标
	for (i = 0; i < 2 * K; i++)
	{
		Fir_borrow = INT_MAX;
		for (j = 0; j < K; j++)
		{
			if ((Key[j].start < Fir_borrow) && !(Key[j].borrow))   //此次借事件尚未加入队列
			{
				Fir_borrow = Key[j].start;
				index1 = j;
			}
		}

		Fir_back = INT_MAX;
		for (j = 0; j < K; j++)
		{
			if ((Key[j].end < Fir_back) && !(Key[j].back))   //此次还事件尚未加入队列
			{
				Fir_back = Key[j].end;
				index2 = j;
			}
			else if ((Key[j].end == Fir_back) && !(Key[j].back))
			{
				if (Key[j].num < Key[index2].num)   //选择钥匙编号小的
				{
					index2 = j;
				}
			}
		}

		if (Fir_back <= Fir_borrow)    //此时应该还钥匙
		{
			EnQu(Even, BACK, index2);
			Key[index2].back = true;   //标记
			Traverse(Even, Key);       //显示事件队列
		}
		else if (Fir_back > Fir_borrow)    //此时应该借钥匙
		{
			EnQu(Even, BORROW, index1);
			Key[index1].borrow = true;   //标记
			Traverse(Even, Key);       //显示事件队列
		}
	}
	KeyBox(Even, Key, Box, N);
	cout << "钥匙盒最终状态为：";
	for (i = 0; i < N; i++)
	{
		cout << Box[i] << " ";
	}
	cout << endl;
	file.close();
	free(Key);
	free(Box);
	free(Even);
	system("pause");
	return 0;
}

void EnQu(Event* Eve, int kind, int index)
{
	Eve[rear].type = kind;
	Eve[rear].index = index;
	rear++;
}
void DeQu(Event* Eve, int& kind, int& index)
{
	kind = Eve[front].type;
	index = Eve[front].index;
	front++;
}
void KeyBox(Event* Eve, TCH* Key, int* Box, int n)
{
	int type, index;
	int i;
	int num;   //此次操作的钥匙编号
	while (front < rear)
	{
		DeQu(Eve, type, index);
		if (type)    //拿钥匙
		{
			num = Key[index].num;
			for (i = 0; i < n; i++)
			{
				if (Box[i] == num)   //找到该钥匙
				{
					Box[i] = 0;   //代表该挂钩为空
					break;
				}
			}
			//cout << "时刻" << Key[index].start << "钥匙盒状态为：";
			cout << "当前钥匙盒状态为：\n";
			for (i = 0; i < n; i++)
			{
				if (Box[i] == 0)
				{
					cout << "X ";
				}
				else
				{
					cout << Box[i] << " ";
				}
			}
			cout << endl;
		}
		else   //还钥匙
		{
			for (i = 0; i < n; i++)
			{
				if (Box[i] == 0)   //找到最小的挂钩
				{
					Box[i] = Key[index].num;
					break;
				}
			}
			//cout << "时刻" << Key[index].end << "钥匙盒状态为：";
			cout << "当前钥匙盒状态为：\n";
			for (i = 0; i < n; i++)
			{
				if (Box[i] == 0)
				{
					cout << "X ";
				}
				else
				{
					cout << Box[i]<<" ";
				}
			}
			cout << endl;
		}
	}
}