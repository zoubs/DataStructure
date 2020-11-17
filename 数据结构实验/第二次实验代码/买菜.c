#include <stdio.h>

int main()
{
	int n,i,j;
	long long a[2000],b[2000],c[2000],d[2000];
	long long time = 0;
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%lld %lld",&a[i],&b[i]);
	for(j=0;j<n;j++)
		scanf("%lld %lld",&c[j],&d[j]);
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
		{
			if(a[i]<d[j])
			{
				if((b[i]>c[j]) && (c[j]>=a[i]) && (d[j]>=b[i]))
				{
					time += (b[i]-c[j]);
				}
				else if((a[i]>=c[j]) && (d[j]>=b[i]))
				{
					time += (b[i]-a[i]);
				}
				else if((a[i]>=c[j]) && (b[i]>=d[j]))
				{
					time += (d[j]-a[i]);	
				}
				else if((c[j]>=a[i]) && (b[i]>=d[j]))
				{
					time += (d[j]-c[j]);
				}
			}
		}
	}
	printf("%lld",time);
	return 0;
} 
