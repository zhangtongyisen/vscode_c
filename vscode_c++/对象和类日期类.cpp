#include<iostream>
#include<iomanip>
using namespace std;
class Date
{
public:
    Date();
    Date(int a,int b,int c);
    void assign(int a,int b,int c);
    void display();
    bool leap_year();
    void increment(int n);
private:
    int day,month,year;
};
Date::Date()
{
    day=1;
    month=1;
    year=2008;
}
Date::Date(int a,int b,int c)
{
    day=a;
    month=b;
    year=c;
}
void Date::assign(int a, int b, int c)
{
    day=a;
    month=b;
    year=c;
    if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
    {
        if(day>31)
            day=day-31;
    }
    if( month==4||month==6||month==9||month==11)
    {
        if(day>30)
        {day=day-30;}
    }
    if(year/4==0)
    {
        if(month==2)
        {
            if(day>29)
            {
                day=day-29;
            }
        }
    }
    if(year/4!=0)
    {
        if(month==2)
        {
            if(day>28)
            {
                day=day-28;
            }
        }
    }
    if(month>12)
    {
        month=month%12;
        if(month%12==0)
            month=12;
    }
}
void Date::display()
{
    cout<<day<<"/"<<month<<"/"<<year<<endl;
}
bool Date::leap_year()
{
    if(year/4==0)
        return true;
    else return false;
}
void Date::increment(int n)
{
    if(month==1||month==3||month==5||month==7||month==8||month==10)
    {
        if(day<=31-n)
            day=day+n;
        else {month=month+1;
            day=day+n-31;}
    }
    if( month==4||month==6||month==9||month==11)
    {
        if(day<=30-n)
        day=day+n;
        else {month=month+1;day=day+n-30;}
        
    }
    if(year/4==0)
    {
        if(month==2)
        {
            if(day<=29-n)
            {
                day=day+n;
            }
            else {month=month+1;day=day+n-30;}
        }
    }
    if(year/4!=0)
    {
        if(month==2)
        {
            if(day<=28-n)
            {
                day=day+n;
            }
            else {month=month+1;day=day+n-29;}
        }
    }
    if(month==12)
    {
        if(day<=31-n)
        {
            day=day+n;
        }
        else {
            year=year+1;
            month=1;
            day=day+n-31;}
    }
}
int main()
{
    Date date1,date2(1,5,2016),date3;
    int n,a,b,c;
    cin>>a>>b>>c;
    date3.assign(a,b,c);
    cin>>n;
    date1.display();
    date2.display();
    date3.display();
    date3.increment(n);
    date3.display();
    return 0;
}
