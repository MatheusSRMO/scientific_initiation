#include "algorithms.h"


void DFS(Graph* graph, int vertex, int* visited, uint16_t* tour, int* tour_size) {
    visited[vertex] = 1;

    // printf("Vertex: %d, tour_size: %d\n", vertex, *tour_size);
    tour[(*tour_size)++] = vertex;

    int V = graph_get_V(graph);
    for (int i = 0; i < V; i++) {
        if (graph_get_weight(graph, vertex, i) != 0 && !visited[i]) {
            // Se existe uma aresta não visitada, visite-a recursivamente.
            DFS(graph, i, visited, tour, tour_size);
        }
    }
}

uint16_t* graph_dfs(Graph* graph, int startVertex, int* tour_size) {
    int V = graph_get_V(graph);
    uint16_t* tour = malloc(V * sizeof(uint16_t));

    int* visited = (int*)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        visited[i] = 0; // Inicialize todos os vértices como não visitados.
    }

    DFS(graph, startVertex, visited, tour, tour_size);

    free(visited);
    return tour;
}


void euler_util(Graph *graph, int vertex, int *visited, int* tour, int* tour_size) {
    visited[vertex] = 1;
    
    tour[(*tour_size)++] = vertex;

    int V = graph_get_V(graph);
    for (int i = 0; i < V; i++) {
        if (graph_get_weight(graph, vertex, i) != 0 && !visited[i]) {
            euler_util(graph, i, visited , tour, tour_size);
        }
    }
}

int* euler_tour(Graph *graph, int start) {
    int V = graph_get_V(graph);
    int* tour = malloc(V * sizeof(int));
    int tour_size = 0;
    
    int *visited = (int *)malloc(V * sizeof(int));

    // Inicializa o array 'visited' com 0
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }

    euler_util(graph, start, visited , tour, &tour_size);

    free(visited);

    return tour;
}
