#ifndef GRAPHICA_H
#define GRAPHICA_H
#include "point.h"
#include <GL/glut.h>
#include <set>
class Color
{
public:
	double red;
	double green;
	double blue;
	Color(double r=0.9, double g=0.9, double b=0.5):red(r),green(g),blue(b) {}
};

class GraphicalObject
{
public:
	virtual void draw()=0;
	virtual ~GraphicalObject();
};

class GraphicalPoint: public GraphicalObject
{
public:
	point p;
	Color color;
	double p_size;
	
	GraphicalPoint(const point &d, double size=10):p(d),p_size(size) { Color c; color=c; }
	GraphicalPoint(const point &d, Color &c, double size=5):p(d), color(c), p_size(size) {}
    void draw();
};

class GraphicalSegment: public GraphicalObject
{
public:
	point endpoint_1;
	point endpoint_2;
	Color color;
	double l_width; 

	GraphicalSegment(const point &p1,const point &p2, double width=5):
		endpoint_1(p1), endpoint_2(p2), l_width(width) { Color c; color=c; }

	GraphicalSegment(const point &p1,const point &p2, Color &c, double width=5):
		endpoint_1(p1), endpoint_2(p2), color(c), l_width(width)  {}
	
	void draw();
	
};

class GraphicalScene
{
public:
	std::set<GraphicalObject*> objs;

	void draw_all();
	void addObj(GraphicalObject* obj);
	void removeObj(GraphicalObject* obj);
};

class GraphicalView
{ 
public:
	double x;
	double y;
	double m[16];
	GraphicalScene* scene;

	GraphicalView();
	void draw();
	void translate( double x, double y);

};

#endif