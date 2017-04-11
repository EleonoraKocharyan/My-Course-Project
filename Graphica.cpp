#include "Graphica.h"

void GraphicalPoint::draw()
{
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA_SATURATE, GL_ONE);

	glPointSize(p_size);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	
	glColor3d(color.red,color.green,color.blue);
	glVertex2d(p.x,p.y);
	
	glEnd();
}

void GraphicalSegment::draw()
{
	glEnable(GL_LINE_SMOOTH);
	//glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA_SATURATE, GL_ONE);

	glLineWidth(l_width);
	glBegin(GL_LINES);

	glColor3d(color.red,color.green,color.blue);
	glVertex2d(endpoint_1.x,endpoint_1.y);
	glVertex2d(endpoint_2.x,endpoint_2.y);

	glEnd();
}

void GraphicalScene::draw_all()
{
	glClear( GL_COLOR_BUFFER_BIT );
	for(auto i=objs.begin(); i!=objs.end(); ++i)
		(*i)->draw();
	
	glFlush();
	glutSwapBuffers();
}

void GraphicalScene::addObj(GraphicalObject* obj)
{
	objs.insert(obj);
	glutPostRedisplay();
}

void GraphicalScene::removeObj(GraphicalObject* obj)
{
	objs.erase(obj);
	glutPostRedisplay();
}

void GraphicalView::draw()
{
	glLoadIdentity();
	glMultMatrixd(m);
	scene->draw_all();
}

void GraphicalView::translate( double x, double y)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(m);
	glTranslated(x,y,0);
	glGetDoublev(GL_MODELVIEW_MATRIX,m);
	glutPostRedisplay();
}

GraphicalView::GraphicalView() 
{
	for(int i=0; i<16; ++i)
		m[i]=0;
	
	m[0]=m[5]=m[10]=m[15]=1;
	scene=new GraphicalScene;
}