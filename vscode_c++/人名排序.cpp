#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main()
{
    string str[3];
    getline(cin,str[0],'\n');
    getline(cin,str[1],'\n');
    getline(cin,str[2],'\n');
    sort(str,str+3);
    cout<<str[0]<<endl<<str[1]<<endl<<str[2]<<endl;
}
