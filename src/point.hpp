#pragma once

#include <cmath>

class Point{
    public:
        double x = 0;
        double y = 0;
        Point(double x, double y);
    private:
};

double dist_point(Point* &a, Point* &b);
