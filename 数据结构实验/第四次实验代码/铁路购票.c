#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num[100];
	int i,flag,m;
	for(i=0;i<100;i++)
	{
		num[i] = 1;   //代表座位未卖出 
	}
	int length = 100;
	int n,j,k,t,count;
	scanf("%d",&n);
	int p[n];
	for(i=0;i<n;i++)
	{
		scanf("%d",&p[i]);
	}
	for(i=0;i<n;i++)
	{
		if(p[i] < 1 || p[i] > 5)
		{
			printf("输入不合法，一次购票只能买1到5张,请重新输入购买票数");
			i--; 
		}
		else if(p[i]>length)
		{
			printf("余票不足，剩余票数为：%d张，请重新输入购买票数");
			i--;
		}
		else 
		{
			flag = 0;
			for(j=0;j<20;j++) //判断某排是否有连座 
			{
				k=0;
				while(k<6-p[i])  //每次遍历p[i]个连着的座位，每排要遍历这么多次 
					{
						for(t=0;t<p[i];t++)  //判断是否有连着p[i]个座位为空
						{
							if(num[5*j+k+t] != 1)
							{
								flag = 0;
								break; 
							}
							flag = 1;
						}
						if(flag) //说明此时第j+1排有连座可买，不再遍历
						{
							break; 
						}
						k++;
					}
				if(flag)  //买到连座，退出 
				{
					break;
				}
			}
			if(flag)  //买到连座 
				{
					for(t=0;t<p[i];t++)
					{
						printf("%d ",5*j+k+t+1);
						num[5*j+k+t] = 0;   //座位已卖出 
					}
					length -= p[i];
					printf("\n");
				}
			else   //没有连座剩余 
			{
				for(m=0;m<100;m++)
				{
					count = 0;
					if(count<p[i])   //分配p[i]张票 
						{
							if(num[m] == 1)
							{
								printf("%d ",m+1);
								num[m] = 0;  //已卖出 
								count++;
							}
						}
					else
					{
						length -= p[i];  //改变剩余票数 
						printf("\n");
						break;
					} 
				} 
			}
		}
	}
	system("pause"); 
	return 0; 
}
