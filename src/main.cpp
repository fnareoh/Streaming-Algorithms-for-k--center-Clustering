#include <iostream>

#include "point.hpp"
#include "static.hpp"


int main() {
    std::vector<Point> points;
    for(int i = 0; i < 1000; i++){
        int unix_timestamp;
        double x,y;
        std::cin >> unix_timestamp >> x >> y;
        Point* p = new Point(x,y);
        points.push_back(*p);
    }
    std::cout << static_algo(0, 1, 3, points) << std::endl;
    return 0;
}
