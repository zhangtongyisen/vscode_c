//
//  main.cpp
//  最大公约数与最小公约数
//
//  Created by 张童义森 on 2018/12/4.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include <stdio.h>
int hef(int x,int o);
int led(int x,int o);
int main()
{
    int i,j,z,e;
    while(scanf("%d%d",&i,&j)!=EOF)
    {   z=hef(i,j);
        e=led(i,j);
        printf("%d %d\n",z,e);
                    
    }return 0;
}
int hef(int x,int o)
{
    int d,b,a;
    d=x;
    if(x<o)
    {x=o;
        o=d;}
    for(b=2;b<=o;b++)
    {
        if(x%b==0&&o%b==0)
            a=b;
    }
    return a;
}
int led(int x,int o)
{
    int m,g;
    g=hef(x,o);
    m=(x*o)/g;
    return m;
}
