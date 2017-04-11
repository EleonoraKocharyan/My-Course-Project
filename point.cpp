#include "point.h"

double point::DistanceFrom(const point &a) const
{
	point vec(a.x-x,a.y-y);
 	return sqrt(vec*vec);
}

double point::CosAngle(const point &a, const point &b) const
{
	point a_vec(a.x-x,a.y-y);
	point b_vec(b.x-x,b.y-y);
	double skl = a_vec * b_vec;
	double adist=DistanceFrom(a);
	double bdist=DistanceFrom(b);
	double cos=skl/(adist*bdist);
	
	if(adist==0||bdist==0) 
	return 2;
	
	else return cos;
}

std::istream &operator >>(std::istream &pin, point &a)
{
	double x=(rand()%1600)-800;
	double y=(rand()%1600)-800;
	a.x=x/1000;
	a.y=y/1000;
	//pin>>a.x>>a.y;
	return pin;
}

std::ostream &operator <<(std::ostream &pout, const point &a)
{
	pout<<"x = "<<a.x<<" y = "<<a.y<<std::endl;
	return pout;
}
	
bool point::operator ==(const point &b) const
{
	return((b.x==x)&&(b.y==y));
}

bool point::operator !=(const point &b) const
{
	return !(*this==b);
}

point &point::operator =(const point& b) 
{
	x=b.x;
	y=b.y;
	return *this;
}

double point::operator *(const point& b) const
{
	return x*b.x+y*b.y;
}












