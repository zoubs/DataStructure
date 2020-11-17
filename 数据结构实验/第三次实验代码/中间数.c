#include <stdio.h>
#include <stdlib.h>
int main()
{
	int n,i,j,value;
	int small,big;
	int *a;
	scanf("%d",&n);
	a = (int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=1;i<n;i++)  //排序 
	{
		
		if(a[i] < a[i-1])
		{
			j = i-1;
			value = a[i];
			while(j>=0 && value <a[j])
			{
				a[j+1] = a[j];
				j--;
			}
			a[j+1] = value;
		} 
		
	} 
	for(i=0;i<n;i++)
	{
		j=i+1;
		while(j < n && a[j]==a[i])
		{
			j++;
		}
		big = n - j;   //比其大的数的个数 
		j = i - 1;
		while(j>=0 && a[j]==a[i])
		{
			j--;
		}
		small = j + 1;  //比其小的数的个数 
		if(small == big)
		{
			printf("%d",a[i]);
			return 0;
		}
	}
	printf("-1");
	//system("pause"); 
	return 0;
} 
