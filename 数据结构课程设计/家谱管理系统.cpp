#include<iostream>
#include<queue>
#include<stack>
#include<fstream>

using namespace std;

#define Source "FamilyTree_Input.txt"
#define OutFile "Family_Tree_Result.txt"
typedef struct person
{
	int ID;          //编号
	int parentID;    //父亲的编号，方便找父亲
	char name[20];   //姓名
	bool IsMarry;    //1：已婚  0：未婚
	bool IsLive;     //是否在世
	char address[40];  //地址
	char Birth[20];    //出生时间
	char Dead_Time[20];  //死亡时间，若其已死亡
	int x;              //输出时的x坐标
	int y;              //输出时的y坐标
	struct person* nextSibling;
	struct person* firstChild;

}Person, *Member;
int num = 0;                //记录成员个数
Member familyTree();                        //创建家谱
Member findPerson_ID(int ID, Member T);     //根据编号找成员
void Write_File(Member T);                  //输出到文件
void deletTree(Member p, Member T);         //删除子树
void Print_Tree(Member T);                  //显示家谱
void Show_Gen(int n, Member T);             //显示第n代所有人信息
void Show_Member(Member p);                 //显示成员个人信息
Member findPerson_Birth(char* birth, Member T);//按生日显示成员
void Search_ship(person*, person*);         //查询两人关系
bool IsElder(Member p, Member q, Member T); //查询是否是长辈
void AddChild(Member p);                    //增加孩子
Member findPerson_name(char* name, Member T);//根据姓名查找成员
void Delete(Member& p);                     //删除以p为根的树
int Depth(Member T);                       //计算家谱深度
void Locate(Member T);                      //对家谱中的结点定位

