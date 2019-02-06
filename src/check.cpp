#include "check.hpp"

std::tuple<int,std::vector<Point*>> check(double r, std::vector<Point*> cluster_center){
    std::vector<Point*> point_not_coverded;

    int eta = 16;
    std::filebuf fb;
    if (fb.open ("../dataset/twitter_1000000.txt",std::ios::in)){
        std::istream is(&fb);
        long long int unix_timestamp;
        double x,y;
        while(is >> unix_timestamp >> x >> y){
            Point* p = new Point(x,y);
            bool covered = false;
            for(Point* c: cluster_center){
                if (dist_point(p,c) <= r*eta) covered = true;
            }
            if (!covered) point_not_coverded.push_back(p);
            else delete[] p;
        }
        fb.close();
    }
    //std::cout << "nb_point_not_coverred: " << point_not_coverded.size() << std::endl;
    return make_tuple(point_not_coverded.size(), point_not_coverded);
}

double recompute(std::vector<Point*> cluster_center, std::vector<Point*> point_not_coverded){
    double r = 0;
    int eta = 16;

        std::filebuf fb;
        if (fb.open ("../dataset/twitter_1000000.txt",std::ios::in)){
            std::istream is(&fb);
            long long int unix_timestamp;
            double x,y;
            while(is >> unix_timestamp >> x >> y){
                Point* p = new Point(x,y);
                bool good_point = true;
                for(Point* pn: point_not_coverded) {
                    if (pn->x == p->x && pn->y == p->y) good_point = false;
                }
                if (good_point) {
                    double r_p = dist_point(cluster_center[0],p);
                    for(Point* c: cluster_center){
                        r_p = std::min(r_p,dist_point(c,p));
                    }
                    r = std::max(r,r_p);
                }
                delete[] p;
            }
            fb.close();
        }
    return r/eta;
};
