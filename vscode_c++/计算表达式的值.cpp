//
//  main.cpp
//  计算表达式的值3
//
//  Created by 张童义森 on 2018/12/6.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include <stdio.h>
int main()
{
    double eps,a=1,p=1,pi;
    int i;
    while(scanf("%lf",&eps)!=EOF)
    {
        for(i=1;a>eps;i++)
        {
            a=a*i/(2*i+1);
            p=p+a;
        }
        pi=2*p-2*a;
        printf("%lf\n",pi);
        p=1;a=1;
    }
}
