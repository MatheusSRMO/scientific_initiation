#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <set>
#include "../point/point.hpp"

using namespace std;


enum class GraphType {
    UNDIRECTED,
    DIRECTED
};
enum class GraphRepresentation {
    ADJACENCY_MATRIX,
    ADJACENCY_LIST
};

class Graph {
    private:
        struct GraphNode { int to; double weight; };
        int V;
        GraphType type;
        GraphRepresentation representation;
        vector<vector<double>> adjacency_matrix;
        vector<vector<GraphNode>> adjacency_list;
    public:
        Graph();
        Graph(const Graph &graph);
        Graph(int V, GraphType type, GraphRepresentation representation);
        ~Graph();
        void add_edge(int from, int to, double weight);
        void remove_edge(int from, int to);
        vector<int> get_neighbors(int node);
        void print();

        int get_V() { return this->V; }
        GraphType get_type() { return this->type; }
        GraphRepresentation get_representation() { return this->representation; }

        double get_edge_weight(int from, int to);
        double get_min_distance(int from, int to);
};

#endif // GRAPH_HPP