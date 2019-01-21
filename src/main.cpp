#include <iostream>
#include <vector>

#include "point.hpp"
#include "static.hpp"
#include "streaming.hpp"

int static_test(){
    int n = 6;
    std::vector<Point> points;
    for(int i = 0; i < n; i++){
        long long int unix_timestamp;
        double x,y;
        std::cin >> unix_timestamp >> x >> y;
        Point* p = new Point(x,y);
        points.push_back(*p);
    }
    bool result;
    std::vector<Point> cluster_center;
    tie(result,cluster_center) = static_algo(1, 6, 5, points);
    std::cout << result << std::endl;
    return 0;
}

bool get_batch(std::istream& stream, std::vector<Point>& free_points, int size_batch){
    int nb_added = 0;
    long long int unix_timestamp;
    double x,y;

    while (size_batch > nb_added && stream >> unix_timestamp >> x >> y){
        /* New => you have to free TO FIX */
        Point* p = new Point(x,y);
        free_points.push_back(p)
        nb_added++;
    }

    return (size_batch != nb_added);
}

int streaming_test(int k, int z){
    int alpha = 4;
    int beta = 8;
    int eta = 16;
    int m = 1;

    int nb_batch = kz;
    std::vector<Points> cluster_center;
    std::vector<std::vector<Points>> support_point;
    std::vector<Points> free_points;
    /* TODO : initialisate the istream and add the call to get batch then debug */

    std::vector<int> r_point(k+z+1,0);
    for(int i = 0; i < r_point.size(); i++) r_point[i] = rand() % n ;
    double r = dist_point(free_points[r_point[0]], free_points[r_point[1]])/2;
    for(int i = 0; i < r_point.size(); i++) {
        for (int j = 0; j < i; j++) {
            if ( dist_point(free_points[r_point[i]], free_points[r_point[j]])/2 < r )
                    r =  dist_point(free_points[r_point[i]], free_points[r_point[j]])/2 ;
        }
    }

    bool last = false;
    tie(r,cluster_center,support_point,free_points) streaming_algo(k, z, r, alpha, beta, eta, cluster_center, support_point, free_points, last);

    while(!last){

    }
}

int main() {
    int k = 20;
    int z = 10;
    return 0;
}
