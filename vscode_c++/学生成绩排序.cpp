//
//  main.cpp
//  学生成绩排序
//
//  Created by 张童义森 on 2018/12/13.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include<stdio.h>
struct cjd
{
    double xh;
    char xm[12];
    int cj;
};
struct cjd a[100],temp={0};
int main()
{
    int i,j,n,k;
    while(scanf("%d",&n)!=EOF)
    {
        for(i=0;i<n;i++)
        {
            scanf("%lf%s%d",&a[i].xh,a[i].xm,&a[i].cj);
        }
        for(i=0;i<n;i++)
        {
            k=i;
            for(j=i+1;j<n;j++)
            {
                if(a[k].cj<a[j].cj)
                {
                    k=j;
                }
            }
            if(k!=i)
            {
                temp=a[k];
                a[k]=a[i];
                a[i]=temp;
            }
        }
        for(i=0;i<n;i++)
        {
            printf("%.0lf %s %d\n",a[i].xh,a[i].xm,a[i].cj);
        }
    }
    return 0;
}
