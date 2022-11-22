#include<stdio.h>
int main()
{
    int n,i,m=1;
    while(scanf("%d",&n)!=EOF)
    {for(i=1;i<=n;i++)
    {
        m=m*i;
    }
    printf("%d",m);
        m=1;
    }

    return 0;
}
