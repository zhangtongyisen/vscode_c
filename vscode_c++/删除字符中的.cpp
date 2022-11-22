//
//  main.cpp
//  删除字符中的*
//
//  Created by 张童义森 on 2018/11/29.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include <stdio.h>
int shanchu(char a[100]);
int main() {
    // insert code here...
    int T;
    char a[100];
    scanf("%d",&T);
    getchar();
    while(T--)
    {   gets(a);
            shanchu(a);
    }
    return 0;
}
int shanchu(char s[])
{
    int i,j=0;
    char b[100];
    
    for(i=0;i<=100;i++)
    { if(s[i]!='*')
    {
        b[j]=s[i];
        j++;
    }
}
    printf("%s\n",b);
    return 0;
}
