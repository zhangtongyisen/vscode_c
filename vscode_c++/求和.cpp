#include<stdio.h>

int main()
{
    int n,t,m;
    int max,min;
    scanf("%d%d%d",&n,&t,&m);
    max=min=n;
    if(min>t)
        min=t;
    else if(max<t)
        max=t;
    if(min>m)
        min=m;
    else if(max<m)
        max=m;
    
    printf("%d %d",max,min);
}
