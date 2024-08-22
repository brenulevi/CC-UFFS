#include <iostream>
#include <vector>

/**
 * n -> item number
 * w -> knapsack capacity
 * v -> item value
 * p -> item weight
 */

/**
 * n - w
 * v - p
 */

int bru_knapsack(int i, int n, int w, int *v, int *p);
int dyn_knapsack(int i, int n, int w, int *v, int *p, std::vector<std::vector<int>> &m);

int main()
{
    int n, w;
    int *v = new int[n];
    int *p = new int[n];

    // get values
    std::cin >> n >> w;
    for (int i = 0; i < n; i++)
        std::cin >> v[i] >> p[i];

    // initialize
    std::vector<std::vector<int>> m;
    m.resize(n);
    for (int i = 0; i < n; i++)
        m[i].resize(w + 1, -1);

    std::cout << dyn_knapsack(0, n, w, v, p, m) << std::endl;

    delete v;
    delete p;
}

int bru_knapsack(int i, int n, int w, int *v, int *p)
{
    // verify if number of items exceeded or knapsack weight is zero (base case)
    if (i >= n || w == 0)
        return 0;

    // don't put item with weight greater than knapsack capacity
    if (p[i] > w)
    {
        // computate and save value in remember matrix
        return bru_knapsack(i + 1, n, w, v, p);
    }

    // put item (reduce sack weight for next iteration) or not put and continue [save in remember matrix]
    return std::max(v[i] + bru_knapsack(i + 1, n, w - p[i], v, p), bru_knapsack(i + 1, n, w, v, p));
}

int dyn_knapsack(int i, int n, int w, int *v, int *p, std::vector<std::vector<int>> &m)
{
    // verify if number of items exceeded or knapsack weight is zero (base case)
    if (i >= n || w == 0)
        return 0;

    // if this values was already computated, return it
    if (m[i][w] != -1)
        return m[i][w];

    // don't put item with weight greater than knapsack capacity
    if (p[i] > w)
    {
        // computate and save value in remember matrix
        m[i][w] = dyn_knapsack(i + 1, n, w, v, p, m);
        return m[i][w];
    }

    // put item (reduce sack weight for next iteration) or not put and continue [save in remember matrix]
    m[i][w] = std::max(v[i] + dyn_knapsack(i + 1, n, w - p[i], v, p, m), dyn_knapsack(i + 1, n, w, v, p, m));
    return m[i][w];
}