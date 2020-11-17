#include<stdio.h>
#include<stdlib.h> 

typedef struct ball
{
	int pos;    //位置 
	int dir;    //运动方向 
}BL;

int main()
{
	
	int n,l,t,i,j;
	BL *a;
	scanf("%d %d %d",&n,&l,&t);
	a = (BL *)malloc(n*sizeof(BL));
		
	for(i=0;i<n;i++)   //初始化位置 
	{
		scanf("%d",&(a[i].pos));
		a[i].dir = 1;
	}
	
	while(t--)
	{
		for (i=0;i<n;i++)
		{
			for(j=i+1;j<n;j++)
			{
				if(a[i].pos == a[j].pos)
				{
					a[i].dir *=(-1);
					a[j].dir *=(-1);
				}
			}
			if(a[i].pos==0||a[i].pos==l)
			{
				a[i].dir *=(-1);
			}
		}

		for(i=0;i<n;i++)
		{
			a[i].pos += a[i].dir;
			
		}
	}
	
	for(i=0;i<n;i++)
	{
		printf("%d ",a[i].pos); 
		
	}
	
	return 0;
	
 } 
