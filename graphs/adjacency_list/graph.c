#include "graph.h"

struct graph {
    int V;
    int E;
    Vector* adj;
};

int cmp_int_fn(data_type a, data_type b) {
    int _a = *(int*) a;
    int _b = *(int*) b;
    return _a - _b;
}

int cmp_vector_fn(data_type a, data_type b) {
    if (a == NULL || b == NULL) {
        // Caso um dos vetores seja NULL, não podemos compará-los.
        // Nesse caso, consideraremos que eles não são iguais.
        return false;
    }

    if (vector_size(a) != vector_size(b)) {
        // Se os tamanhos dos vetores forem diferentes, eles não são iguais.
        return false;
    }

    // Comparando os elementos individualmente
    for (size_t i = 0; i < vector_size(a); i++) {
        if (vector_get(a, i) != vector_get(b, i)) {
            // Se encontrarmos um elemento diferente, os vetores não são iguais.
            return false;
        }
    }

    // Se chegarmos até aqui, os vetores são iguais.
    return true;
}

Graph* graph_construct() {    
    Graph* graph = malloc(sizeof(Graph));
    graph->V = 0;
    graph->E = 0;
    graph->adj = vector_construct(cmp_vector_fn);
    return graph;
}

void graph_add_vertex(Graph* graph, data_type data) {
    vector_push_back(graph->adj, vector_construct(cmp_int_fn));
    graph->V++;
}

void graph_add_edge(Graph* graph, data_type data1, data_type data2) {
    int v1 = vector_find(graph->adj, data1);
    int v2 = vector_find(graph->adj, data2);

    printf("v1: %d\n", v1);
    printf("v2: %d\n", v2);
    
    graph->E++;
}
