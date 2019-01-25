#include "check.hpp"

std::tuple<bool,std::vector<Point*>> check(){
    std::vector<Point*> cluster_center;
    std::vector<Point*> point_not_coverded;

    int eta = 16;
    int n; double r;
    std::cin >> n >> r;
    std::vector<Point*> points;
    for(int i = 0; i < n; i++){
        double x,y;
        std::cin >> x >> y;
        Point* p = new Point(x,y);
        cluster_center.push_back(p);
    }

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
    }
    fb.close();

    return make_tuple(point_not_coverded.size()==0, point_not_coverded);
}
