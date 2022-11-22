#include<iostream>
#include<cmath>
using namespace std;
class  hexagons
{
public:
    hexagons();
    double circumference();
    double area();
    void setSide(double side1);
    double getSide();
private:
    double side,a,length;
};
hexagons::hexagons()
{
    side=10;
    a=0;
    length=0;
}
double hexagons::circumference()
{
    length=side*6;
    return length;
}
double hexagons::area()
{
    a=sqrt(3)*3/2*side*side;
    return a;
}
void hexagons::setSide(double side1)
{
    side=side1;
}
double hexagons::getSide()
{
    
    return side;
}
int main()
{
    double side;
    cin>>side;
    class hexagons hex1;
    cout<<"The side of the hxagons is "<<hex1.getSide()<<endl;
    hex1.setSide(side);
    cout<<"The circumference of the hex1 is "<<hex1.circumference()<<" and area is "<<hex1.area()<<endl;
    
    return 0;
}
