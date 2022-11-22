//
//  main.cpp
//  复数的加减运算
//
//  Created by 张童义森 on 2018/12/10.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include<stdio.h>

struct fushu
{
    double a;
    double b;
};

int main()
{   struct fushu f1,f2,f3;
    int n;
    char c;
    scanf("%d\n",&n);
    while(n--)
    {
        
        scanf("(%lf%lfi)",&f1.a,&f1.b);
        
        scanf("%c",&c);
        
        scanf("(%lf%lfi)",&f2.a,&f2.b);
        
        getchar();
        
        
        if(c=='+')
        {
            f3.a=f1.a+f2.a;
            
            f3.b=f1.b+f2.b;
        }
        
        if(c=='-')
        {
            f3.a=f1.a-f2.a;
            
            f3.b=f1.b-f2.b;
        }
        
        if(f3.b<0)
            printf("%.2lf%.2lfi\n",f3.a,f3.b);
        
        if(f3.b>0)
            printf("%.2lf+%.2lfi\n",f3.a,f3.b);
        
        
    }
    
    return 0;
}
