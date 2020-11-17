#include <stdio.h>
#include <stdlib.h>

int main()
{
    long int r,y,g,t;
    int n,k,i;
	int time = 0;
    scanf("%ld %ld %ld",&r,&y,&g);
    scanf("%d",&n);
    for(i=0;i<n;i++)
        {
        	scanf("%d %d",&k,&t);
            if(k==0)
				time += t;
			if(k==1)  
				time += t;
            if(k==2)
            	time  = time + t + r;
            if(k==3)
            	time += 0; 
        }
    printf("%d",time);
    return 0;
}
