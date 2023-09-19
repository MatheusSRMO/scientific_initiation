#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "file_handler/file_handler.h"
#include "file_handler/scp/scp.h"
#include "file_handler/vrp/vrp.h"
#include "graph/graph.h"
#include "edge_list/edge_list.h"


int main() {
    FileHandler *file_handler = file_handler_create(
        "text.scp",
        "r",
        scp_file_reader,
        scp_file_data_to_edge_list,
        scp_file_writer,
        scp_file_destructor,
        scp_file_get_dimension,
        scp_file_get_edges_dimension
    );

    file_handler_read_data(file_handler);

    int dimension = file_handler_get_dimension(file_handler);
    printf("Dimension: %d\n", dimension);
    int edges_dimension = file_handler_get_edges_dimension(file_handler);
    EdgeList *edge_list = edge_list_create(edges_dimension);

    file_handler_data_to_edge_list(file_handler, edge_list);

    // edge_list_print(edge_list);

    Graph *graph = graph_create(dimension, adj_list);

    graph_of_edge_list(graph, edge_list);

    // graph_print(graph);

    graph_destroy(graph);
    edge_list_destroy(edge_list);
    file_handler_destroy(file_handler);
    return 0;
}