int main()
{
	Member T, ptr, temp;
	T = familyTree();
	char ch = 'y';
	int choice, n;
	char name[20], birthday[20], address[40];
	while (ch == 'y')
	{
		cout << "**************家谱管理系统欢迎您*************" << endl;
		cout << "1：显示家谱" << endl;
		cout << "2：显示第n代所有人信息" << endl;
		cout << "3：通过姓名查询成员信息" << endl;
		cout << "4：通过生日查询成员信息" << endl;
		cout << "5：输入成员名为其添加孩子" << endl;
		cout << "6：查询两人关系" << endl;
		cout << "7：删除某成员及其后代" << endl;
		cout << "8：修改成员信息" << endl;
		cout << "9：将信息输出到文件" << endl;
		cout << "请选择要做的项目：";
		cin >> choice;
		switch (choice)
		{
		case 1:
			Print_Tree(T);
			break;
		case 2:
			cout << "请输入要查询第几代：";
			cin >> n;
			Show_Gen(n,T);
			break;
		case 3:
			cout << "请输入要查询的姓名：";
			cin >> name;
			ptr = findPerson_name(name, T);
			if (ptr == NULL)
			{
				cout << "该成员不在家谱中" << endl;
			}
			else
			{
				cout << "本人信息如下：" << endl;
				Show_Member(ptr);
				temp = findPerson_ID(ptr->parentID, T);
				if (temp == NULL)
				{
					cout << "其是该家族的祖先" << endl;
				}
				else
				{
					cout << "父亲信息如下: " << endl;
					Show_Member(temp);
				}
				if (ptr->firstChild)
				{
					cout << "孩子信息如下：" << endl;
					temp = ptr->firstChild;
					Show_Member(temp);
					temp = temp->nextSibling;
					while (temp)
					{
						Show_Member(temp);
						temp = temp->nextSibling;
					}
				}
				else
				{
					cout << "其没有孩子" << endl;
				}
			}
			break;
		case 4:
			cout << "请输入要查询的成员的生日：";
			cin >> birthday;
			ptr = findPerson_Birth(birthday, T);
			if (ptr == NULL)
			{
				cout << "家谱中无该成员" << endl;
			}
			else
			{
				cout << "该成员信息如下：" << endl;
				Show_Member(ptr);
			}
			break;
		case 5:
			cout << "请输入要添加孩子的成员名: ";
			cin >> name;
			ptr = findPerson_name(name, T);
			if (ptr == NULL)
			{
				cout << "该成员不在家谱中,无法添加孩子" << endl;
			}
			else
			{
				AddChild(ptr);
				num++;
			}
			break;
		case 6:
			char name2[20];
			cout << "请依次输入要查询关系的两个成员名" << endl;
			cout << "成员1：";
			cin >> name;
			ptr = findPerson_name(name, T);
			if (ptr == NULL)
			{
				cout << "成员1不在家谱中" << endl;
				break;
			}
			cout << "成员2：";
			cin >> name2;
			temp = findPerson_name(name2, T);
			if (temp == NULL)
			{
				cout << "成员2不在家谱中" << endl;
				break;
			}
			if (IsElder(ptr, temp, T))
			{
				cout << name << "是" << name2 << "的长辈" << endl;
			}
			else if(IsElder(temp,ptr,T))
			{
				cout << name2 << "是" << name << "的长辈" << endl;
			}
			else
			{
				cout << "两成员无关系" << endl;
			}
			break;
		case 7:
			cout << "请输入要删除成员及其后代的姓名：";
			cin >> name;
			ptr = findPerson_name(name, T);
			if (ptr == NULL)
			{
				cout << "该成员不在家谱中" << endl;
			}
			else
			{
				deletTree(ptr, T);
			}
			break;
		case 8:
			cout << "请输入要修改信息的成员名：";
			cin >> name;
			ptr = findPerson_name(name, T);
			if (ptr == NULL)
			{
				cout << "该成员不在家谱中" << endl;
			}
			else
			{
				char ch;
				cout << "1：姓名" << endl;
				cout << "2：生日" << endl;
				cout << "3：地址" << endl;
				cout << "4：是否结婚" << endl;
				cout << "5：是否在世" << endl;
				cout << "请输入要修改的项目编号：" << endl;
				cin >> choice;
				switch (choice)
				{
				case 1:
					cout << "请输入要修改的姓名：";
					cin >> name;
					cout << "确认将姓名修改为：" << name << "吗?(y or n)";
					cin >> ch;
					if (ch == 'y')
					{
						strcpy_s(ptr->name, 20, name);
						cout << "姓名修改成功";
					}
					else
					{
						cout << "取消修改" << endl;
					}
					break;
				case 2:
					cout << "请输入要修改生日：";
					cin >> birthday;
					cout << "确认将生日修改为：" << birthday << "吗?(y or n)";
					cin >> ch;
					if (ch == 'y')
					{
						strcpy_s(ptr->Birth, 20, birthday);
						cout << "生日修改成功";
					}
					else
					{
						cout << "取消修改" << endl;
					}
					break;
				case 3:
					cout << "请输入要修改的地址：";
					cin >> address;
					cout << "确认将地址修改为：" << address << "吗?(y or n)";
					cin >> ch;
					if (ch == 'y')
					{
						strcpy_s(ptr->address, 20, address);
						cout << "地址修改成功";
					}
					else
					{
						cout << "取消修改" << endl;
					}
					break;
				case 4:
					cout << "请输入是否已婚（1：已婚 0：未婚）：";
					cin >> ch;
					if (ch == '1')
					{
						cout << "确认将修改为已婚吗?(y or n)";
						cin >> ch;
						if (ch == 'y')
						{
							ptr->IsMarry = true;
							cout << "修改成功";
						}
						else
						{
							cout << "取消修改" << endl;
						}
					}
					else
					{
						cout << "确认将修改为未婚吗?(y or n)";
						cin >> ch;
						if (ch == 'y')
						{
							ptr->IsMarry = false;
							cout << "修改成功";
						}
						else
						{
							cout << "取消修改" << endl;
						}
					}
					break;
				case 5:
					cout << "请输入是否在世（1：在世 0：去世）：";
					cin >> ch;
					if (ch == '1')
					{
						cout << "确认将修改为在世吗?(y or n)";
						cin >> ch;
						if (ch == 'y')
						{
							ptr->IsLive = true;
							cout << "修改成功";
						}
						else
						{
							cout << "取消修改" << endl;
						}
					}
					else
					{
						cout << "确认将修改为未婚吗?(y or n)";
						cin >> ch;
						if (ch == 'y')
						{
							ptr->IsLive = false;
							cout << "修改成功";
						}
						else
						{
							cout << "取消修改" << endl;
						}
					}
					break;
				default:
					break;
				}
			}
			break;
		case 9:
			Write_File(T);
			break;

		default:
			break;
		}
		cout << endl << "是否继续使用系统（y or n）:";
		cin >> ch;
		//system("cls");
	}
	system("pause");
	return 0;
}
//*************************************************************************
Member familyTree()
{
	fstream file;
	file.open(Source, ios::in);
	Member T, temp, parent;
	if (file.fail())
	{
		cout << "文件打开失败";
		exit(0);
	}
	T = new Person;
	if (!T)
	{
		cout << "空间分配失败";
		exit(0);
	}
	T->parentID = 0;
	T->firstChild = NULL;
	T->nextSibling = NULL;
	int i, j;
	char ID[5] = { '\0'};
	char parentID[5] = { '\0' };
	char help[2] = { '\0','\0' };
	char name[20] = { '\0' };
	char Birth[20] = { '\0' };    //出生时间
	char Dead_Time[20] = {'\0'};  //死亡时间，若其已死亡
	char address[40] = { '\0' };
	char inputLine[128] = { '\0' };
	while (!file.eof())
	{
		file.getline(inputLine, 128);
		if (file.eof())
		{
			break;
		}
		if (num == 0)
		{
			temp = T;
			num++;
		}
		else
		{
			temp = new person;
			num++;
		}
		i = 0;

		//获取ID
		while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
		{ 
			i++;
		}
		while (inputLine[i] != '\t' && inputLine[i] != '\n' && inputLine[i] != ' ')
		{
			help[0] = inputLine[i];
			strcat_s(ID, 5,help);
			i++;
		}
		temp->ID = atoi(ID);
		
		while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
		{
			i++; 
		}
		while (inputLine[i] != '\t' && inputLine[i] != '\n' && inputLine[i] != ' ')
		{
			help[0] = inputLine[i];
			strcat_s(name, 20, help);
			i++;
		}
		strcpy_s(temp->name, 20, name);

		while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
		{
			i++;
		}
		while (inputLine[i] != '\t' && inputLine[i] != '\n' && inputLine[i] != ' ')
		{
			help[0] = inputLine[i];
			strcat_s(parentID, 5, help);
			i++;
		}
		temp->parentID = atoi(parentID);
		while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
		{
			i++;
		}
		while (inputLine[i] != '\t' && inputLine[i] != '\n' && inputLine[i] != ' ')
		{
			help[0] = inputLine[i];
			strcat_s(Birth, 20, help);
			i++;
		}
		strcpy_s(temp->Birth, 20, Birth);

		while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
		{
			i++;
		}
		if (inputLine[i] == '1')
		{
			temp->IsMarry = true;    //说明已结婚
		}
		else if (inputLine[i] == '0')
		{
			temp->IsMarry = false;
		}
		else
		{
			cout << "输入数据错误" << endl;
			exit(0);
		}
		i++;

		while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
		{
			i++;
		}
		while (inputLine[i] != '\t' && inputLine[i] != '\n' && inputLine[i] != ' ')
		{
			help[0] = inputLine[i];
			strcat_s(address, 40, help);
			i++;
		}
		strcpy_s(temp->address, 40, address);

		//是否死亡
		while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
		{
			i++;
		}
		if (inputLine[i] == '1')
		{
			temp->IsLive = true;
		}
		else if (inputLine[i] == '0')
		{   //死亡，记录死亡时间
			temp->IsLive = false;
			i++;
			while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
			{
				i++;
			}
			while (inputLine[i] != '\t' && inputLine[i] != '\n' && inputLine[i] != ' ' && inputLine[i] != '\r' && inputLine[i] != '\0')
			{
				help[0] = inputLine[i];
				strcat_s(Dead_Time, 20, help);
				i++;
			}
			strcpy_s(temp->Dead_Time, 20, Dead_Time);
		}
		else
		{
			cout << "输入数据错误" << endl;
			exit(0);
		}
		temp->firstChild = NULL;
		temp->nextSibling = NULL;
		//将结点插入到家谱正确位置中
		parent = findPerson_ID(temp->parentID,T);
		if (parent != NULL)
		{
			if (parent->firstChild == nullptr)
			{
				parent->firstChild = temp;
			}
			else
			{
				parent = parent->firstChild;
				while (parent->nextSibling != nullptr)
				{
					parent = parent->nextSibling;
				}
				parent->nextSibling = temp;
			}
		}
		memset(inputLine, 0, 128);
		memset(name, 0, 20);
		memset(ID, 0, 5);
		memset(address, 0, 40);
		memset(Birth, 0, 20);
		memset(Dead_Time, 0, 20);
		memset(parentID, 0, 5);
	}
	file.close();
	return T;
}
//*************************************************************************
Member findPerson_ID(int ID, Member T)
{
	Member p = T;
	stack<Member> S;
	while (!S.empty() || p)
	{
		if (p)
		{
			if (p->ID == ID)
			{
				return p;
			}
			S.push(p);
			p = p->firstChild;
		}
		else
		{
			p = S.top();
			S.pop();
			p = p->nextSibling;
		}
	}
	return NULL;
}
//*************************************************************************
Member findPerson_name(char* name, Member T)
{
	Member p = T;
	stack<Member> S;
	while (!S.empty() || p)
	{
		if (p)
		{
			if (!strcmp(name,p->name))
			{
				return p;
			}
			S.push(p);
			p = p->firstChild;
		}
		else
		{
			p = S.top();
			S.pop();
			p = p->nextSibling;
		}
	}
	return NULL;
}
//*************************************************************************
Member findPerson_Birth(char* birth, Member T)
{
	Member p = T;
	stack<Member> S;
	while (!S.empty() || p)
	{
		if (p)
		{
			if (!strcmp(birth, p->Birth))
			{
				//Show_Member(p);
				return p;
			}
			S.push(p);
			p = p->firstChild;
		}
		else
		{
			p = S.top();
			S.pop();
			p = p->nextSibling;
		}
	}
	return NULL;
}
//*************************************************************************
void deletTree(Member p, Member T)
{
	Member parent;
	Member del;
	if (p == T)
	{
		delete(T);
		return;
	}
	parent = findPerson_ID(p->parentID,T);
	if (parent->firstChild == p)   //p是其双亲的第一个孩子
	{
		del = p;
		parent->firstChild = p->nextSibling;   //双亲第一个孩子指针指向其下一个孩子即可
		Delete(p);
	}
	else
	{
		parent = parent->firstChild;
		while (parent->nextSibling != NULL && parent->nextSibling != p)   //一直找到要删除的子树的根结点p
		{
			parent = parent->nextSibling;
		}
		del = p;
		parent->nextSibling = p->nextSibling;
		Delete(p);
	}
	cout << "删除成功" << endl;
}
//*************************************************************************
void Delete(Member& p)//删除以p为根的子树
{
	if (p)
	{
		Delete(p->firstChild);
		Delete(p->nextSibling);
		delete p;
	}
}
//*************************************************************************
void Show_Gen(int n, Member T)
{
	queue<Member> Q;   //定义队列
	Member p, q;
	int level = 0;
	int Dep, len;
	Dep = Depth(T);
	if (n > Dep)
	{
		cout << "查询的代数大于家谱的代数" << endl;
		return;
	}
	if (T == NULL)
	{
		cout << "家谱为空" << endl;
		return;
	}
	Q.push(T);
	while (!Q.empty())
	{
		len = Q.size();
		level++;   //层数
		while (len--)
		{
			p = Q.front();
			Q.pop();
			if (level == n)
			{
				Show_Member(p);
			}
			if (p->firstChild)
			{
				q = p->firstChild;
				Q.push(q);
				while (q->nextSibling)   //所有孩子入队
				{
					q = q->nextSibling;
					Q.push(q);
				}
			}
		}
	}
}
//*************************************************************************
int Depth(Member T)
{
	if (T == NULL)
	{
		return 0;
	}
	else
	{
		return ((Depth(T->firstChild) + 1) > Depth(T->nextSibling)) ? (Depth(T->firstChild) + 1) : Depth(T->nextSibling);
	}
}
//*************************************************************************
void Show_Member(Member p)
{
	if (p == NULL)
	{
		cout << "该成员不存在" << endl;
	}
	cout << "该成员个人信息如下" << endl;
	cout << "编号:		" << p->ID << endl;
	cout << "姓名:		" << p->name << endl;
	cout << "出生日期:	" << p->Birth << endl;
	if (p->IsMarry) 
	{ 
		cout << "已婚"; 
	}
	else
	{
		cout << "未婚";
	}
	cout << endl;
	cout << "家庭地址:	" << p->address << endl;
	if (p->IsLive)
	{
		cout << "在世" << endl;
	}
	else
	{
		cout << "已去世" << endl;
		cout << "去世时间为: " << p->Dead_Time << endl;
	}
}
//*************************************************************************
void Relationship(Member p, Member q, Member T)
{
	if (IsElder(p, q, T))
	{
		cout << " " << p->name << " 是 " << q->name << "的长辈" << endl;
	}
	else
	{
		if (IsElder(q, p, T))
		{
			cout << " " << q->name << " 是 " << p->name << "的长辈" << endl;
		}
	}
}
//*************************************************************************
bool IsElder(Member p, Member q, Member T)
{
	//判断p是否是q的长辈
	Member temp;
	temp = q;
	if (p == NULL || q == NULL)
	{
		cout << "查询关系错误";
		return false;
	}
	while (temp->parentID != 0)
	{
		temp = findPerson_ID(temp->parentID, T);
		if (temp->ID == p->ID)
		{
			return true;
		}
	}
	return false;
}
//*************************************************************************
void AddChild(Member p)
{
	if (p == NULL)
	{
		return;
	}
	Member temp, index;
	int IsMerry, IsDead;
	temp = new person;
	//temp = p->firstChild;
	if (p->firstChild == NULL)  //该成员没有孩子
	{
		p->firstChild = temp;
	}
	else
	{
		index = p->firstChild;
		while (index->nextSibling)
		{
			index = index->nextSibling;
		}
		//此时index的下一个兄弟为temp
		index->nextSibling = temp;
	}
	temp->firstChild = NULL;
	temp->nextSibling = NULL;
	//cout << "请输入编号：";
	//cin >> temp->ID;
	temp->ID = num + 1;
	cout << "输入姓名：";
	cin >> temp->name;
	temp->parentID = p->ID;
	cout << "输入出生日期：";
	cin >> temp->Birth;
	cout << "是否结婚（1/0）：";
	cin >> IsMerry;
	temp->IsMarry = (IsMerry == 1) ? true : false;
	cout << "输入地址：";
	cin >> temp->address;
	cout << "是否死亡（1/0）：";
	cin >> IsDead;
	if (IsDead == 1)
	{
		temp->IsLive = false;
		cout << "输入死亡日期：";
		cin >> temp->Dead_Time;
	}
	else
	{
		temp->IsLive = 1;
	}
	cout << "添加成功!" << endl;
}
//*************************************************************************
void Locate(Member T)   //定位结点
{
	stack<Member> S;
	queue<Member> Q;
	Member p, temp;
	int x = 1, y = 1;
	int len;
	int level = 0;
	p = T;
	while (p || !S.empty())
	{
		if (p)
		{
			S.push(p);
			p = p->firstChild;
		}
		else
		{
			p = S.top();
			S.pop();
			p->x = x++;
			p = p->nextSibling;
		}
	}//定位x
	/*
	while (!S.empty() || p)
	{
		if (p)
		{
			if (!strcmp(name,p->name))
			{
				return p;
			}
			S.push(p);
			p = p->firstChild;
		}
		else
		{
			p = S.top();
			S.pop();
			p = p->nextSibling;
		}
	}
	*/
	p = T;
	Q.push(p);
	while (!Q.empty())
	{
		len = Q.size();
		level++;
		while (len--)
		{
			p = Q.front();
			Q.pop();
			p->y = level;
			if (p->firstChild)
			{
				temp = p->firstChild;
				Q.push(temp);
				temp = temp->nextSibling;
				while (temp)
				{
					Q.push(temp);
					temp = temp->nextSibling;
				}
			}
		}
	}
}
//*************************************************************************
void Print_Tree(Member T)  //画树
{
	cout << endl;
	Locate(T);
	Member p, temp, draw;// , pre;
	queue<Member>Q;
	int count = 0, num = 0, len, pre = -1;
	p = T;
	Q.push(p);
	queue<Member> W;
	while (!Q.empty())
	{
		count = 0;
		//line = 0;
		len = Q.size();
		while (len--)
		{
			p = Q.front();
			Q.pop();
			W.push(p);
			//W.push(p->firstChild);
			count = (p->x - count);
			num = count * 1;
			while (num--)
			{
				if (pre == p->parentID)
				{
					cout << "-";
				}
				else
				{
					cout << " ";
				}
			}
			cout << p->name;
			if (p->firstChild)
			{
				temp = p->firstChild;
				Q.push(temp);
				temp = temp->nextSibling;
				while (temp)
				{
					Q.push(temp);
					temp = temp->nextSibling;
				}
			}
			pre = p->parentID;
			
		}
		count = 0;
		cout << endl;
		while (!W.empty())
		{
			draw = W.front();
			W.pop();
			count = (draw->x - count);
			num = count * 1;
			while (num--)
			{
				cout << " ";
			}
			if (draw->firstChild)
			{
				cout << " |   ";
			}
			else
			{
				cout << "       ";
			}
		}
		cout << endl << endl;
	}
}
//*************************************************************************
void Write_File(Member T)
{
	fstream file;
	file.open(OutFile, ios::out);
	if (file.fail())
	{
		cout << "文件打开失败";
		return;
	}
	if (T == NULL)
	{
		return;
	}
	queue<Member>Q;
	Member p, q;
	p = T;
	Q.push(p);
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();
		file << p->ID << "\t" << p->name << "\t\t" << p->parentID << "\t" << p->Birth << "\t\t";
		if (p->IsMarry)
		{
			file << "1";
		}
		else
		{
			file << "0";
		}
		file << "\t" << p->address << "\t\t";
		if (p->IsLive)
		{
			file << "1" << endl;
		}
		else
		{
			file << "0\t" << p->Dead_Time << endl;
		}
		if (p->firstChild != NULL)
		{
			Q.push(p->firstChild);
			q = p->firstChild->nextSibling;
			while (q)
			{
				Q.push(q);
				q = q->nextSibling;
			}
		}
	}
	file.close();
}
//*************************************************************************