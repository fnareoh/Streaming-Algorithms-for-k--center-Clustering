#include <vector>
#include <utility>


double static_algo(int k, double radius, std::vector<Point> points)
{
    int n = points.size();
    std::vector<std::unordered_set<int>> G(n);
    std::vector<std::unordered_set<int>> E(n);
    std::std::vector<bool> covered(n,false);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if (dist(points[i],points[j]) < radius)
            {
                G[i].insert(j);
                G[j].insert(i);
            }
            elif (dist(points[i],points[j]) < 3*radius)
            {
                E[i].insert(j);
                E[j].insert(i);
            }
        }
    }

    for (int step = 0; step < r; step++)
    {
        int max_G = 0;
        int i_max_G = 0;
        for(int i = 0; i < n; i++)
        {
            if (!covered[i] && G[i].size() > max_G){
                max_G = G[i].size();
                i_max_G = i;
            }
        }

        for(const int i: E[i_max_G])
        {
            covered[i] = true;
            for(const int k: G[i]){
                G[k].erase(i);
            }
            for(const int k: E[i]){
                E[k].erase(i);
            }
            G[i] = {};
            E[i] = {};
        }

        covered[i_max_G] = true;
        G[i_max_G] = {};
        E[i_max_G] = {};
        
    }
}
