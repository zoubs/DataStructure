#include<iostream>
#include<fstream>
#include<string>

using namespace std;
#define INPUT_FILEPATH "source.txt"  //输入文件地址
#define HUFFMAN "Huffman.txt"    //编码表地址
#define HCODE "Hcode.txt"    //按字符编码文件地址
#define Code "code.dat"       //按位编码的文件
#define recode "recode.txt"   //解码后的文件

#define Stack_Init_Size  200
#define STACKINCREMENT   100

typedef struct
{
	char ch;    //代表字符信息
	int weight;
	int parent, lchild, rchild;
}HTNode, * HufTree;

int sum = 0;   //用0/1字符编码的总字符数
int freq[256] = {0};

typedef char** HuffmanCode;

typedef struct
{
	char* base;   // 栈底指针
	char* top;    // 栈顶指针
	int stacksize;    //当前已分配的存储空间，以SElemType为单位
}SqStack, *Stack;

void Select(HufTree HT, int i, int& s1, int& s2);
void HufCode(int n, int* w, HufTree& HT, HuffmanCode& HC);
void readfile();   //读输入文件统计各个字符的频率
int GetNum();    //统计叶节点数量
void GetHCode(HuffmanCode HC,HufTree HT, int n);    //得到文章初步编码文件
void storebit(HuffmanCode HC);   //转化为二进制bit;
void Recode(HuffmanCode HC, HufTree HT, int n);   //对编码后的文件解码
void InitStack(Stack S); //构造一个空栈
void Push(Stack S, char e);//压栈
void ClearStack(Stack S);  //清空栈

