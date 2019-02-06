#include "lower_bound.hpp"

double lower_bound(double r_min, double r_max, int nb_center, std::vector<Point*> points){
    double r_mid =(r_min+r_max)/2;
    int eta = 16;

    if (r_max-r_min < 0.001) return r_mid;
    else{
        std::vector<Point*> cluster_center;
        for(Point* p: points){
            bool far_enough = true;
            for(Point* c: cluster_center){
                if (dist_point(p,c) < 2*eta*r_mid) far_enough = false;
            }
            if (far_enough) cluster_center.push_back(p);
        }
        int l = cluster_center.size();
        if (l > nb_center){
            return lower_bound(r_mid,r_max,nb_center,points);
        }
        else{
            return lower_bound(r_min,r_mid,nb_center,points);
        }
    }

}
