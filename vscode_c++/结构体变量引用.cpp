//
//  main.cpp
//  结构体变量的引用
//
//  Created by 张童义森 on 2018/12/10.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include <stdio.h>
struct date
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
};
struct person
{
    int a[10];
    char name[10];
    char zhiwei[10];
    struct date birthday;
    int gongzi[3];
    int total;
};
int main()
{
    struct person p1,p2,p3;
    int i,sum;
    scanf("%d %s %s",&p1.a,p1.name,p1.zhiwei);
    for(i=0;i<3;i++)
        scanf("%d",&p1.gongzi[i]);
    scanf("%d %d %d",&p1.birthday.year,&p1.birthday.month,&p1.birthday.day);
    scanf("%d %s %s",p2.a,p2.name,p2.zhiwei);
    for(i=0;i<3;i++)
        scanf("%d",&p2.gongzi[i]);
    scanf("%d %d %d",&p2.birthday.year,&p2.birthday.month,&p2.birthday.day);
    scanf("%d %s %s",p3.a,p3.name,p3.zhiwei);
    for(i=0;i<3;i++)
        scanf("%d",&p3.gongzi[i]);
    scanf("%d %d %d",&p3.birthday.year,&p3.birthday.month,&p3.birthday.day);
    for(i=0,sum=0;i<3;i++)
        sum=sum+p1.gongzi[i];
    p1.total=sum;
    if(p1.total>5000)
    {printf("姓名：%s，",p1.name);
        printf("出生日期：%d.%d.%d，",p1.birthday.year,p1.birthday.month,p1.birthday.day);
        printf("工资：%d\n",p1.total);}
    for(i=0,sum=0;i<3;i++)
        sum=sum+p2.gongzi[i];
    p2.total=sum;
    if(p2.total>5000)
    {printf("姓名：%s，",p2.name);
    printf("出生日期：%d.%d.%d，",p2.birthday.year,p2.birthday.month,p2.birthday.day);
        printf("工资：%d\n",p2.total);}
    for(i=0,sum=0;i<3;i++)
        sum=sum+p3.gongzi[i];
    p3.total=sum;
    if(p3.total>5000)
    {printf("姓名：%s，",p3.name);
    printf("出生日期：%d.%d.%d，",p3.birthday.year,p3.birthday.month,p3.birthday.day);
        printf("工资：%d\n",p3.total);}
}

