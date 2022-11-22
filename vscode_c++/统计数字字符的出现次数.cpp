//
//  main.cpp
//  统计数字字符的出现次数
//
//  Created by 张童义森 on 2018/11/29.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include <stdio.h>
int shu(char x[]);
int main()
{
    // insert code here...
    char a[100];
    int b,T;
    scanf("%d",&T);
    while(T--)
    {   gets(a);
        b=shu(a);
    }
    printf("%d",b);
    return 0;
}
int shu(char x[])
{
    
    int i,j;
    for(i=0;i<100;i++)
        if(x[i]>='0'&&x[i]<='9')
            j++;
    printf("%d",j);
    return j;
}
