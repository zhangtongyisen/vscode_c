//
//  main.cpp
//  删除字符串中的非小写字母
//
//  Created by 张童义森 on 2018/12/4.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include<stdio.h>
int main()
{
    int T,i,j,n;
    char a[100];
    scanf("%d",&T);
    getchar();
    while(T--)
    {
        gets(a);
        for(j=0;a[j]!=0;j++)
        {
            if(a[j]>='a'&&a[j]<='z')
                printf("%c",a[j]);
        }
        printf("\n");
    }
    
}
