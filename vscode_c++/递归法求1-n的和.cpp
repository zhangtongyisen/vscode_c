//
//  main.cpp
//  递归法求1-n的和
//
//  Created by 张童义森 on 2018/12/4.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include<stdio.h>
int sum(int  n);
int main()
{
    int n,Sum=0;
    scanf("%d",&n);
    Sum=sum(n);
    printf("%d\n",Sum);
}
int sum(int n)
{
    
    if(n==1)
        return 1;
    else
        return n+sum(n-1);
    return n;
}
