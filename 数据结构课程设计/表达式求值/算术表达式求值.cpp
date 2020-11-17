#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

#define MAX 1000
#define Stack_Init_Size  100
#define STACKINCREMENT   40

typedef struct
{
	char* base;//栈底指针
	char* top;//栈顶
	int size;//栈的大小
}TR,*OPTR;//运算符栈

typedef struct
{
	float* base;//栈的指针
	float* top;//栈顶
	int size;//栈的大小

}ND, *OPND;//数字栈


int Init(TR& S);                          //初始化运算符栈，参数：运算符栈
int Push(TR& S, char e);                  //运算符入栈，参数：运算符栈S，运算符e
int Pop(TR& S, char& e);                  //运算符弹栈，参数：运算符栈S，字符e
int Gettop(TR S, char& e);                //取运算符栈栈顶元素，参数：运算符栈S，字符e
int Init_Data(ND& S);                     //初始化数字栈，参数：数字栈
int Push_Data(ND& S, float e);            //数字入栈，参数数字栈S，数据e
int Pop_Data(ND& S, float& e);            //数字弹栈，参数：数字栈S，数据e
int Gettop_Data(ND S, float& e);          //取数字栈栈顶元素，参数：数字栈，数据e
char Judge(char a, char b);               //判断运算符优先级，参数，两个运算符a，b
int IsOptr(char c);                       //判断是否为运算符，参数：字符c
float cal_ans(float a, char k, float b);  //计算akb的结果，k为运算符，a、b为数字，参数：数据a，运算符k，数据b
int Get_Answer(char* input, float& ans);       //参数：算式a，答案ans
int TraveraseOptr(TR S);                  //遍历符号栈
int TraveraseOpnd(ND S);                  //遍历操作数栈
int BracketMatch(char* a);                    //检验括号是否匹配

