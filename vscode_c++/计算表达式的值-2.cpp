//
//  main.cpp
//  计算表达式的值
//
//  Created by 张童义森 on 2018/12/6.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include <stdio.h>
int main()
{
    double x=0.0,sum=0.0,z=3.0,s=4.0;
    int i,j,b,n,c,v;
    while(scanf("%d",&n)!=EOF)
    {
        static_cast<void>(sum=0.0),static_cast<void>(z=3.0),static_cast<void>(s=4.0),x=0.0;
        for(v=1;v<=n;v++)
        {   i=(2*v+1);
            j=(2*v-1);
            z=i*j;
            b=(2*v);
            c=(2*v);
            s=b*c;
            x=z/s;
            sum=sum+x;
            
        }printf("%lf\n",sum);
    }
    return 0;
}
