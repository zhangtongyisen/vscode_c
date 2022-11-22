#include<iostream>
#include<string>
using namespace std;
int main()
{
    string str;
    int i=0,n=1,j=0,len;
    double b=0;
    getline(cin,str);
    len=str.length();
    for(i=0;i<len;i++)
    {
    if(isalpha(str[i]))
        j++;
    }
    for(i=1;i<len;i++)
    if(i!=0&&(isalpha(str[i])&&!isalpha(str[i-1])))
        n++;
    b=j*1.0/n;
   cout<<b<<endl;
    
}
