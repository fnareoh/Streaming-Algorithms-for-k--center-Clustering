#include "static.hpp"


tuple<bool,std::vector<Point>> static_algo(int k, int p, double radius, std::vector<Point>& points)
{
    int n = points.size();
    std::vector<std::unordered_set<int>> G(n);
    std::vector<std::unordered_set<int>> E(n);
    std::vector<int> covered(n,false);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if (dist_point(points[i],points[j]) < radius)
            {
                G[i].insert(j);
                G[j].insert(i);
                E[i].insert(j);
                E[j].insert(i);
            }
            else if (dist_point(points[i],points[j]) < 3*radius)
            {
                E[i].insert(j);
                E[j].insert(i);
            }
        }
    }

    std::vector<Point> cluster_center;
    for (int step = 0; step < k; step++)
    {
        int max_G = 0;
        int i_max_G = 0;
        for(int i = 0; i < n; i++)
        {
            if (!covered[i] && G[i].size()+1 > max_G){
                max_G = G[i].size();
                i_max_G = i;
            }
        }

        cluster_center.push_back(points[i_max_G]);
        for(const int i: E[i_max_G])
        {
            covered[i] = true;
            for(const int l: G[i]){
                if (l != i_max_G) G[l].erase(i);
            }
            for(const int l: E[i]){
                if (l != i_max_G) E[l].erase(i);
            }
            G[i] = {};
            E[i] = {};
        }

        covered[i_max_G] = true;
        G[i_max_G] = {};
        E[i_max_G] = {};
    }

    int nb_covered = 0;
    for(int i = 0; i < n; i++) if (covered[i]) nb_covered++;

    return make_tuple(nb_covered >= p,cluster_center);
}
