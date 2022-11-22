//
//  main.cpp
//  完数
//
//  Created by 张童义森 on 2018/11/29.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include <stdio.h>
int wanshu(int x);
int main()
{
    // insert code here...
    int a,x;
    while(scanf("%d",&x)!=EOF)
    { a=wanshu(x);
        if(a==1)printf("Yes\n");
        else printf("No\n");}
    return 0;
}
int wanshu(int x)
{
    int i,s=0;
    for(i=1;i<x;i++)
    {
        if(x%i==0)
            s=s+i;
    }
    if(s==x)
        return 1;
    else return 0;
}
