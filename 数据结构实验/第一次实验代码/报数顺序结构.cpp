#include<stdio.h>
#include<stdlib.h>

int main()
{
	int* p;
	int n, m,i,length=0,temp=0;
	scanf_s("%d %d", &n, &m);
	if (m >= n || m <= 0 || n <= 0)  // 判断输入是否合法
	{
		printf("输入不合法");
		return -1;
	}
	p = (int*)malloc(n * sizeof(int));  // 开辟数组空间
	if (!p)
	{
		printf("空间分配失败");
		return -1;
	}
	for (i = 0; i < n; i++)  // 初始化人物信息
	{
		p[i] = i + 1;
	}
	length = n;  // length 代表剩余人数
	i = 0;
	while (length > 0)  // 所有人均出列时结束循环
	{
		if (p[i] != 0)   // p[i]为零代表第i人已出列，不再参与报数
		{
			temp++;
		}
		if (temp == m)
		{
			printf("%d ", p[i]);
			p[i] = 0;    // 将要出列的人物标记为 0
			length--;
			temp = 0;
		}
		i++;
		if (i >= n)  // 遍历到最后一个人之后，回到第一人继续遍历
		{
			i = 0;
		}
	}
	/*for (i = 0; i < n; i++)  //打印最后一人的信息
	{
		if (p[i] != 0)
		{
			printf("%d", p[i]);
			break;
		}
	}*/
	return 0;
}