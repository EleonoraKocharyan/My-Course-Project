#include "GlobFunc.h"
#include "Graphica.h"
#include <iostream>
#include <string>
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
static bool pressed=false;
std::vector<point> points;
std::vector<GraphicalPoint*> g_points;

void mouseFunction(int button, int state, int x, int y)
{
	if(pressed==false && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		double xd=x;
		double yd=y;
	
		double xx=xd/300-1;
		double yy=1-yd/300;
		
		GraphicalPoint* p=new GraphicalPoint(point (xx,yy));
		points.push_back(point(xx,yy));
		view->scene->addObj(p);
		g_points.push_back(p);
	}
	else
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
	if(pressed==false)
		return;
	
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

void keyfunc(unsigned char key, int x, int y)
{
	switch(key){
	case 'c':
	{   
		pressed=true;
		GiftWrapping();
	}
	}
}


class InterruptAlgorithm : public std::exception
{
};


#define WORK_ITEM_BEGIN( Key ) \
		if ( doneWorkItems.count( Key ) == 0 ) { \
			{
			

#define WORK_ITEM_END( Key ) \
			} \
			doneWorkItems.insert( Key ); \
			throw InterruptAlgorithm(); \
		}


bool GiftWrapping()
{
	static std::set< std::string > doneWorkItems;
	try{
	WORK_ITEM_BEGIN("A")
	for(int i=0; i<points.size(); ++i)
	{
		//WORK_ITEM_BEGIN("A"+std::to_string(i));
		GraphicalPoint* p=new GraphicalPoint(points[i]);
		view->scene->addObj(p);
		g_points.push_back(p);
		//WORK_ITEM_END("A"+std::to_string(i));
	}
	WORK_ITEM_END("A")
	
	static int minPoint=0;
	for(int i=0; i<points.size(); ++i) // searching for leftmost point in the hull
		if(points[i].x<points[minPoint].x || points[i].x==points[minPoint].x && points[i].y<points[minPoint].y)
		   minPoint=i;
	point imgpoint(points[minPoint].x, points[minPoint].y-0.1);
	
	static point prevCHpoint=imgpoint;
	static point currCHpoint=points[minPoint];
	
	int i;
	for( i=0; i<points.size();++i)
		if(i!=minPoint)
			break;
	static int nextCHpoint=i;
	static int tmpCHpoint;
	
	static std::vector<bool> used(points.size(),false);
	static int count=0;
	static double minCos;
	static double currCos;
	
	static GraphicalSegment* Fixed_line;
	static GraphicalSegment *temp_obj;
	
	while(nextCHpoint!=minPoint)
	{ 
		WORK_ITEM_BEGIN("C"+std::to_string(count))
			for(int k=0; k<points.size(); ++k)
				if(used[k]==false && points[k]!=currCHpoint && points[k]!=points[minPoint])
					{tmpCHpoint=k; break;}
				
				minCos=currCHpoint.CosAngle(prevCHpoint,points[tmpCHpoint]);
				Fixed_line=new GraphicalSegment(currCHpoint,points[tmpCHpoint],Color(0.8,0.07,0.2));
				view->scene->addObj(Fixed_line);
				g_points[tmpCHpoint]->color=Color(1,0.2,0);
				
				doneWorkItems.insert("a"+std::to_string(tmpCHpoint)+" "+std::to_string(count));
				doneWorkItems.insert("b"+std::to_string(tmpCHpoint)+" "+std::to_string(count));
				doneWorkItems.insert("c"+std::to_string(tmpCHpoint)+" "+std::to_string(count));
				doneWorkItems.insert("f"+std::to_string(tmpCHpoint)+" "+std::to_string(count));
			WORK_ITEM_END("C"+std::to_string(count))
				
			
			for(int i=0; i<points.size(); ++i)
			{
				if(used[i]==false && i!=tmpCHpoint && points[i]!=currCHpoint)
				{
					WORK_ITEM_BEGIN("a"+std::to_string(i)+" "+std::to_string(count))
						temp_obj=new GraphicalSegment(currCHpoint,points[i]);
						view->scene->addObj(temp_obj); 
						g_points[i]->color=Color(1,1,0);
						currCos=currCHpoint.CosAngle(prevCHpoint,points[i]);
					WORK_ITEM_END("a"+std::to_string(i)+" "+std::to_string(count));
		
					if(currCos<minCos)
					{
						WORK_ITEM_BEGIN("b"+std::to_string(i)+" "+std::to_string(count))
							view->scene->removeObj(Fixed_line); 
							Fixed_line=temp_obj;
							g_points[tmpCHpoint]->color=Color();
							doneWorkItems.insert("f"+std::to_string(i)+" "+std::to_string(count));
						WORK_ITEM_END("b"+std::to_string(i)+" "+std::to_string(count))

						WORK_ITEM_BEGIN("c"+std::to_string(i)+" "+std::to_string(count))
							Fixed_line->color=Color(0.8,0.07,0.2);
							g_points[i]->color=Color(1,0.2,0);
							view->scene->addObj(Fixed_line);
							minCos=currCos;
							tmpCHpoint=i;
							doneWorkItems.insert("f"+std::to_string(i)+" "+std::to_string(count));
						WORK_ITEM_END("c"+std::to_string(i)+" "+std::to_string(count))
					}
					else 
						if(currCos==minCos)
						{
							if(currCHpoint.DistanceFrom(points[nextCHpoint])>currCHpoint.DistanceFrom(points[i]))
							{
								WORK_ITEM_BEGIN("b"+std::to_string(i)+" "+std::to_string(count));
									view->scene->removeObj(Fixed_line); 
									Fixed_line=temp_obj;
									g_points[tmpCHpoint]->color=Color();
									doneWorkItems.insert("f"+std::to_string(i)+" "+std::to_string(count));
								WORK_ITEM_END("b"+std::to_string(i)+" "+std::to_string(count))
							
								WORK_ITEM_BEGIN("c"+std::to_string(i)+" "+std::to_string(count))
									Fixed_line->color=Color(0.8,0.07,0.2);
									g_points[i]->color=Color(1,0.2,0);
									view->scene->addObj(Fixed_line); 
									tmpCHpoint=i;
									doneWorkItems.insert("f"+std::to_string(i)+" "+std::to_string(count));
								WORK_ITEM_END("c"+std::to_string(i)+" "+ std::to_string(count))
							}
						}
						else 
						{
							WORK_ITEM_BEGIN("f"+std::to_string(i)+" "+std::to_string(count))
							view->scene->removeObj(temp_obj);
							g_points[i]->color=Color();
							doneWorkItems.insert("b"+std::to_string(i)+" "+std::to_string(count));
							doneWorkItems.insert("c"+std::to_string(i)+" "+std::to_string(count));
							WORK_ITEM_END("f"+std::to_string(i)+" "+std::to_string(count))
						}
				}
			}
				nextCHpoint=tmpCHpoint;
				++count;
				prevCHpoint=currCHpoint;
				currCHpoint=points[nextCHpoint];
				used[nextCHpoint]=true;
			}
		
	
		}
catch ( InterruptAlgorithm& ) {
		return false;
}
}