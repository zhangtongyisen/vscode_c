#include<stdio.h>
int main()
{
    int a[10];
    int i,j,n;
    for(i=0;i<10;i++)
    {
        scanf("%d",&a[i]);
    }
    for(i=0;i<10;i++)
    {
        for(j=i+1;j<10;j++)
            if(a[i]>a[j])
            {
                n=a[i];
                a[i]=a[j];
                a[j]=n;
            }
    }
    for(i=0;i<10;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}
