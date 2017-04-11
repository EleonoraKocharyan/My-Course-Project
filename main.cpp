#include <GL/glut.h>
#include "GlobFunc.h"
#include <iostream>
int main( int argc, char **argv )
{
	
    glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize( 600, 600 );
	
	//std::cin>>points;
	glutCreateWindow( "Porc" );
	glutDisplayFunc( Display );
	glutMouseFunc(mouseFunction);
	glutMotionFunc(motionFunction);
	glutKeyboardFunc(keyfunc);
	glutReshapeFunc(reshapeFunction);
	
	glutMainLoop();

}
