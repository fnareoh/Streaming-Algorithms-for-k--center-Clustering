#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>


#include "check.hpp"
#include "point.hpp"
#include "static.hpp"
#include "streaming.hpp"

int static_test(){
    int n = 6;
    std::vector<Point*> points;
    for(int i = 0; i < n; i++){
        long long int unix_timestamp;
        double x,y;
        std::cin >> unix_timestamp >> x >> y;
        Point* p = new Point(x,y);
        points.push_back(p);
    }
    bool result;
    std::vector<Point*> cluster_center;
    tie(result,cluster_center) = static_algo(1, 6, 5, points);
    std::cout << result << std::endl;
    return 0;
}

bool get_batch(std::istream& stream, std::vector<Point*>& free_points, int size_batch){
    int nb_added = 0;
    long long int unix_timestamp;
    double x,y;

    while (size_batch > nb_added && stream >> unix_timestamp >> x >> y){
        /* New => you have to free TO FIX */
        Point* p = new Point(x,y);
        free_points.push_back(p);
        nb_added++;
    }
    //std::cout << nb_added << std::endl;
    return (size_batch != nb_added);
}

int streaming_test(int k, int z){
    double alpha = 1.1;
    int beta = 8;
    int eta = 16;
    int m = 1;

    int size_batch = k*z;
    std::vector<Point*> cluster_center;
    std::vector<Point*> cluster_center_static;
    std::vector<std::vector<Point*>> support_point;
    std::vector<Point*> free_points;
    std::filebuf fb;
    if (fb.open ("../dataset/twitter_1000000.txt",std::ios::in)){
        std::istream is(&fb);
        bool last = get_batch(is,free_points,size_batch);
        int n = free_points.size();
        double r = dist_point(free_points[0], free_points[1])/2;
        for(int i = 1; i < k+z; i++) {
            for (int j = 0; j < i; j++) {
                if ( dist_point(free_points[i], free_points[j])/2 > 0 &&
                dist_point(free_points[i], free_points[j])/2 < r )
                        r =  dist_point(free_points[i], free_points[j])/2 ;
            }
        }
        std::cout << "lauching streaming_algo r: " << r  << std::endl;

        tie(r,cluster_center,support_point,free_points, cluster_center_static) = streaming_algo(k, z, r, alpha, beta, eta, cluster_center, support_point, free_points);
        int nb_batch = 0;
        while(!last){
            nb_batch++;
            //std::cout << "getting batch: " << nb_batch << std::endl;
            last = get_batch(is,free_points,size_batch);
            if (last && free_points.size()==0) {
                std::cout << "nb_cluster just before last: " << cluster_center.size() << std::endl;
                for(Point* cluster_static: cluster_center_static) cluster_center.push_back(cluster_static);
                break;
            }
            //std::cout << "lauching streaming_algo r: " << r << " nb_free_points " << free_points.size() << " nb_cluster: " << cluster_center.size() << std::endl;
            tie(r,cluster_center,support_point,free_points,cluster_center_static) = streaming_algo(k, z, r, alpha, beta, eta, cluster_center, support_point, free_points);
            //std::cout << "cluster cluster_center: " << std::endl;
            //for (Point* c : cluster_center) std::cout << "  " << c->x << " " << c->y << std::endl;
            if (last) {
                std::cout << "nb_cluster just before last: " << cluster_center.size() << std::endl;
                for(Point* cluster_static: cluster_center_static) cluster_center.push_back(cluster_static);
            }
        }
        fb.close();
        std::cout << "Streaming algorithm for " << nb_batch*size_batch << " tweets ended with nb_cluster: " << cluster_center.size() << " r: " << r << std::endl;
        for (Point* c : cluster_center) std::cout << 1 << " " << c->x << " " << c->y << std::endl;
    }
    else{
        std::cout << "File opening failed" << std::endl;
    }
    return 0;
}

int main() {
    int k = 20;
    int z = 50;
    streaming_test(k,z);
    bool result;
    std::vector<Point*> point_not_coverded;
    return 0;
}
