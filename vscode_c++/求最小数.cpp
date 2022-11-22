#include<iostream>
#include<string>
using namespace std;
int miniElement(int str1[],int n);
double miniElement(double str2[],int n);
int main()
{
    int str1[20];
    double str2[20];
    int i,q,n1,a,n2;
    double d;
    cin>>n1;
    for(i=0;i<n1;i++)
    {
        cin>>str1[i];
    }
    q=miniElement(str1,n1);
    
    cin>>n2;
    getchar();
    for(a=0;a<n2;a++)
    {
        cin>>str2[a];
    }
    d=miniElement(str2,n2);
    cout<<q<<endl;
    cout<<d<<endl;
    return 0;
}

int miniElement(int str1[],int n)
{
    int b,i,q,min;
    for(i=0;i<n-1;i++)
        for(q=0;q<n-1-i;q++)
        {
            if(str1[q]>str1[q+1])
            {
                b=str1[q];
                str1[q]=str1[q+1];
                str1[q+1]=b;
            }
            
        }
    min=str1[0];
    return min;
}

double miniElement(double str2[],int n)
{
    int b,i,q;
    double min;
    for(i=0;i<n-1;i++)
        for(q=0;q<n-1-i;q++)
        {
            if(str2[q]>str2[q+1])
            {
                b=str2[q];
                str2[q]=str2[q+1];
                str2[q+1]=b;
            }
            
        }
    min=str2[0];
    return min;
    
}
