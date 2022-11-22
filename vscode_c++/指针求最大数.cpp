//
//  main.cpp
//  求最大数（指针）
//
//  Created by 张童义森 on 2018/12/3.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include<stdio.h>
int Max(int *p,int *q,int *o);
int main()
{
    int a,b,c,z;
    int *p ,*q ,*o ;
    while(scanf("%d%d%d",&a,&b,&c)!=EOF)
    {o=&a,p=&b,q=&c;
        z=Max(o,p,q);
        printf("%d\n",z);}
        return 0;
}

int Max(int *p,int *q,int *o)
{   int max;
    if(*p>=*o)
        max=*p;
    {
        if(*p>=*q)
            max=*p;
        else max=*q;
        
    }
    if(*o>=*p)
        max=*o;
    return max;
}
