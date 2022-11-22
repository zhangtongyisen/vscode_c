//
//  main.cpp
//  课程平均数
//
//  Created by 张童义森 on 2018/11/29.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include <stdio.h>
double Ave(double c[7]);
int main()
{
    // insert code here...
    int i,n,T;
    double ave,b[7];
    char a[20];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",a);
        for(i=0;i<8;i++)
        {
            scanf("%lf",&b[i]);
            
        }
        ave=Ave(b);
        printf("%s: %f\n",a,ave);
    }
    return 0;
}
double Ave(double c[7])
{
    int i;
    double sum=0,u;
    for(i=0;i<=7;i++)
    {   scanf("%lf",&c[i]);
        sum=sum+c[i];
        u=sum/8;
    }
    return u;
}

