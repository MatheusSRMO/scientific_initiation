#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "file_handler/file_handler.h"
#include "graph/graph.h"
#include "edge_list/edge_list.h"
#include "kruskal/kruskal.h"

int main() {
    FileHandler *file_handler = file_handler_create("exemplos/in/berlin52.tsp", tsp);

    // file_handler_print(file_handler);

    int edges_dimension = file_handler_get_edges_dimension(file_handler);
    printf("Dimension: %d\n", edges_dimension);

    EdgeList *edge_list = edge_list_create(edges_dimension);

    file_handler_to_edge_list(file_handler, edge_list);

    edge_list_sort(edge_list);


    EdgeList* mst_list = kruskal(edge_list, edges_dimension);

    edge_list_print(mst_list);
    file_handler_write_mst(file_handler, mst_list);

    // Destroying the edge list and the file handler

    edge_list_destroy(mst_list);
    edge_list_destroy(edge_list);
    file_handler_destroy(file_handler);
    return 0;
}
