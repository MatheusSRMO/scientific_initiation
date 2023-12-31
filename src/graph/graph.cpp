#include "graph.hpp"

Graph::Graph() {
    this->V = 0;
    this->type = GraphType::UNDIRECTED;
    this->representation = GraphRepresentation::ADJACENCY_MATRIX;
}

Graph::Graph(const Graph &graph) {
    this->V = graph.V;
    this->type = graph.type;
    this->representation = graph.representation;
    this->adjacency_matrix = graph.adjacency_matrix;
    
    if (representation == GraphRepresentation::ADJACENCY_MATRIX) {
        return;
    }

    this->adjacency_list = graph.adjacency_list;
    
}

Graph::Graph(int V, GraphType type, GraphRepresentation representation) {
    this->V = V;
    this->type = type;
    this->representation = representation;

    if (representation == GraphRepresentation::ADJACENCY_MATRIX) {
        this->adjacency_matrix = vector<vector<double>>(V, vector<double>(V, 0));
        return;
    }

    this->adjacency_list = vector<vector<GraphNode>>(V, vector<GraphNode>());
}

Graph::~Graph() {
}

void Graph::add_edge(int from, int to, double weight) {
    if (representation == GraphRepresentation::ADJACENCY_MATRIX) {
        this->adjacency_matrix[from][to] = weight;
        if (type == GraphType::UNDIRECTED) {
            this->adjacency_matrix[to][from] = weight;
        }
        return;
    }

    this->adjacency_list[from].push_back({to, weight});
    if (type == GraphType::UNDIRECTED) {
        this->adjacency_list[to].push_back({from, weight});
    }
}

vector<int> Graph::get_neighbors(int node) {
    if (representation == GraphRepresentation::ADJACENCY_MATRIX) {
        vector<int> neighbors;
        for (int i = 0; i < this->V; i++) {
            if (adjacency_matrix[node][i] != 0) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }

    vector<int> neighbors;
    for(const auto &[to, _] : adjacency_list[node]) {
        neighbors.push_back(to);
    }
    return neighbors;
}

void Graph::print() {
    if (representation == GraphRepresentation::ADJACENCY_MATRIX) {
        for(int i = 0; i < this->V; i++) {
            cout << "\t" << i;
        }
        cout << endl;
        for (int i = 0; i < this->V; i++) {
            cout << i << " ";
            for (int j = 0; j < this->V; j++) {
                cout << "\t" << adjacency_matrix[i][j];
            }
            cout << endl;
        }
        return;
    }

    for (int i = 0; i < this->V; i++) {
        cout << i << ": ";
        for (const auto &[to, _] : adjacency_list[i]) {
            cout << to << " ";
        }
        cout << endl;
    }
    
}
