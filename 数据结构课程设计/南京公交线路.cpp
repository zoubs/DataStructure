#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<iomanip>

using namespace std;

#define Source "BUS.txt"
typedef struct BusStop
{
	int busNum;    //站点所在线路
	int pre;       //与该线路上的上一个站连通的站点编号
	int next;      //与该线路的下一个站连通的站点编号
}BusStop;

typedef struct station
{
	int ID;               //站点编号
	char name[50];        //站点名
	bool flag;            //用于标记该站在广度搜索时是否被使用
	vector<BusStop> Total_Next_Stations; //该站所在的所有线路，即连通站
}Station;
typedef struct road
{
	int parent;         //用于储存路径
	int Num;            //公交站编号
}Path;

vector<int> BusLine[1000];    //公交线

vector<Station> Graph;       //公交线路图

int IsExist(char* name);   //处理输入文件时判断站点是否已存在
void BFS_Station(char* start, char* finish);   //所经车站最少的路线   参数：两个站点名
void Min_BusLine(char* start, char* finish);   //换成最少的路线，参数：两个站点名

int main()
{
	fstream file;
	file.open(Source, ios::in);
	if (file.fail())
	{
		cout << "文件打开失败";
		return 0;
	}
	Station temp;   //临时存储站点名
	int pre = 0, next, BusNum, Sta_Num, i = 0, j;
	char help[2] = { '\0','\0' };
	char Input[1000];
	temp.Total_Next_Stations.clear();
	temp.ID = 0;
	temp.flag = true;
	Graph.push_back(temp);    //作为0元素存储
	BusStop Adj_Station;
	char BusName[10], busname[10] = { '\0' };
	char sta_name[40] = {'\0'};
	while (!file.eof())
	{
		pre = 0;
		file >> BusName;  //遇到空格停
		file >> Input;    //获取该条线路信息
		if (file.eof())
		{
			break;
		}
		i = 0;
		while (BusName[i] >= '0' && BusName[i] <= '9')
		{
			help[0] = BusName[i];
			strcat_s(busname, 10, help);
			i++;
		}
		BusNum = atoi(busname);    //得到编号
		i = 0;
		while (i < strlen(Input))
		{
			while (Input[i] != ',' && Input[i] != '\n' && i < strlen(Input))
			{
				help[0] = Input[i];
				strcat_s(sta_name, 40, help);
				i++;
			}
			if (Input[i] != '\0')
			{
				i++;
			}
			Sta_Num = IsExist(sta_name);
			if (Sta_Num > 0)   //已有站点信息
			{
				Adj_Station.pre = pre;
				Adj_Station.busNum = BusNum;
				Adj_Station.next = 0;
				Graph[Sta_Num].Total_Next_Stations.push_back(Adj_Station);
				//修改上一个车站在该路线上的下一个车站信息
				if (pre != 0)   //上一个车站的编号不为 0
				{
					//搜索上一个车站并修改
					for (j = 0; j < Graph[pre].Total_Next_Stations.size(); j++)
					{
						if (Graph[pre].Total_Next_Stations[j].busNum == BusNum)
						{
							Graph[pre].Total_Next_Stations[j].next = Sta_Num;
							break;
						}
					}
				}
				pre = Sta_Num;    //修改下一个车站的上一个车站为本车站
			}
			else     //站点信息不存在
			{
				Sta_Num = Graph.size();   //现有站点数量+1，也即本次添加站点的编号
				temp.flag = false;
				strcpy_s(temp.name, 40, sta_name);
				temp.ID = Sta_Num;
				temp.Total_Next_Stations.clear();
				Graph.push_back(temp);
				Adj_Station.busNum = BusNum;
				Adj_Station.next = 0;
				Adj_Station.pre = pre;
				Graph[Sta_Num].Total_Next_Stations.push_back(Adj_Station);    //将本线路上的该站点信息存储
				if (pre != 0)  //修改本线路上的上一个车站的信息
				{
					for (j = 0; j < Graph[pre].Total_Next_Stations.size(); j++)
					{
						if (Graph[pre].Total_Next_Stations[j].busNum == BusNum)
						{
							Graph[pre].Total_Next_Stations[j].next = Sta_Num;
							break;
						}
					}
				}
				pre = Sta_Num;
			}
			BusLine[BusNum].push_back(Sta_Num);
			memset(sta_name, 0, 40);
			
		}
		memset(busname, 0, 10);
	}
	char start_station[40], finish_station[40];
	cout << "请输入要查询路线的两个站名" << endl;
	cout << "起始站：";
	cin >> finish_station;
	cout << "终点站：";
	cin >> start_station;
	if (IsExist(start_station) == 0)
	{
		cout << "起始站不存在" << endl;
	}
	else if(IsExist(finish_station) == 0)
	{
		cout << "终点站不存在" << endl;
	}
	else
	{
		cout << "经过站点最少的路线如下：" << endl;
		BFS_Station(start_station, finish_station);
		cout << endl;
		cout << "转线最少的路线如下：" << endl;
		Min_BusLine(start_station, finish_station);
	}
	cout << endl;
	system("pause");
	return 0;
}
//******************************************************************
void BFS_Station(char* start, char* finish)
{
	int start_ID, finish_ID;
	int size, j, i = 0, now;
	bool find = false;
	start_ID = IsExist(start);
	finish_ID = IsExist(finish);
	if (start_ID == finish_ID)
	{
		cout << "起点站与终点站相同" << endl;
		return;
	}
	vector<Path> path;
	Path temp, Next;   //遍历时临时使用的结点
	temp.parent = 0;
	temp.Num = 0;
	path.push_back(temp);
	temp.Num = start_ID;
	path.push_back(temp);   //保存起始站
	Graph[start_ID].flag = true;  //选中起始点
	i = 1;
	while (i < path.size())
	{
		temp = path[i];
		i++;
		if (temp.Num != finish_ID)  
		{
			for (j = 0; j < Graph[temp.Num].Total_Next_Stations.size(); j++)
			{   //将其相邻站点加入路径
				Next.parent = i - 1;//标记当前结点
				Next.Num = Graph[temp.Num].Total_Next_Stations[j].next;
				if (!Graph[Next.Num].flag)
				{
					path.push_back(Next);
					Graph[Next.Num].flag = true;
				}
				Next.Num = Graph[temp.Num].Total_Next_Stations[j].pre;
				if (!Graph[Next.Num].flag)
				{
					path.push_back(Next);
					Graph[Next.Num].flag = true;
				}
			}
		}
		else     //说明找到了终点，开始输出路径
		{
			cout << Graph[temp.Num].name;
			now = temp.Num;
			temp = path[temp.parent];
			while (temp.parent != 0)
			{
				cout << "->";
				for (int j = 0; j < Graph[now].Total_Next_Stations.size(); j++)
				{
					for (int k = 0; k < Graph[temp.Num].Total_Next_Stations.size(); k++)
					{
						if (Graph[now].Total_Next_Stations[j].busNum == Graph[temp.Num].Total_Next_Stations[k].busNum)
						{
							cout << Graph[now].Total_Next_Stations[j].busNum << "路 ";
						}
					}
				}
				cout << "->" << Graph[temp.Num].name;
				now = temp.Num;
				temp = path[temp.parent];
			}
			cout << "->";
			for (int j = 0; j < Graph[now].Total_Next_Stations.size(); j++)
			{
				for (int k = 0; k < Graph[path[1].Num].Total_Next_Stations.size(); k++)
				{
					if (Graph[now].Total_Next_Stations[j].busNum == Graph[path[1].Num].Total_Next_Stations[k].busNum)
					{
						cout << Graph[now].Total_Next_Stations[j].busNum << "路 ";
					}
				}
			}
			cout << "->" << Graph[path[1].Num].name;
			for (j = 1; j < Graph.size(); j++)
			{
				Graph[j].flag = false;
			}
			find = true;
			break;
		}
	}
	if (!find)
	{
		cout << "两站点之间没有路线可以到达" << endl;
		for (j = 1; j < Graph.size(); j++)   //清空标志位，为下次查询做准备
		{
			Graph[j].flag = false;
		}
	}
}
//******************************************************************
void Min_BusLine(char* start, char* finish)
{
	int start_ID, finish_ID, i, j, k;
	start_ID = IsExist(start);
	finish_ID = IsExist(finish);
	int line;
	/*struct line
	{
		int BusNum;
		int parent;
		int now;
	};
	
	queue<int>Q;
	queue<line>P;
	if (start_ID == finish_ID)
	{findBus
		cout << "起点站与终点站相同" << endl;
		return;
	}
	int i, j;
	int now;
	//line temp;
	Q.push(start_ID);
	while (!Q.empty())
	{
		now = Q.front();
		Q.pop();
		for (i = 0; i < Graph[now].Total_Next_Stations.size(); i++)
		{
			for (j = 0; j < Graph[finish_ID].Total_Next_Stations.size(); j++)
			{
				if (Graph[now].Total_Next_Stations[i].busNum == Graph[finish_ID].Total_Next_Stations[j].busNum)
				{//判断二者是否在一条公交线上
					find = true;
				}
			}
		}
	}*/

	bool find[1000];//用于标记路线是否已经添加
	for (i = 0; i < 1000; i++)
	{
		find[i] = true;
	}
	vector<Path> path;
	Path temp;
	temp.parent = 0;
	temp.Num = 0;
	path.push_back(temp);
	temp.Num = start_ID;  //初始化
	path.push_back(temp);
	int nowstation;   //当前站点
	int busNum;
	Path Next_Sta;
	i = 1;
	Graph[start_ID].flag= true;
	while (i < path.size())
	{
		temp = path[i];
		i++;
		//从第一个站点开始排查，是否可以通过某条公交线直接到终点站
		for (j = 0; j < Graph[temp.Num].Total_Next_Stations.size(); j++)
		{
			//搜索没有搜索过的线路
			int line = Graph[temp.Num].Total_Next_Stations[j].busNum;
			if (find[line])
			{
				//开始搜索该线路
				find[line] = false;
				int k = 0;
				while (k < BusLine[line].size())
				{
					if (BusLine[line][k] != finish_ID)
					{
						//该站不是终点站
						if (!Graph[BusLine[line][k]].flag)
						{
							Next_Sta.parent = i - 1;
							Next_Sta.Num = BusLine[line][k];
							path.push_back(Next_Sta);
							Graph[BusLine[line][k]].flag = true;
						}
					}
					else
					{
						//该点是终点站
						//输出路径
						if (temp.Num != finish_ID)
						{
							cout << Graph[finish_ID].name;
							cout << "->";
							for (j = 0; j < Graph[finish_ID].Total_Next_Stations.size(); j++)
							{
								for (k = 0; k < Graph[temp.Num].Total_Next_Stations.size(); k++)
								{
									if (Graph[finish_ID].Total_Next_Stations[j].busNum == Graph[temp.Num].Total_Next_Stations[k].busNum)
									{
										cout << Graph[finish_ID].Total_Next_Stations[j].busNum << "路 ";
									}
								}
							}
							cout << "->";
						}
						cout << Graph[temp.Num].name;
						nowstation = temp.Num;
						temp = path[temp.parent];
						while (temp.parent != 0)
						{
							cout << "->";
							for (j = 0; j < Graph[nowstation].Total_Next_Stations.size(); j++)
							{
								for (k = 0; k < Graph[temp.Num].Total_Next_Stations.size(); k++)
								{
									if (Graph[nowstation].Total_Next_Stations[j].busNum == Graph[temp.Num].Total_Next_Stations[k].busNum)
									{
										cout << Graph[nowstation].Total_Next_Stations[j].busNum << "路 ";
									}
								}
							}
							cout << "->" << Graph[temp.Num].name;
							nowstation = temp.Num;
							temp = path[temp.parent];
						}
						if (nowstation != path[1].Num)
						{
							cout << "->";
							for (int j = 0; j < Graph[nowstation].Total_Next_Stations.size(); j++)
							{
								for (int k = 0; k < Graph[path[1].Num].Total_Next_Stations.size(); k++)
								{
									if (Graph[nowstation].Total_Next_Stations[j].busNum == Graph[path[1].Num].Total_Next_Stations[k].busNum)
									{
										cout << Graph[nowstation].Total_Next_Stations[j].busNum << "路 ";
									}
								}
							}
							cout << "->" << Graph[path[1].Num].name;
						}
						for (int j = 1; j < Graph.size(); j++)
						{
							Graph[j].flag = false;
						}
						return;
					}
					k++;
				}
			}
		}
	}
	for (int j = 1; j < Graph.size(); j++)
	{
		Graph[j].flag = false;
	}
	cout << "两站之间没有路线" << endl;
}
//******************************************************************
int IsExist(char* name)
{
	int i;
	for (i = 0; i < Graph.size(); i++)
	{
		if (!strcmp(Graph[i].name, name))
		{
			return i;
		}
	}
	return 0;
}
//******************************************************************