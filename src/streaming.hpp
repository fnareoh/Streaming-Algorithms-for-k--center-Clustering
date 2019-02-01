#include <iostream>
#include <tuple>
#include <vector>
#include <utility>
#include <unordered_set>
#include "point.hpp"


std::tuple<double,std::vector<Point*>,std::vector<std::vector<Point*>>,std::vector<Point*>,std::vector<Point*>> streaming_algo(
                    int k, int z, double r, double alpha, int beta, int eta,
                    std::vector<Point*> cluster_center,
                    std::vector<std::vector<Point*>> support_point,
                    std::vector<Point*> free_points);
