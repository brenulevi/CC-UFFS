#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <math.h>
#include <iomanip>
#include <set>

double bru_travelling(std::vector<int> &ind, std::unordered_map<int, std::pair<int, int>> &m);
double dyn_travelling(std::vector<int> &ind, std::unordered_map<int, std::pair<int, int>> &m);
void sort(std::vector<std::pair<int, double>>& v);
bool findAtVector(std::vector<int>& v, int value);

int main()
{
    int dimension;

    std::string line;
    do
    {
        std::cin >> line;
        if (line == "DIMENSION:")
            std::cin >> dimension;
        if (line == "DIMENSION")
        {
            std::cin >> line;
            std::cin >> dimension;
        }
    } while (line != "NODE_COORD_SECTION");

    std::vector<int> indices;
    std::unordered_map<int, std::pair<int, int>> map;

    for (int i = 0; i < dimension; i++)
    {
        int index, x, y;
        std::cin >> index >> x >> y;
        indices.push_back(index);
        map.insert({index, {x, y}});
    }

    std::cout << std::setprecision(2) << std::fixed << dyn_travelling(indices, map) << std::endl;
}

double bru_travelling(std::vector<int> &ind, std::unordered_map<int, std::pair<int, int>> &m)
{
    double optimal = INFINITY;

    do
    {
        double sum = 0;
        for (int i = 0; i < ind.size(); i++)
        {
            auto p1 = m.at(ind[i]);
            auto p2 = (i < ind.size() - 1) ? m.at(ind[i + 1]) : m.at(ind[0]);
            sum += sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2));
        }

        if (sum < optimal)
            optimal = sum;

    } while (std::next_permutation(ind.begin(), ind.end()));

    return optimal;
}

double dyn_travelling(std::vector<int> &ind, std::unordered_map<int, std::pair<int, int>> &m)
{
    std::vector<int> c;
    c.push_back(ind[0]);

    int v = ind[0];

    while(c.size() != ind.size())
    {
        double nearestDist = INFINITY;
        int nearestIndex = -1;

        for (int i = 0; i < ind.size(); i++)
        {
            if (ind[i] == v)
                continue;

            auto p1 = m.at(v);
            auto p2 = m.at(ind[i]);
            double dist = sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2));
            if(dist < nearestDist && !findAtVector(c, ind[i]))
            {
                nearestDist = dist;
                nearestIndex = ind[i];
            }
        }

        c.push_back(nearestIndex);
        v = nearestIndex;
    }

    double sum = 0;
    for (int i = 0; i < c.size(); i++)
    {
        auto p1 = m.at(c[i]);
        auto p2 = (i < c.size() - 1) ? m.at(c[i+1]) : m.at(c[0]);
        sum += sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2));
    }

    return sum;
}

void sort(std::vector<std::pair<int, double>> &v)
{
    for(int i = 0; i < v.size(); i++)
    {
        for(int j = 0; j < v.size() - i - 1; j++)
        {
            if(v[j].second > v[j+1].second)
            {
                std::pair<int, double> p = v[j];
                v[j] = v[j+1];
                v[j+1] = p;
            }
        }
    }
}

bool findAtVector(std::vector<int>& v, int value)
{
    bool found = false;
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i] == value)
            found = true;
    }

    return found;
}