int main()
{
	char a[MAX];   //存放输入
	char c[MAX] = {'\0'};   //用于存放括号，进行括号匹配
	int i, j = 0;   //用于遍历
	int flag = 0;   //表示当前算式有无等号
	float ans;    //存储最终结果
	int left = 0, right = 0;//统计左右括号数量
	cout << "请输入要计算的表达式：" << endl;
	cin.getline(a, MAX);
	if (a[0] != '#')
	{
		cout << "[错误] 表达式的开头应为'#'" << endl;
		system("pause");
		return -1;
	}//此时a[0] == '#'
	flag = 0;
	for (i = 1; i < strlen(a); i++)  //初步判断表达式是否合法
	{
		if (a[i] == '(')
		{
			c[j] = '(';
			j++;
			c[j] = '\0';   //保证数组结尾为\0
			left++;
		}
		else if (a[i] == ')')
		{
			c[j] = ')';
			j++;
			c[j] = '\0';
			right++;
		}
		else if (a[i] == '/' && a[i + 1] == '0')
		{
			cout << "[错误]除数不能为0";
			system("pause");
			return -1;
		}
		else if (!(a[i] == '.' || IsOptr(a[i]) || isdigit(a[i])))
		{
			cout << "有不合法字符出现" << endl;
			system("pause");
			return -1;
		}
	}
	if (left != right)
	{
		cout << "左右括号不匹配";
		system("pause");
		return -1;
	}
	else
	{
		if (!BracketMatch(c))//调用检查括号匹配函数
		{
			system("pause");
			return 0;
		}
		else if (Get_Answer(a, ans))
		{
			cout << "表达式的结果为：" << ans << endl;
			system("pause");
			return 0;
		}
	}
}
//********************************************************************
int Init(TR &S)//初始化运算符栈，参数：运算符栈引用
{
	S.base = (char*)malloc(Stack_Init_Size * sizeof(char));
	if (S.base == NULL)
	{
		cout << "存储空间分配失败";
		exit(0);
	}
	S.size = Stack_Init_Size;
	S.top = S.base;
	return 1;
}
//********************************************************************
int Push(TR& S, char e)//运算符入栈，参数：运算符栈s引用，运算符e
{
	char* newbase;
	if (S.top - S.base >= S.size)
	{
		printf("存储空间不足，请增加分配");
		newbase = (char*)realloc(S.base, (S.size + STACKINCREMENT) * sizeof(char));
		if (!newbase)
		{
			printf("存储分配失败");
			exit(OVERFLOW);
		}
		S.base = newbase;
		S.top = S.base + S.size;
		S.size += STACKINCREMENT;
	}
	*S.top = e;
	S.top++;
	return 1;
}
//********************************************************************
int Pop(TR& S, char& e)
{
	if (S.top == S.base)
	{
		return -1;
	}
	S.top--;
	e = *(S.top);
	return 1;
}
//********************************************************************
int Gettop(TR S, char& e)//取运算符栈栈顶元素，参数：运算符栈s，字符e
{
	if (S.top == S.base)
	{
		exit(-1);
	}
	e = *(S.top-1);
	return 1;
}
//********************************************************************
int Init_Data(ND& S)//初始化数字栈，参数：数字栈引用
{
	S.base = (float*)malloc(Stack_Init_Size * sizeof(float));
	if (S.base == NULL)
	{
		cout << "存储空间分配失败";
		exit(0);
	}
	S.size = Stack_Init_Size;
	S.top = S.base;
	return 1;
}
//********************************************************************
int Push_Data(ND& S, float e)//运算符入栈，参数：运算符栈s引用，运算符e
{
	float* newbase;
	if (S.top - S.base >= S.size)
	{
		printf("存储空间不足，请增加分配");
		newbase = (float*)realloc(S.base, (S.size + STACKINCREMENT) * sizeof(float));
		if (!newbase)
		{
			printf("存储分配失败");
			exit(0);
		}
		S.base = newbase;
		S.top = S.base + S.size;
		S.size += STACKINCREMENT;
	}
	*S.top = e;
	S.top++;
	return 1;
}
//********************************************************************
int Pop_Data(ND& S, float& e)
{
	if (S.top == S.base)
	{
		return -1;
	}
	S.top--;
	e = *(S.top);
	return 1;
}
//********************************************************************
int Gettop_Data(ND S, float& e)//取数字栈栈顶元素，参数：数字栈，数据e
{
	if (S.top == S.base)
	{
		exit(-1);
	}
	e = *(S.top - 1);
	return 1;
}
//********************************************************************
char Judge(char a, char b)//判断优先级
{
	switch (a)
	{
	case '+':
		if (b == '+' || b == '-' || b == ')' || b == '#')
		{
			return '>';
		}
		else
		{
			return '<';
		}
	case '-':
		if (b == '+' || b == '-' || b == ')' || b == '#')
		{
			return '>';
		}
		else
		{
			return '<';
		}
	case '*':
		if (b == '(')
		{
			return '<';
		}
		else
		{
			return '>';
		}
	case '/':
		if (b == '(')
		{
			return '<';
		}
		else
		{
			return '>';
		}
	case '#':
		if (b == '#')
		{
			return '=';
		}
		else if (b == ')')
		{
			return '0';
		}
		else
		{
			return '<';
		}
	case '(':
		if (b == ')')
		{
			return '=';
		}
		else if (b == '#')
		{
			return '0';
		}
		else
		{
			return '<';
		}
	case ')':
		if (b == '(')
		{
			return ' ';
		}
		else
		{
			return '>';
		}

	default:
		return '0';
	}
}
//********************************************************************
int IsOptr(char c)//判断是否为运算符，参数：字符c
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '#')
	{
		return 1;
	}
	return 0;
}
//********************************************************************
float cal_ans(float a, char k, float b)//计算akb的结果，k为运算符，a、b为数字，参数：数据a，运算符k，数据b
{
	switch (k)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	default:
		return 0.0;
	}
}
//********************************************************************
int Get_Answer(char* input, float& ans)//参数：算式a，答案ans
{
	TR optr;
	ND opnd;     //定义两个栈
	int i = 0;   //用于遍历
	float data;
	char t[20] = {0};
	char help[2] = { '#', '\0' };
	//char* c;
	char e;
	char x;
	float a, b;
	int flag = 0;//记录有无错误

	Init(optr);   //初始化符号栈
	Init_Data(opnd);  //初始化数字栈
	Push(optr, input[i]);   //放入#号
	i++;
	TraveraseOptr(optr);
	Gettop(optr, e);
	cout << "输入序列：" << &input[i] << endl << endl;
	while (input[i] != '#' || e != '#')
	{
		if (!IsOptr(input[i]))
		{
			help[0] = input[i];
			strcat_s(t, 20, help);
			i++;
			if (IsOptr(input[i]) || input[i] == '#')
			{
				data = atof(t);
				Push_Data(opnd, data);
				TraveraseOpnd(opnd);
				strcpy_s(t, 20, "\0");
				//printf("%.2f, ", data);
			}
		}
		else
		{
			switch (Judge(e, input[i]))
			{
			case '<':
				Push(optr, input[i]);    //运算符压栈
				TraveraseOptr(optr);
				i++;
				break;
			case '=':
				Pop(optr, e);    //运算符抵消
				TraveraseOptr(optr);
				i++;
				break;
			case '>':
				Pop(optr, e);
				TraveraseOptr(optr);
				//
				if (opnd.top - opnd.base < 2)
				{
					cout << "表达式运算符数量与数据数量不匹配，算式有误！" << endl;
					system("pause");
					//flag = 1;
					return 0;
				}
				else
				{
					Pop_Data(opnd, b);
					Pop_Data(opnd, a);   //弹出两个操作数,a被除数，b除数
					TraveraseOpnd(opnd);
					if (e == '/' && b == 0)
					{
						cout << "[错误]除数不能为0" << endl;
						system("pause");
						return 0;
					}
					else   //计算结果入栈
					{
						Push_Data(opnd, cal_ans(a, e, b));
						TraveraseOpnd(opnd);
					}
				}
				break;
			}
			cout << "输入序列：" << &input[i] << endl << endl;
		}
		Gettop(optr, e);
	}
	cout << endl;
	Gettop_Data(opnd, ans);   //取出栈顶答案
	free(opnd.base);
	free(optr.base);
	return 1;
}
//********************************************************************
int TraveraseOptr(TR S)
{
	char* p;
	cout << "运算符栈：";
	for (p = S.base; p < S.top; p++)
	{
		cout << *p << " ";
	}
	cout << endl;
	return 1;
}
//********************************************************************
int TraveraseOpnd(ND S)
{
	float* p;
	cout << "操作数栈：";
	for (p = S.base; p < S.top; p++)
	{
		cout << *p << " ";
	}
	cout << endl;
	return 1;
}
//********************************************************************
int BracketMatch(char* a)
{
	int i = 0, n = strlen(a);
	char e;
	TR bracket;   //括号栈
	Init(bracket);
	for (i = 0; i < n; i++)
	{
		switch (a[i])
		{
		case '(':   //左括号则压栈
			Push(bracket, a[i]);   
			break;
		case ')':
			if (bracket.base == bracket.top)   //若栈空，则右括号多余
			{
				cout << "[错误]有右括号多余" << endl;
				return 0;
			}
			Pop(bracket, e);   //弹出栈顶元素
			if (e != '(')  //说明不匹配
			{
				cout << "[错误]左右括号不匹配" << endl;
				return 0;
			}
			break;
		default:
			break;
		}
	}
	if (bracket.base != bracket.top)   //栈不空,有多余的左括号
	{
		cout << "[错误]有多余的左括号" << endl;
		return 0;
	}
	free(bracket.base);
	return 1;
}
//********************************************************************