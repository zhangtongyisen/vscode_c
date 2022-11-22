//
//  main.cpp
//  快速排序
//
//  Created by 张童义森 on 2021/10/9.
//

#include <stdio.h>
#include "stdlib.h"
int setpartition(int a[],int n){
    int pivotkey,low=0,low0=0,high=n-1,high0=n-1,flag=1,k=n/2,i;
    int s1=0,s2=0;
    while(flag){
        pivotkey=a[low];
            while(low<high){
                while(low<high&&a[high]>=pivotkey) --high;
                a[low]=a[high];
                while(low<high&&a[low]<=pivotkey) ++low;
                a[high]=a[low];
            }
            a[low]=pivotkey;
            if(low==k-1){
                flag=0;
            }
            else{
                if(low<k-1){
                    low0=++low;
                    high=high0;
                }
                else{
                    high0=--high;
                    low=low0;
                }
            }
    }
    for(i=0;i<k;i++)s1+=a[i];
    for(i=k;i<n;i++)s2+=a[i];
    return s2-s1;
}
int main(){
    int p;
    int a[10]={8,2,4,19,50,64,39,25,19,33};
    p=setpartition(a,10);
    printf("%d\n",p);
}
    
