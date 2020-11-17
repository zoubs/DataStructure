//JSON
#include<iostream>
#include<map>
#include<string>
#include<fstream>
using namespace std;
//键值对类型 
map<string, string> mp;

void format(string& s)
{
	//把字符串s中的转义字符\删除，并保留其下一个字符
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '\\')
		{
			s.erase(s.begin() + i);
		}
	}
}

//分离键名与键值
void deal(string& json, string& add)
{
	int count, i, j;
	string key, value;
	for (i = 0; i < json.size(); i++)
	{
		if (json[i] == '"')   //双引号开始
		{
			j = json.find(':', i + 1);   //从i+1位置开始找 ':'
			//找到:  即键名结束后是value
			key = json.substr(i + 1, j - i - 2);  //截取""里面的子串 
			if (add == "")    //上一层没有查询即小数点的形式
			{
				key = add + key;
			}
			else		   //上一层有 
			{
				key = add + '.' + key;
			}
			if (json[j + 1] == '"')    //说明后面不是对象是字符串
			{
				if (json.find(',', j + 1) != -1)   //能找到',' 说明
				{
					i = json.find(',', j + 1);
				}
				else                         //没找到，说明结束了
				{
					i = json.size() - 1;
				}
				value = json.substr(j + 2, i - j - 3);
				format(key);   //去转义字符
				format(value);
			}
			else
			{   //冒号后面是左括号{,所以后面是对象
				count = 1;
				i = j + 2; 					//{ 之后一个字符开始
				while (count != 0)         //找到对应后面的} 
				{
					if (json[i] == '{')
					{
						++count;
					}
					if (json[i] == '}')
					{
						--count;
					}
					i++;
				}
				value = json.substr(j + 1, i - j - 1);  //此时的value是一个对象
				//递归实现
				deal(value, key);
			}
			mp[key] = value;
		}
	}
}
int main()
{
	//打开文件
	fstream file;
	file.open("JSON.txt", ios::in);
	if (file.fail())
	{
		cout << "打开文件失败" << endl;
		exit(0);
	}
	//首先去除空白符号等
	string s, json;
	//json保存的是最终去掉空格等之后的字符串
	string::iterator it;
	int n, m;
	file >> n >> m; //得到输入和查询的个数 
	getline(file, s);   //第一行输入数字那个 
	for (int i = 0; i < n; i++)
	{
		getline(file, s);
		//把该行的空格换行抹去
		for (it = s.begin(); it != s.end();)
		{
			//将s里面每一个字符都遍历一次
			if (isspace(*it)) //判断字符为空格换行符制表符则返回非0值，否则返回0 
			{
				s.erase(it);  //删除迭代器位置的一个字符
			}
			else
			{
				++it;         //向后移一个 
			}
		}
		//抹去空格之后,都加到json上面
		json += s;
	}
	string add;
	add = "";
	deal(json, add);
	//开始查询 
	for (int i = 0; i < m; i++)
	{
		getline(file, s);
		if (mp.find(s) != mp.end())   //找到了
		{
			if (mp[s][0] == '{')
			{
				cout << "OBJECT" << endl;
			}
			else
			{
				cout << "STRING " << mp[s] << endl;
			}
		}
		else
		{
			cout << "NOTEXISTENCE" << endl;
		}
	}
	file.close();
	cout << endl;
	system("pause");
	return 0;
}