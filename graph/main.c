#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int main(int argc, char *argv[]) {
    // le o numero de vertices do argumento
    int V = atoi(argv[1]);
    Graph *graph = graph_create(V, adj_matrix);

    // Adiciona arestas aleatórias 1eN vezes
    for (int i = 0; i < 1e3; i++) {
        int v = rand() % V;
        int w = rand() % V;
        float weight = (float) rand() / RAND_MAX;
        graph_add_edge(graph, v, w, weight);
    }

    // graph_print(graph);

    graph_destroy(graph);
    return 0;
}