/*
 * Tarefa 01 - Grafo - Listas de Adjacencia
 *
 * GEN254 - Grafos - 2023/2
 *
 * Nome:      Breno Soares Alves
 * Matricula: 2211100022
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <list>
#include <vector>
#include "Edge.h"

class Graph
{
private:
    std::vector<std::vector<int>> adj;
    int n_vertex_;
    int n_edges_;

public:
    Graph(int v);

    int get_vertex_number();
    int get_edges_number();

    void insert_edge(Edge e);

    bool verify_connected();
    int get_degree(int v);

    void print();

private:
    void deepSearch(int v, int* marked);

};

inline int Graph::get_vertex_number() { return n_vertex_; }
inline int Graph::get_edges_number() { return n_edges_; }

#endif
