#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include "point.hpp"

std::tuple<int,std::vector<Point*>> check(double r, std::vector<Point*> cluster_center);

double recompute(std::vector<Point*> cluster_center,std::vector<Point*> point_not_coverded);
