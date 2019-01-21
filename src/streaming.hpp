#include <vector>
#include <utility>
#include <unordered_set>
#include "point.hpp"

tuple<> streaming_algo(int k, int z, double r, int alpha, int beta, int eta,
                    std::vector<Point> cluster_center,
                    std::vector<std::vector<Point>> support_point,
                    std::vector<Point> free_points,
                    bool last);
