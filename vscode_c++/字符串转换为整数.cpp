#include<iostream>
#include<string>
#include<cmath>
using namespace std;
int main()
{
    string str;
    int i,len,a[10000],b=0,t;
    cin>>str;
    getchar();
    len=str.length();
    for(i=0;i<len;i++)
    {if(str[i]<'0'||str[i]>'9')
    {cout<<"error"<<endl;return 0;}
     
    else
        a[i]=str[i]-'0';
    
    }
    t=len;
    for(i=0;i<len;i++,t--)
    {
        b=b+a[i]*pow(10,t-1);
        
    }
    cout<<b+1<<endl;
}
