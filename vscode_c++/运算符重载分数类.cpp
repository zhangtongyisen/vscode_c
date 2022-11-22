#include <iostream>
#include<iomanip>
using namespace std;

int gcd(int a,int b)
{
    return b==0?a:gcd(b,a%b);
}

class fraction
{
public:
    fraction();
    fraction(int a,int b);
    inline void input();
    void output();
    fraction operator+(fraction t) const;
    fraction operator-(fraction t) const;
    fraction operator*(fraction t) const;
    fraction operator/(fraction t) const;
private:
    int numerator,denominator;
};

fraction::fraction()
{
    numerator=0,denominator=1;
}

fraction::fraction(int a,int b)
{
    numerator=a,denominator=b;
}

inline void fraction::input()
{
    int a,b;
    cin>>a>>b;
    numerator=a,denominator=b;
}

void fraction::output()
{
    int t;
    t=gcd(numerator,denominator);
    cout<<numerator/t<<'/'<<denominator/t<<endl;
}

fraction fraction::operator+(fraction t) const
{
    fraction temp;
    temp.denominator=denominator*t.denominator;
    temp.numerator=numerator*t.denominator+t.numerator*denominator;
    return temp;
}

fraction fraction::operator-(fraction t) const
{
    fraction temp;
    temp.denominator=denominator*t.denominator;
    temp.numerator=numerator*t.denominator-t.numerator*denominator;
    return temp;
}

fraction fraction::operator*(fraction t) const
{
    fraction temp;
    //cout<<'*'<<denominator<<' '<<t.denominator<<' ';
    temp.denominator=denominator*t.denominator;
    temp.numerator=numerator*t.numerator;
    //cout<<temp.numerator<<'/'<<temp.denominator<<endl;
    return temp;
}

fraction fraction::operator/(fraction t) const
{
    fraction temp;
    //cout<<'*'<<denominator<<' '<<t.denominator<<' ';
    temp.denominator=denominator*t.numerator;
    temp.numerator=numerator*t.denominator;
    //cout<<temp.numerator<<'/'<<temp.denominator<<endl;
    return temp;
}

int main()
{
    fraction x1,x2(2,7),x3,y1,y2,z1,z2,z3,z4,z5;
    x3.input();
    y1.input();
    y2.input();
    //    cout<<endl;
    //    x1.output();
    //    x2.output();
    //    x3.output();
    //    y1.output();
    //    y2.output();
    //    cout<<endl;
    z1=x3+y1;   z1.output();
    z2=x3-y1;   z2.output();
    z3=x3*y2;   z3.output();
    z4=x3/y2;   z4.output();
    z5=x1+x2;   z5.output();
    return 0;
}
