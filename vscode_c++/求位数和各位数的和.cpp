#include<stdio.h>
int main()
{
    int i,j=0,sum=0;
    scanf("%d",&i);
    while(i!=0)
    {
        sum+=i%10;
        i/=10;
        j++;
    }
    printf("%d\n",sum);
    printf("位数=%d",j);
    return 0;
}
