#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <math.h>
#include <iomanip>

double travelling(std::vector<int>& i, std::unordered_map<int, std::pair<int, int>>& m);

int main()
{
    int dimension;

    std::string line;
    do
    {
        std::cin >> line;
        if(line == "DIMENSION:")
            std::cin >> dimension;
        if(line == "DIMENSION")
        {
            std::cin >> line;
            std::cin >> dimension;
        }
    } while (line != "NODE_COORD_SECTION");

    std::vector<int> indices;
    std::unordered_map<int, std::pair<int, int>> map;

    for(int i = 0; i < dimension; i++)
    {
        int index, x, y;
        std::cin >> index >> x >> y;
        indices.push_back(index);
        map.insert({index, {x, y}});
    }
    
    std::cout << std::setprecision(2) << std::fixed << travelling(indices, map) << std::endl;
}

double travelling(std::vector<int> &ind, std::unordered_map<int, std::pair<int, int>> &m)
{
    double optimal = INFINITY;

    do
    {
        double sum = 0;
        for(int i = 0; i < ind.size(); i++)
        {
            auto p1 = m.at(ind[i]);
            auto p2 = (i < ind.size() - 1) ? m.at(ind[i+1]) : m.at(ind[0]);
            sum += sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2));
        }

        if(sum < optimal)
            optimal = sum;

    } while (std::next_permutation(ind.begin(), ind.end()));

    return optimal;
}
