#ifndef POINT_H
#define POINT_H

#include <ostream>
#include <istream>

struct point
{
	double x;
	double y;
	
	point(double xval=0, double yval=0):x(xval),y(yval)
	{}
	double DistanceFrom(const point &a) const; //finds the distance from point a
	double CosAngle(const point &a, const point &b) const; // finds the cos of the angle with a and b endpoints
	
	friend std::istream &operator >>(std::istream &pin, point &a); //outputs a point
	friend std::ostream &operator <<(std::ostream &pout, const point &a); //inputs a point
	
	bool operator ==(const point &b) const; 
	bool operator !=(const point &b) const;
	double operator *(const point& b) const; //calculates scalar product 
	point &operator =(const point& b);
	
};
#endif
