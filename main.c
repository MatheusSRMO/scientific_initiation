#include <stdio.h>
#include "src/graph/graph.h"

int main(int argc, char *argv[]) {
    Graph *graph = graph_create(5, adj_list);

    graph_add_edge(graph, 0, 1, 1);
    graph_add_edge(graph, 0, 2, 1);
    graph_add_edge(graph, 0, 3, 1);
    graph_add_edge(graph, 0, 4, 1);

    graph_print(graph);

    graph_destroy(graph);
    return 0;
}