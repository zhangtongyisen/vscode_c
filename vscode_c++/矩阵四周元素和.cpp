//
//  main.cpp
//  矩阵四周元素的和
//
//  Created by 张童义森 on 2018/11/4.
//  Copyright © 2018年 张童义森. All rights reserved.
//

#include <stdio.h>
#define N 10
int main() {
    // insert code here...
    int a[N][N],i,j,n,z=0,x=0,c=0,v=0,s=0;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {scanf("%d",&a[i][j]);}
        
    }
    for(i=0;i<n;i++)
    { x=x+a[i][0];}
    for(j=0;j<n;j++)
    {z=a[0][j];}
    for(i=0;i<n;i++)
    {c=a[i][n-1];}
    for(j=0;j<n;j++)
    {v=a[n-1][j];}
    s=z+x+c+v-a[0][0]-a[n-1][n-1]-a[0][n-1]-a[n-1][0];
    printf("%d",s);
    return 0;
}
