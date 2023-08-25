#include "graph.h"

struct graph {
    int V;
    int E;
    
};

int cmp_int_fn(data_type a, data_type b) {
    return a - b;
}

Graph* graph_construct(
    vertex_cmp_fn vertex_cmp,
    vertex_print_fn vertex_print,
    vertex_destruct_fn vertex_destruct,
    edge_cmp_fn edge_cmp,
    edge_print_fn edge_print,
    edge_destruct_fn edge_destruct
) {    
    
}

void graph_add_vertex(Graph* graph, data_type data) {
    
}

void graph_add_edge(Graph* graph, data_type data1, data_type data2) {
    
}