int main()
{
	int n;
	int w[100];
	HuffmanCode HC;
	HufTree HT;
	//cout << sizeof(bool);
	readfile();
	n = GetNum();
	HufCode(n, w, HT, HC);
	GetHCode(HC, HT, n);
	storebit(HC);
	Recode(HC, HT, n);
	free(HT);
	free(HC);
	system("pause");

	return 0;
}
//********************************************************************
void Select(HufTree HT, int i, int& s1, int& s2)
{//在1~i-1单元中，选择parent为0且weight最小的两个结点
	int j;
	int mindex1 = 0, mindex2 = 0;
	HT[0].weight = INT_MAX;
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
//********************************************************************
void HufCode(int n, int* w, HufTree& HT, HuffmanCode& HC)
{
	//n表示叶结点数量
	//w是用来存放叶结点权值的一维数组名
	//HT用来表示存储哈夫曼树的一维数组名
	//HC是用来存储哈夫曼编码的码表
	fstream file;
	int m, i, j;
	int s1, s2, start, c, f;
	char* cd;
	file.open(HUFFMAN, ios::out);
	if (file.fail())
	{
		cout << "文件打开失败";
		exit(0);
	}
	if (n == 0)
	{//无节点，直接返回
		
		return;
	}
	m = 2 * n - 1;
	HT = (HufTree)malloc((m + 1) * sizeof(HTNode));   //0号单元未用
	if (HT == NULL)
	{
		cout << "空间分配失败";
		exit(0);
	}
	for (i = 0, j = 1; i < 256; i++)
	{
		if (freq[i] != 0)
		{
			HT[j].weight = freq[i];   //初始化权重
			HT[j].ch = i;             //初始化顶点信息
			HT[j].lchild = 0;
			HT[j].rchild = 0;
			HT[j].parent = 0;
			j++;
		}
	}
	
	file << "字符\t" << "频率\t" <<"编码" << endl;
	if (n == 1)
	{
		file << HT[1].ch << "\t" << freq[(int)HT[1].ch] << "\t0" << endl;
		return ;
	}
	for (j = n + 1; j <= m; j++)
	{
		HT[j] = { 0,0,0,0,0 };
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
	cd = (char *)malloc(n * sizeof(char));  //求编码的工作空间
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
		HC[i] = (char *)malloc((n - start) * sizeof(char));
		if (HC[i] == NULL)
		{
			printf("空间分配失败");
			exit(0);
		}
		strcpy_s(HC[i], n - start, &cd[start]);
	}
	
	for (i = 1; i <= n; i++)
	{
		file << HT[i].ch << "\t" << HT[i].weight<<"\t" <<HC[i] << endl;
	}


	free(cd);
}
//********************************************************************
void readfile()
{
	fstream file;
	char ch = 0;
	file.open(INPUT_FILEPATH, ios::in);
	if (file.fail())
	{
		cout << "文件打开失败";
		exit(0);
	}
	file.unsetf(ios::skipws);   //忽略默认的不读空白字符
	while (1)   //读到文件结束
	{
		file>>ch;
		if (file.eof())
		{
			break;
		}
		freq[(int)ch]++;
	}
	file.close();
}
//********************************************************************
int GetNum()
{
	int n = 0;
	for (int i = 0; i < 256; i++)
	{
		if (freq[i] != 0)   //说明该字符存在
		{
			n++;
		}
	}
	return n;
}
//********************************************************************
void GetHCode(HuffmanCode HC,HufTree HT, int n)
{
	fstream filein,fileout;
	char ch;
	int i;
	filein.open(INPUT_FILEPATH, ios::in);
	if (filein.fail())
	{
		cout << "文件打开失败";
		exit(0);
	}
	fileout.open(HCODE, ios::out);
	if (fileout.fail())
	{
		cout << "文件打开失败";
		exit(0);
	}
	filein.unsetf(ios::skipws);   //忽略默认的不读空格换行
	while (1)    //读文件
	{
		filein >> ch;
		if (filein.eof())  //最后一个是多读的，不应该处理
		{
			break;
		}
		for (i = 1; i <= n; i++)
		{
			if (ch == HT[i].ch)
			{
				sum += strlen(HC[i]);
				fileout << HC[i];
				break;
			}
		}
	}
	filein.close();
	fileout.close();
}
//********************************************************************
void storebit(HuffmanCode HC)
{
	fstream fin, fout;
	fin.open(HCODE, ios::in);
	if (fin.fail())
	{
		cout << "文件打开失败";
		exit(0);
	}
	fout.open(Code, ios::out|ios::binary);   //二进制方式写文件
	if (fout.fail())
	{
		cout << "文件打开失败";
		exit(0);
	}
	char c = '\0';
	//char d = ' ';
	char ch;
	int count = 0;
	while (1)
	{
		fin >> ch;  //读一个字符
		if (fin.eof())   
		{
			break;
		}
		count++;
		if (ch == '1')
		{
			c = (c << 1) | 1;
		}
		else
		{
			c = c << 1;
		}
		if (count == 8)   //读8个字符0/1写一个字节
		{
			count = 0;
			fout.write(&c, sizeof(char));
			c = '\0';
		}
	}
	if (count > 0)   //说明有剩下的字符0/1，另外处理
	{
		fout.write(&c, sizeof(char));
	}
	fin.close();
	fout.close();
}
//********************************************************************
void Recode(HuffmanCode HC, HufTree HT, int n)
{
	fstream fout,fin;
	fout.open(recode, ios::out);
	if (fout.fail())
	{
		cout << "文件打开失败";
		exit(0);
	}
	fin.open(Code, ios::in | ios::binary);   //编码文件为二进制文件
	if (fin.fail())
	{
		cout << "文件打开失败";
		exit(0);
	}
	char c, d;
	char a;
	int i;
	int tag;   //区分二进制编码文件是奇数字节还是偶数字节
	int r = sum & 7;    //即r = sum % 8，代表剩余的一个字节有效的位为低r位
	int count = 8;
	Stack S;
	S = (Stack)malloc(sizeof(SqStack));
	if (!S)
	{
		cout << "文件打开失败";
		exit(0);
	}
	InitStack(S);
	fin.read(&c, sizeof(char));   //先读一个字节

	//最后一个字节的8位的低位可能有非编码的0，因为用字符0/1编码得到的字符个数不一定是8的倍数
	//最后一个字节单独处理
	while (!fin.eof())   //读编码文件结束
	{

		fin.read(&d, sizeof(char));   //一次读一个字节
		if (fin.eof())   
		{
			break;
		}
		while (count)
		{
			count--;
			a = c >> count;
			a = a & 0x01;    //只保留最低位
			a = a | 0x30;     //变成0/1对应的字符

			Push(S, a);
			for (i = 1; i <= n; i++)
			{
				if (!strcmp(S->base, HC[i]))    //判断是否找到了该编码
				{
					fout << HT[i].ch;
					ClearStack(S);
					break;
				}
			}
		}
		count = 8;
		c = d;
	}

	//此时还剩一个字节,要根据tag位判断剩余的是c中值还是d中值
	//cout << S->base;
	
	while (r)
	{
		r--;
		a = c >> r;
		a = a & 0x01;    //只保留最低位
		a = a | 0x30;     //变成0/1对应的字符
		Push(S, a);
		for (i = 1; i <= n; i++)
		{
			if (!strcmp(S->base, HC[i]))    //判断是否找到了该编码
			{
				fout << HT[i].ch;
				ClearStack(S);
				break;
			}
		}
	}
	fin.close();
	fout.close();
	free(S->base);
	free(S);
}
//********************************************************************
void InitStack(Stack S) //构造一个空栈
{
	S->base = (char*)malloc(Stack_Init_Size * sizeof(SqStack));
	if (!S->base)
	{
		printf("存储空间分配失败");
		exit(OVERFLOW);
	}
	S->top = S->base;
	S->stacksize = Stack_Init_Size;
}
//********************************************************************
void Push(Stack S, char e)
{
	char* newbase;
	if (S->top - S->base >= S->stacksize)
	{
		printf("存储空间不足，请增加分配");
		newbase = (char*)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(char));
		if (!newbase)
		{
			printf("存储分配失败");
			exit(OVERFLOW);
		}
		S->base = newbase;
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*(S->top) = e;
	(S->top)++;
	*(S->top) = '\0';
}
//********************************************************************
void Pop(Stack S, char& e)
{
	if (S->top == S->base)
		exit(0);
	(S->top)--;
	e = *(S->top);
	*(S->top) = '\0';
}
//********************************************************************
void ClearStack(Stack S)
{
	S->top = S->base;
}
//********************************************************************