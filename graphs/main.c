#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../graphs/adjacency_list/graph.h"

// Função auxiliar para imprimir os dados do vértice
void printData(int data) {
    printf("%d ", data);
}

int main() {
    Graph* graph = graph_construct();

    // Adicionando alguns vértices e arestas para teste
    int *v1 = malloc(sizeof(int));
    int *v2 = malloc(sizeof(int));
    int *v3 = malloc(sizeof(int));
    int *v4 = malloc(sizeof(int));

    *v1 = 10;
    *v2 = 20;
    *v3 = 30;
    *v4 = 40;

    graph_add_vertex(graph, v1);
    graph_add_vertex(graph, v2);
    graph_add_vertex(graph, v3);
    graph_add_vertex(graph, v4);

    graph_add_edge(graph, v1, v2);
    graph_add_edge(graph, v1, v3);
    graph_add_edge(graph, v2, v4);
    graph_add_edge(graph, v3, v4);


    return 0;
}
