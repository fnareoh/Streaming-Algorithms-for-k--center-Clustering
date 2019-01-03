#include "point.hpp"

Point::Point(double x, double y) :
    x(x),
    y(y)
{}

double dist_point(Point& a, Point& b)
{
    return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}
