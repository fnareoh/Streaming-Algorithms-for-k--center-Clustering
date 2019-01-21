#include "streaming.hpp"

int streaming_algo(int k, int z, double r, int alpha, int beta, int eta,
                    std::vector<Point> cluster_center,
                    std::vector<std::vector<Point>> support_point,
                    std::vector<Point> free_points,
                    bool last)
{
    int n = free_points.size();

    /*Handeling a batch*/
    std::vector<bool> is_free(n, true);
    bool step3 = false;

    while(!step3){
        /* step 1 */
        for(int c = 0; c < cluster_center.size(); c++){
            for(int i = 0; i < n; i++) {
                if (dist_point(free_points[i],cluster_center[c]) < eta*r) is_free[i] = false;
            }
        }

        /* step 2 */
        for(int i = 0; i < n; i++) {
            if (is_free[i] && !step3) {
                int cpt = 0;
                std::vector<Point> support;
                std::vector<int> not_free;
                for(int j = 0; j <= i; j++){
                    if (is_free[j]) && dist_point(free_points[i],free_points[j]) < beta*r) {
                        cpt++;
                        not_free.push_back(j);
                        support.push_back(free_points[j]);
                    }
                }
                if (p >= z+1) {
                    cluster_center.push_back(free_points[i]);
                    support_point.push_back(support(support.begin(), support.begin()+std::min(z,k)));
                    for(int j: not_free) is_free[j] = false;
                    step3 = true;
                }
            }
        }
    }

    /* step 3 */
    int l = cluster_center.size();
    std::vector<Point> static_point;
    for(int i = 0; i < n; i++) if (is_free[i]) static_point.push_back(points[i]);
    int nb_free_points = static_point.size();
    bool done = true;
    if (l > k || nb_free_points > (k-l)*z + z ){
        done = false;
    }
    else {
        bool static_result;
        bool static_cluster_center;
        tie(static_result, static_cluster_center) = static_algo(k-l,z,(double)eta*r/3,static_point);
        if (!static_result) done = false;
    }

    /* step 4 */
    if (!done) {
        r = alpha*r;
        std::vector<int> new_cluster_center;
        std::vector<std::vector<int>> new_support_point;
        std::conflict<bool> conflict(n,false);
        for(int i = 0; i < cluster_center.size(); i++){
            if (!conflict[i]){
                new_cluster_center.push_back(cluster_center[i]);
                new_support_point.push_back(support_point[i]);
                for(int j = i+1; j < cluster_center.size(); j++){
                    if (conflict[j]) break;
                    for(int point_i: support_point[i]){
                        for(int point_j: support_point[j]){
                            if ( dist_point(point_i,point_j) < 2*r ) conflict[j] = true;
                        }
                    }
                }
            }
        }
        return streaming_algo(k, z, r, alpha, beta, eta, new_cluster_center, new_support point, points);
    }
    else{
        if (last); //add static_cluster_center to cluster_center
        return 1;
    }
    return 0;
}
