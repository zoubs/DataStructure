#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<Windows.h>
#include<TlHelp32.h>
#include<psapi.h>
#include<time.h>
#include<iomanip>
#pragma comment(lib,"Psapi.lib") 
using namespace std;
typedef struct Node 
{
	double t;
	int pId;
	char start_time[40];
	char IDName[100];
	SIZE_T Mem_Size;
	char end_time[40];
	double Work_Time;		//持续时间
	struct Node * pre;     //指向前驱
	struct Node * next;    //指向后继
}proNode, * pro;

void Get_Pro_Info(pro p);      //读取进程
SIZE_T Get_Pro_Mem(DWORD pId);//返回进程占用的内存大小
void Sort_Mem(pro p);      //按内存排序
void Sort_Time(pro Closed_head);   //按结束时间排序
void Show_Process(pro p);      //显示开启的进程信息
void Show_Close(pro p);     //显示已结束的进程信息
void Refresh(pro p, pro pCur, pro pEnd);	//根据当前读到的pCur更新p，和pEnd
void DestroyList(pro head);


int main()
{
	char ch = 'y';
	pro pCur, head, Closed_head;
	head = new proNode;		//活跃进程
	Closed_head = new proNode;	//结束的进程
	if (!head || !Closed_head)
	{
		cout << "空间分配失败";
		return 0;
	}
	Closed_head->next = NULL;
	head->next = NULL;
	Get_Pro_Info(head);
	Sort_Mem(head);
	/*
	time_t rawtime;
	struct tm* info;
	info = new tm;

	time(&rawtime);

	localtime_s(info, &rawtime);
	asctime_s(buffer, info);
	cout<<"当前的本地时间和日期："<<buffer;*/

	while (ch == 'y')
	{
		pCur = new proNode;		//新一秒的进程
		if (!pCur)
		{
			cout << "空间分配失败";
			return 0;
		}
		Get_Pro_Info(pCur);						//读取新的进程列表
		Refresh(head, pCur, Closed_head);						//更新两个链表
		Sort_Mem(head);								//按内存排序
		Sort_Time(Closed_head);								//按时间排序
		cout << "当前活动进程：" << endl;
		Show_Process(head);
		cout << endl << "已结束进程：" << endl;
		Show_Close(Closed_head);
		DestroyList(pCur);
		cout << "是否继续显示：(y or n):";
		cin >> ch;
		//Sleep(5*1000);
		system("cls");
	}
	DestroyList(head);
	DestroyList(Closed_head);

	system("pause");
	return 0;
}
//**************************************************************
void Get_Pro_Info(pro p)      //读取进程
{
	time_t rawtime;
	struct tm* info;
	info = new tm;
	int i = 1;
	pro cur, last;
	STARTUPINFO st_Info;
	PROCESS_INFORMATION Pro_Info;
	PROCESSENTRY32 ps;
	HANDLE HP;
	memset(&st_Info, 0, sizeof(STARTUPINFO));
	memset(&Pro_Info, 0, sizeof(PROCESS_INFORMATION));
	st_Info.cb = sizeof(STARTUPINFO);
	memset(&ps, 0, sizeof(PROCESSENTRY32));
	ps.dwSize = sizeof(PROCESSENTRY32);
	HP = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);	//获取进程快照
	BOOL bMore = Process32First(HP, &ps);
	cur = p;
	p->pre = NULL;
	p->next = NULL;
	while (bMore) 
	{
		if (Get_Pro_Mem(ps.th32ProcessID) != -1) 
		{				//获取占用内存大小
			last = new proNode;
			if (!last)
			{
				cout << "空间分配失败";
				exit(0);
			}
			last->t = clock();
			last->next = NULL;
			last->pId = ps.th32ProcessID;
			char* m_char;
			int len = WideCharToMultiByte(CP_ACP, 0, ps.szExeFile, wcslen(ps.szExeFile), NULL, 0, NULL, NULL);
			m_char = new char[len + 1];
			WideCharToMultiByte(CP_ACP, 0, ps.szExeFile, wcslen(ps.szExeFile), m_char, len, NULL, NULL);
			m_char[len] = '\0';

			strcpy_s(last->IDName, strlen(m_char) + 1, m_char);				//获取进程名

			last->Mem_Size = Get_Pro_Mem(ps.th32ProcessID) / 1024;
			last->Work_Time = 0;
			time(&rawtime);
			localtime_s(info, &rawtime);
			asctime_s(last->start_time, info);
			last->pre = cur;
			cur->next = last;
			cur = cur->next;
		}
		bMore = Process32Next(HP, &ps);		//获取下一个进程信息
	}
	CloseHandle(HP);
}
//**************************************************************
SIZE_T Get_Pro_Mem(DWORD pId)//返回进程占用的内存大小
{
	HANDLE HP;
	PROCESS_MEMORY_COUNTERS pc;
	HP = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, pId);
	if (HP)
	{
		if (GetProcessMemoryInfo(HP, &pc, sizeof(pc)))
		{
			return pc.WorkingSetSize;         //返回当前内存使用
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
	//CloseHandle(HP);
}
//**************************************************************
void Sort_Mem(pro head)     //按内存排序
{
	pro p, q, temp, min, pre;
	if (head->next == NULL)
	{
		return;
	}
	q = head->next;
	
	p = new proNode;    //排序用的头结点
	p->next = NULL;
	while (head->next)
	{
		pre = head;
		min = head->next;
		temp = min->next;
		while (temp)
		{
			if (temp->Mem_Size < min->Mem_Size)
			{
				min = temp;
			}
			temp = temp->next;
		}
		pre = min->pre;
		pre->next = min->next;
		if (min->next)
		{
			min->next->pre = pre;
		}

		min->next = p->next;
		p->next = min;
		if (min->next)
		{
			min->next->pre = min;
		}
		min->pre = p;
	}
	head->next = p->next;   //排序完成
	if (p->next)
	{
		p->next->pre = head;
	}
	delete p;  
}
//**************************************************************
void Sort_Time(pro Closed_head)   //按结束时间排序
{
	pro temp_head, temp, pre, max;
	if (Closed_head->next == NULL)
	{
		return;
	}
	temp_head = new proNode;
	if (!temp_head)
	{
		cout << "空间分配失败";
		return;
	}
	temp_head->next = NULL;
	while (Closed_head->next)
	{
		pre = Closed_head;
		max = Closed_head->next;
		temp = max->next;
		while (temp)
		{
			if (temp->Work_Time > max->Work_Time)
			{
				max = temp;
				while (pre->next != max)
				{
					pre = pre->next;
				}
			}
			temp = temp->next;
		}
		pre->next = max->next;
		max->next = temp_head->next;
		temp_head->next = max;
	}
	Closed_head->next = temp_head->next;
	delete temp_head;
}
//**************************************************************
void Show_Process(pro head)      //显示开启的进程信息
{
	pro temp;
	int num = 1;
	temp = head->next;
	//***********************
	using std::wcout;
	using std::cout;
	cout.setf(std::ios::left);
	cout.width(8);
	cout << "进程ID：";
	cout.width(70);
	cout << "                                     进程名：" ;
	cout.width(20);
	cout << "     进程内存：";
	cout.width(10);
	cout << "       持续时间：" ;
	cout << "   开始时间："<< endl;
	
	while (temp)
	{
		cout<< setw(8)<< right << temp->pId;
		cout << setw(70) << temp->IDName;
		cout << setw(10) << right << temp->Mem_Size << " KB     ";
		cout << setw(15) << right << temp->Work_Time<<" S     ";
		cout << temp->start_time;
		
		temp = temp->next;
	}
}
//**************************************************************
void Show_Close(pro head)     //显示已结束的进程信息
{
	pro temp;
	int num = 1;
	temp = head->next;
	using std::cout;
	cout.setf(std::ios::left);
	cout.width(8);
	cout << "  进程ID：";
	cout.width(70);
	cout << "                                     进程名：";
	cout.width(20);
	cout << "       持续时间：";
	cout.width(20);
	cout << "结束时间：" << endl;
	
	while (temp) 
	{
		cout << setw(8) << right << temp->pId;
		cout << setw(70)<< temp->IDName;
		cout << setw(10)<< right << temp->Work_Time<<" S     ";
		cout << temp->end_time;
		
		temp = temp->next;
	}
}
//**************************************************************
void Refresh(pro head, pro head_now, pro head_Closed)
{
	clock_t Now_Time;
	time_t rawtime;
	struct tm* info;
	info = new tm;

	/*time(&rawtime);

	localtime_s(info, &rawtime);
	asctime_s(buffer, info);*/
	pro temp_now, temp_end, temp_open, pre, temp, temp_close;   //temp_end代表尾结点
	bool flag;
	temp_end = head_Closed;
	while (temp_end->next) //找到已结束进程链表的最后一个结点
	{	
		temp_end = temp_end->next;
	}
	temp_open = head->next;
	while (temp_open) //遍历打开的进程链表中每一个进程，若在当前进程列表未找到，则其已被关闭，将其添加到已结束进程链表
	{
		flag = false;   //代表未找到
		temp_now = head_now->next;
		while (temp_now != NULL) 
		{
			if (!strcmp(temp_open->IDName, temp_now->IDName) && temp_open->pId == temp_now->pId)	//说明进程目前仍被打开
			{
				flag = true;
				break;
			}
			temp_now = temp_now->next;
		}

		temp = temp_open;     //要移出的结点
		temp_open = temp_open->next;    //待操作结点变成下一个
		if (!flag)    //说明temp_open被关闭
		{
			//将其从工作中进程链表中取出，添加到已关闭链表中
			pre = temp->pre;
			pre->next = temp->next;
			if (pre->next)
			{
				pre->next->pre = temp->pre;
			}
			//摘下temp结点
			Now_Time = clock();
			temp->Work_Time = (double)(Now_Time - temp->t) / CLOCKS_PER_SEC;
			
			time(&rawtime);
			localtime_s(info, &rawtime);
			asctime_s(temp->end_time, info);

			temp->next = temp_end->next;
			temp_end->next = temp;				//接到pEnd
			temp_end = temp_end->next;
		}
		else
		{
			Now_Time = clock();
			temp->Work_Time = (double)(Now_Time - temp->t) / CLOCKS_PER_SEC;
		}
	}

	temp_end = head;
	while (temp_end->next)
	{
		temp_end = temp_end->next;
	}

	temp_now = head_now->next;
	while (temp_now) 
	{		//遍历当前进程链表中每一个进程，如果在已打开进程列表中未找到，则说明是新打开的进程，然后将其接到已打开进程的尾端
		flag = false;
		temp_open = head->next;
		while (temp_open) 
		{
			if (!strcmp(temp_open->IDName, temp_now->IDName) && temp_open->pId == temp_now->pId)	//如果还是原来的进程，则略过
			{
				flag = true;
				break;
			}
			temp_open = temp_open->next;
		}
		temp = temp_now;   //要被移出的结点
		temp_now = temp_now->next;    //待操作结点指向下一个
		if (!flag)
		{	//说明是新打开的进程
			pre = temp->pre;   
			pre->next = temp->next;
			if (pre->next)
			{
				pre->next->pre = temp->pre;
			}
			time(&rawtime);
			localtime_s(info, &rawtime);
			asctime_s(temp->start_time, info);
			temp->next = temp_end->next;
			temp_end->next = temp;
			temp_end = temp_end->next;
		}
	}

	temp_close = head_Closed->next; 
	while (temp_close)   //判断已关闭进程是否被重新打开
	{
		flag = false;
		temp_now = head_now->next;
		while (temp_now)
		{
			if (!strcmp(temp_close->IDName, temp_now->IDName) && temp_close->pId == temp_now->pId)
			{//说明又被打开
				flag = true;
				break;
			}
			temp_now = temp_now->next;
		}
		temp = temp_close;                //当前结点
		temp_close = temp_close->next;    //指向下一个
		if (flag)
		{
			pre = head_Closed;
			while (pre->next != temp)
			{
				pre = pre->next;
			}
			pre->next = temp->next;
			delete temp;
		}
	}
}
//**************************************************************
void DestroyList(pro head)
{
	pro temp;
	temp = head->next;
	while (temp)
	{
		head->next = temp->next;
		delete temp;
		temp = head->next;
	}
	delete head;
}