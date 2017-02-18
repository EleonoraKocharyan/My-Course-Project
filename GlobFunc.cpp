#include "point.h"
#include "GlobFunc.h"
#include "Graphica.h"
#include <iostream>

std::ostream& operator <<(std::ostream &out, const std::vector<int> &v)
{
	for(int i=0; i<v.size(); ++i)
	out<<v[i]<<" ";
	out<<std::endl;
	return out;
}
std::ostream& operator <<(std::ostream &out, const std::vector<point> &v)
{
	for(int i=0; i<v.size(); ++i)
	out<<i<<": "<<v[i];
	out<<std::endl;
	return out;
}

std::istream& operator >>(std::istream &in, std::vector<point> &v)
{
	int n;
	std::cout<<"number of points : ";
		in>>n;
	for(int i=0; i<n; ++i)
	{
		point p;
		in>>p;
		v.push_back(p);
	}
	return in;
}

GraphicalView* view = new GraphicalView;

void mouseFunction(int button, int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		double xd=x;
		double yd=y;
	
		view->x=xd/300-1;
		view->y=1-yd/300;
	}
}

void motionFunction(int x, int y)
{
	double xd=x;
	double yd=y;
	
	double dx=xd/300-1-view->x;
	double dy=1-yd/300-view->y;

	view->translate(dx,dy);
	
	view->x=xd/300-1;
	view->y=1-yd/300;
}

void reshapeFunction( int newWidth, int newHeight )
{
	// Prepare space for pixels in buffers
	glViewport( 0, 0, newWidth, newHeight );

	// Setup projection matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -newWidth / 600.0, newWidth / 600.0,
			-newHeight / 600.0, newHeight / 600.0,
			-1, 1 );
}

void Display()
{
	view->draw();
}

void GiftWrapping(const std::vector<point> &v)
{
	GraphicalObject *temp_obj;
	
	int minPoint=0;
	for(int i=0; i<v.size(); ++i) // searching for leftmost point in the hull
	{
		if(v[i].x<v[minPoint].x ||
		   v[i].x==v[minPoint].x && v[i].y<v[minPoint].y)
		{
			minPoint=i;
		}
		else
			view->scene->removeObj(temp_obj);
	}
	
	GraphicalObject* p=new GraphicalPoint(v[minPoint]);
	(view->scene)->addObj(p);	
	point imgpoint(v[minPoint].x, v[minPoint].y-1);
	double minCos=2;

	int nextCHpoint=minPoint;
	for(int i=0; i<v.size(); ++i) // searching for the second element of the hull
	{
		double currCos=v[minPoint].CosAngle(imgpoint,v[i]);
		if(currCos<minCos)
		{
			minCos=currCos;
			nextCHpoint=i;
		}
		else 
			if(currCos==minCos)
			{
				if(v[minPoint].DistanceFrom(v[nextCHpoint])>v[minPoint].DistanceFrom(v[i]))
				nextCHpoint=i;
			}

	}
	
	std::vector<bool> used(v.size(),false);

	point currCHpoint=v[minPoint];
	point prevCHpoint;
	
	int j=1;
	
	//the main search 
	while(nextCHpoint!=minPoint)
	{ 
		p=new GraphicalPoint(v[nextCHpoint]);
		view->scene->addObj(p);

		prevCHpoint=currCHpoint;
		currCHpoint=v[nextCHpoint];
		
		used[nextCHpoint]=true;
		minCos=2;
	
		for(int i=0; i<v.size(); ++i)
		{
			if(used[i]==false)
			{ 
				double currCos=currCHpoint.CosAngle(prevCHpoint,v[i]);
				if(currCos<minCos)
				{
					minCos=currCos;
					nextCHpoint=i;
				}
				else 
					if(currCos==minCos)
					{
						if(currCHpoint.DistanceFrom(v[nextCHpoint])>currCHpoint.DistanceFrom(v[i]))
						nextCHpoint=i;
					}
			}
		}
		++j;
	}
	//Display();
}