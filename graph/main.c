#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"



int main(int argc, char *argv[]) {
    // le o numero de vertices do argumento
    int V = atoi(argv[1]);
    Graph *graph = graph_create(V, adj_matrix);

    // Seta o seed do rand para time atual
    srand(time(NULL));

    for (int i = 0; i < V; i++) {
        int v = rand() % V;
        int w = rand() % V;
        float weight = (float) rand() / RAND_MAX;
        graph_add_edge(graph, v, w, weight);
    }

    graph_print(graph);

    graph_destroy(graph);
    return 0;
}