//
//  main.cpp
//  统计素数的个数
//
//  Created by 张童义森 on 2018/12/3.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include<stdio.h>
#include<math.h>
int main()
{int m,n,i,j,k,s=0,t=0;
    while(scanf("%d%d",&m,&n)!=EOF)
    {if(m>n)
    {k=m;
        m=n;
        n=k;
    }
        for(i=m;i<=n;i++)
        {if(i==2) s++;
        else {
            for(j=2;j<=sqrt(i)+1;j++)
            { t=0;
                if(i%j==0)
                {t=1;
                    break;
                }
            }
            if(t==0) s++;
        }
        }
        printf("%d\n",s);
        s=0;
    }
    return 0;
}    
