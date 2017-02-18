#ifndef GLOB_FUNC_H
#define GLOB_FUNC_H
#include <vector>
#include "Graphica.h"
std::ostream& operator <<(std::ostream &out, const std::vector<point> &v); //outputs vector of points
std::istream& operator >>(std::istream &in, std::vector<point> &v); // inputs vector of points

std::ostream& operator <<(std::ostream &out, const std::vector<int> &v); //outputs vector of integers
void GiftWrapping(const std::vector<point> &v); //finds the convex hull for the set of points

void Display();
void reshapeFunction( int newWidth, int newHeight );
void mouseFunction(int button, int state, int x, int y);
void motionFunction(int x, int y);
#endif
