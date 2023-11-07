#include "Graph.h"
#include <iostream>

int main()
{
    int v, e;
    std::cin >> v >> e;

    Graph* g = new Graph(v);

    for (int i = 0; i < e; i++)
    {
        int v1, v2;
        std::cin >> v1 >> v2;
        g->insert_edge(Edge(v1, v2));
    }

    if (g->verify_connected())
    {
        for (int i = 0; i < v; i++)
        {
            if (g->get_degree(i) % 2 != 0)
            {
                std::cout << "NAO" << std::endl;
                return 0;
            }
        }
        std::cout << "SIM" << std::endl;
        return 0;
    }

    std::cout << "NAO" << std::endl;
    return 0;
}