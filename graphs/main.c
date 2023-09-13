#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../graphs/adjacency_list_2/graph.h"
#include "../graphs/algorithms/io_file.h"


int main() {
    Graph* graph = generate_random_graph(1e5, 1e5);

    generate_graphviz_file(graph, "graph.dot");

    // graph_print(graph);

    graph_destruct(graph);

    return 0;
}
