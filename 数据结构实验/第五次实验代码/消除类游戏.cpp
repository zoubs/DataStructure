#include<stdio.h>
typedef struct node
{
	int num;   //颜色 
	int flag;  //代表该单元是否被消除 
}A;

int main()
{
	int n,m;
	int i,j;
	A a[30][30];
	scanf("%d %d",&n,&m); 
	for(i=0;i<n;i++)   //初始化 
	{
		for(j=0;j<m;j++)
		{
			scanf("%d",&(a[i][j].num));
			a[i][j].flag=0;
		}
	}    
	for(i=1;i<n;i++)   //判断一下棋盘边缘的第0列和第m-1列消除情况 
	{
		if(a[i][0].num==a[i-1][0].num&&a[i][0].num==a[i+1][0].num)  //判断第0列的消除情况，并加标记 
		{
			a[i][0].flag=1;
			a[i-1][0].flag=1;
			a[i+1][0].flag=1;
		}
		if(a[i][m-1].num==a[i-1][m-1].num&&a[i][m-1].num==a[i+1][m-1].num)  //判断第m-1列的消除情况，并加标记 
		{
			a[i][m-1].flag=1;
			a[i-1][m-1].flag=1;
			a[i+1][m-1].flag=1;
		}
		
	}
	for(j=1;j<m;j++)   //判断一下棋盘边缘的第0行和第n-1列消除情况 
	{
		if(a[0][j].num==a[0][j-1].num&&a[0][j].num==a[0][j+1].num)    //判断第0行的消除情况，并加标记 
		{
			a[0][j].flag=1;
			a[0][j-1].flag=1;
			a[0][j+1].flag=1;
		}
		if(a[n-1][j].num==a[n-1][j-1].num&&a[n-1][j].num==a[n-1][j+1].num)  //判断第n-1行的消除情况，并加标记 
		{
			a[n-1][j].flag=1;
			a[n-1][j-1].flag=1;
			a[n-1][j+1].flag=1;
		}
	} 
	 
	
	
	for(i=1;i<n-1;i++)   //判断棋盘中间的消除情况 
	{
		for(j=1;j<m-1;j++)
		{
			if(a[i][j].num==a[i][j-1].num && a[i][j].num==a[i][j+1].num)
			{
				a[i][j].flag=1;
				a[i][j-1].flag=1;
				a[i][j+1].flag=1;
			}
			if(a[i][j].num==a[i-1][j].num && a[i][j].num==a[i+1][j].num)
			{
				a[i][j].flag=1;
				a[i-1][j].flag=1;
				a[i+1][j].flag=1;
				
		    }  
		}
	}
	for(i=0;i<n;i++)   //消除带标记的棋子 
	{
		for(j=0;j<m;j++)
		{
			if(a[i][j].flag)
			  a[i][j].num=0;
		}
	}
	
	
	for(i=0;i<n;i++)   //输出结果 
	{
		for(j=0;j<m;j++)
		{
			printf("%d ",a[i][j].num);
		}
		printf("\n");
	}
	
	return 0;
 } 
