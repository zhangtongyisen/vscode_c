#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
void zhao(int b[],int n);
int main()
{
    int a[20];
    int i,n;
    cin>>n;
    for(i=0;i<n;i++)
    {
        cin>>a[i];
        
    }
    zhao(a,n);
}
void zhao(int b[],int n)
{
    sort(b,b+n);
    cout<<b[n-1]<<' '<<b[n-2];
}
