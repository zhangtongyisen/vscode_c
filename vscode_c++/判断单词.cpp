#include<iostream>
#include<string>
using namespace std;
int main()
{
    string str1,str2;
    int i,p,len1,len2;
    cin>>str1;
    cin>>str2;
    len1=str1.length();
    len2=str2.length();
    for(i=0;i<len1;i++)
    {
        for(p=0;p<len2;p++)
        {
            if(str1[i]==str2[p])
                str2.erase(p,1);
        }
    }
    if(str2.empty())
        cout<<"yes"<<endl;
    else cout<<"no"<<endl;
}
