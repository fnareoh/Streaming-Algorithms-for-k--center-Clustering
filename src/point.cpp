#include "point.hpp"

Point::Point(double x, double y) :
    x(x),
    y(y)
{}

double dist_point(Point* &a, Point* &b)
{
    return pow(pow(a->x - b->x, 2) + pow(a->y - b->y, 2),0.5);
}

bool greater_point(Point* &a, Point* &b)
{
    return (a->y > a->y);
}
