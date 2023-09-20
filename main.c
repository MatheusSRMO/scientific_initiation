#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "file_handler/file_handler.h"
#include "graph/graph.h"
#include "edge_list/edge_list.h"
#include "kruskal/kruskal.h"
#include "algorithms/algorithms.h"

int main(int argc, char const *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input_file_name = (char *) malloc(sizeof(char) * 100);
    strcpy(input_file_name, argv[1]);


    FileHandler *file_handler = file_handler_create(input_file_name, tsp);

    int edges_dimension = file_handler_get_edges_dimension(file_handler);

    EdgeList *edge_list = edge_list_create(edges_dimension);

    file_handler_to_edge_list(file_handler, edge_list);

    edge_list_sort(edge_list);

    int dimension = file_handler_get_dimension(file_handler);
    EdgeList* mst_list = kruskal(edge_list, dimension);

    // edge_list_print(mst_list);
    // file_handler_write_mst(file_handler, mst_list);

    Graph* graph = graph_create(dimension, adj_list);
    graph_of_edge_list(graph, mst_list);

    int* tour = euler_tour(graph, 0);


    // for(int i = 0; i < dimension; i++) {
    //     printf("%d ", tour[i] + 1);
    // }
    // printf("\n");

    free(tour);
    graph_destroy(graph);
    edge_list_destroy(mst_list);
    edge_list_destroy(edge_list);
    file_handler_destroy(file_handler);
    free(input_file_name);
    return 0;
}
