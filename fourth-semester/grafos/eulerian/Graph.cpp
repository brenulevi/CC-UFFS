#include "Graph.h"
#include <algorithm>
#include <stack>

Graph::Graph(int v)
{
    n_vertex_ = v;
    n_edges_ = 0;

    adj.resize(v);

    for (int i = 0; i < v; i++)
        adj[i].resize(v, 0);
}

void Graph::insert_edge(Edge e)
{
    if (e.v1 == e.v2 || e.v1 >= n_vertex_ || e.v2 >= n_vertex_)
        return;

    for (std::vector<int>::iterator i = adj[e.v1].begin(); i != adj[e.v1].end(); i++)
    {
        if (*i == e.v2)
            return;
    }

    adj[e.v1][e.v2] = 1;
    adj[e.v2][e.v1] = 1;

    n_edges_++;
}

void Graph::deepSearch(int v, int *marked)
{
    std::stack<int> stack;
    stack.push(v);
    while (!stack.empty())
    {
        int w = stack.top();
        stack.pop();
        if (marked[w] == 0)
        {
            marked[w] = 1;
            for (int u = (n_vertex_ - 1); u >= 0; u--)
            {
                if (adj[w][u] != 0)
                    if (marked[u] == 0)
                        stack.push(u);
            }
        }
    }
}

bool Graph::verify_connected()
{
    int *marked = (int *)malloc(n_vertex_ * sizeof(int));
    for(int i = 0; i < n_vertex_; i++)
        if(get_degree(i) == 0)
            marked[i] = 1;
            
    deepSearch(0, marked);
    for (int j = 0; j < n_vertex_; j++)
    {
        if (marked[j] == 0)
            return false;
    }
    return true;
}

int Graph::get_degree(int v)
{
    int acc = 0;
    for (int i = 0; i < n_vertex_; i++)
    {
        if (adj[v][i] == 1)
            acc++;
    }
    return acc;
}

void Graph::print()
{
    for (int i = 0; i < n_vertex_; i++)
    {
        std::cout << i << ":";
        for (std::vector<int>::iterator j = adj[i].begin(); j != adj[i].end(); j++)
        {
            std::cout << " " << *j;
        }
        std::cout << "\n";
    }
}
