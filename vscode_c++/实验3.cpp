#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
using namespace std;
 
int main()
{
    int sst=0;//初始阈值
    int n=0;//传输轮次
    int m=0;//快重传的报文段
    int i=1;//打印传输轮次
    int cwnd=1;
    printf("\n");
    printf("ssthrest的初始值:\n");
    scanf("%d",&sst);
    printf("需要模拟的传输轮次数n:\n");
    scanf("%d",&n);
    printf("快重传的值m:\n");
    scanf("%d",&m);
    int t=0;
    int temp=0;
    //慢开始
    printf("\n拥塞窗口cwnd:");
    printf("\n慢开始:");
    if(cwnd<sst){
        for(cwnd;cwnd<sst;)
        {
            printf("%d  ",cwnd);
            t++;
            cwnd=2*cwnd;
        }
        cwnd=sst;
        printf("%d  ",cwnd);
    }
    //拥塞避免
    printf("\n拥塞避免:");
    if(cwnd==sst){
        for(cwnd;cwnd<m;){
            cwnd++;
            printf("%d  ",cwnd);
            t++;
        }
    }
    //快重传
    if(cwnd==m){
        sst=cwnd/2;
        printf("\n快重传慢开始:");
        temp=t;
        for(i=t;i<=n;) {
            for(cwnd=1;cwnd<sst;)
            {
                printf("%d  ",cwnd);
                i++;
                t++;
                cwnd=2*cwnd;
            }
            cwnd=sst;
            for(;i<n;i++) {
                printf("%d  ",cwnd);
                cwnd++;
                t++;
            }
        }
    }
    cwnd=sst;
    printf("\n快恢复:");
    for(i=temp;i<n;i++){
        printf("%d  ",cwnd);
        cwnd++;
    }
}
