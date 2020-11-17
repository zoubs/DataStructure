#include<iostream>
#include<iomanip>

using namespace std;

int main()
{
	int a[30];
	int i, temp, score = 0;
	for (i = 0; i < 30; i++)
	{
		cin >> a[i];
		if (a[i] == 0)
		{
			break;
		}
	}
	for (i = 0; i < 30; i++)
	{
		if (a[i] == 0)
		{
			break;
		}
		if (a[i] == 1)
		{
			temp = 1;  //记录上次得分
			score += temp;
		}
		else if (a[i] == 2)
		{
			if (i == 0 || a[i-1] == 1)
			{
				temp = 2;
				score += temp;
			}
			else
			{
				temp += 2;
				score += temp;
			}
		}
	}
	cout << score << endl;
	system("pause");
	return 0;
}
