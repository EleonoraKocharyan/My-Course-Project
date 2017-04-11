#ifndef GLOB_FUNC_H
#define GLOB_FUNC_H
#include <vector>
#include "point.h"
std::ostream& operator <<(std::ostream &out, const std::vector<point> &v); //outputs vector of points
std::istream& operator >>(std::istream &in, std::vector<point> &v); // inputs vector of points
std::ostream& operator <<(std::ostream &out, const std::vector<int> &v); //outputs vector of integers

bool GiftWrapping(); 

void Display();
void keyfunc(unsigned char key, int x, int y);
void reshapeFunction( int newWidth, int newHeight );
void mouseFunction(int button, int state, int x, int y);
void motionFunction(int x, int y);
extern std::vector<point> points;

#endif
