//
//  main.cpp
//  数据交换
//
//  Created by 张童义森 on 2018/11/4.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include <stdio.h>

int main()
{
    // insert code here...
    int a[50],w;
    int i,n = 0,j,k = 0,t;
    while(scanf("%d",&j)!=EOF)
    {if(n==0)
            break;
            for(i=0;i<j;i++)
                scanf("%d",&a[i]);
            w=a[0];
        for(i=0;i<n;i++)
        {
            if(a[i]<=w)
                k=i;
            w=a[k];
            
        }
        if(w!=a[0])
        {t=a[k];a[k]=a[0];a[0]=t;}
        for(i=0;i<n;i++)
            if(i==0)
                printf("%d",a[i]);
            else printf(" %d",a[i]);
        printf("\n");
        }
    return 0;
}
