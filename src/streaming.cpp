#include "static.hpp"
#include "streaming.hpp"

std::tuple<double,std::vector<Point*>,std::vector<std::vector<Point*>>,std::vector<Point*>,std::vector<Point*>> streaming_algo(
                    int k, int z, double r, double alpha, int beta, int eta,
                    std::vector<Point*> cluster_center,
                    std::vector<std::vector<Point*>> support_point,
                    std::vector<Point*> free_points)
{
    int n = free_points.size();

    /*Handeling a batch*/
    std::vector<bool> is_free(n, true);
    bool step3 = false;

    while(!step3){
        step3 = true;
        /* step 1 */

        for(int c = 0; c < cluster_center.size(); c++){
            for(int i = 0; i < n; i++) {
                if (is_free[i] && dist_point(free_points[i],cluster_center[c]) < eta*r) {
                    is_free[i] = false;
                    delete[] free_points[i];
                }
            }
        }

        /* step 2 */

        for(int i = 0; i < n; i++) {
            if (is_free[i] && step3) {
                int cpt = 0;
                std::vector<Point*> support;
                std::vector<int> not_free;
                for(int j = 0; j < n; j++){
                    if (i == j);
                    else if ((is_free[j]) && (dist_point(free_points[i],free_points[j]) < beta*r)) {
                        cpt++;
                        not_free.push_back(j);
                        support.push_back(free_points[j]);
                    }
                }
                if (cpt >= z) {
                    cluster_center.push_back(free_points[i]);
                    is_free[i] = false;
                    for(int j: not_free) is_free[j] = false;
                    std::vector<Point*> support_cluster(support.begin(), support.begin()+std::min(z,k));
                    if (support.size() > std::min(z,k)) {
                        std::vector<Point*> not_support_cluster(support.begin()+std::min(z,k)+1, support.end());
                        for(Point* point_del : not_support_cluster) delete[] point_del;
                    }
                    support_cluster.push_back(free_points[i]);
                    support_point.push_back(support_cluster);
                    step3 = false;
                    std::cout << "a cluster_center was added: " << free_points[i]->x << " " << free_points[i]->y << std::endl;
                }
            }
        }
    }

    /* step 3 */
    int l = cluster_center.size();
    bool static_result = false;
    std::vector<Point*> static_cluster_center;
    std::vector<Point*> static_points;
    for(int i = 0; i < n; i++) if (is_free[i]) static_points.push_back(free_points[i]);
    int nb_free_points = static_points.size();
    bool done = true;
    if (l > k || nb_free_points > (k-l)*z + z ){
        done = false;
    }
    else {
        tie(static_result, static_cluster_center) = static_algo(k-l,nb_free_points-z,(double)eta*r/3,static_points);
        if (!static_result) done = false;
    }

    /* step 4 */
    if (!done) {
        r = alpha*r;
        std::cout << "r is multiplied by four: " << r  << std::endl;
        std::vector<Point*> new_cluster_center;
        std::vector<std::vector<Point*>> new_support_point;
        std::vector<bool> conflict(n,false);
        for(int i = 0; i < cluster_center.size(); i++){
            if (!conflict[i]){
                new_cluster_center.push_back(cluster_center[i]);
                new_support_point.push_back(support_point[i]);
                std::cout << "a cluster_center was kept: " << cluster_center[i]->x << " " << cluster_center[i]->y << std::endl;
                for(int j = i+1; j < cluster_center.size(); j++){
                    for(Point* point_i: support_point[i]){
                        for(Point* point_j: support_point[j]){
                            if ( dist_point(point_i,point_j) < 2*r ) conflict[j] = true;
                        }
                    }
                }
            }
            else {
                std::cout << "a cluster_center was dropped: " << cluster_center[i]->x << " " << cluster_center[i]->y  << std::endl;
                for(Point* point_i: support_point[i]){
                    delete[] point_i;
                }
            }
        }
        return streaming_algo(k, z, r, alpha, beta, eta, new_cluster_center, new_support_point, static_points);
    }
    else{
        return make_tuple(r,cluster_center,support_point,static_points,static_cluster_center);
    }
}
