#include<iostream>
using namespace std;
class vehicle
{
public:
    vehicle(int a,string yan);
    void display();
protected:
    int num;
    string color;
};
vehicle::vehicle(int a,string yan)
{
    num=a;
    color=yan;
}
void vehicle::display()
{
    cout<<"vehicleID="<<num<<" vehicleName="<<color<<endl;
}
class bike:public vehicle
{
public:
    bike(int a,string yan,int b):vehicle(a,yan),weight(b){}
    void display();
private:
    int weight;
};
void bike::display()
{
    cout<<"vehicleID="<<num<<" vehicleName="<<color<<" weight="<<weight<<endl;
}
int main()
{
    int ID;
    string name;
    int weight;
    
    cin>>ID>>name;
    
    class vehicle vehicle1(ID,name);
    vehicle1.display();
    cout<<endl;
    cin>>ID>>name>>weight;
    class bike bike1(ID,name,weight);
    bike1.display();
    cout<<endl;
    
    return 0;
}
