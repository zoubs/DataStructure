#include<iostream>
#include<iomanip>

using namespace std;

int main()
{
	int n, j, i, num, max;
	int* a;
	a = new int[1001];
	if (!a)
	{
		cout << "¿Õ¼ä·ÖÅäÊ§°Ü";
		exit(0);
	}
	for (i = 0; i < 1001; i++)
	{
		a[i] = 0;
	}
	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> num;
		a[num]++;
	}
	for (i = 0; i < 1001; i++)
	{
		max = 0;
		for (j = 0; j < 1001; j++)
		{
			if (a[max] < a[j])
			{
				max = j;
			}
		}
		if (a[max] != 0)
		{
			cout << max << " " << a[max] << endl;
			a[max] = 0;
		}
	}

	delete[]a;
	system("pause");
	return 0;
}