#include "graph.h"


Edge* edge_create(int target, float weight, Edge* next) {
    Edge* edge = malloc(sizeof(Edge));
    edge->target = target;
    edge->weight = weight;
    edge->next = next;
    return edge;
}

void edge_destroy(Edge* edge) {
    free(edge);
}


// complexity: O(N)
Graph *graph_construct(int V, int E, bool directed) {
    Graph *graph = malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->directed = directed;
    graph->adj = malloc(V * sizeof(Edge*));
    for (int i = 0; i < V; i++) {
        graph->adj[i] = NULL;
    }
    return graph;
}

/// @brief Adiciona um vértice no grafo
/// @param graph Ponteiro para o grafo
/// @param data  Dado a ser inserido
// complexity: O(1)
// void graph_add_vertex(Graph* graph, int data) {
    
// }

void graph_add_edge(Graph* graph, int src, float weight, int dest) {
    if(src >= graph->V || dest >= graph->V || src < 0 || dest < 0) {
        printf("Invalid vertex\n");
        return;
    }
    if(graph->adj[src]->target == dest && graph->adj[src]->weight == weight) {
        // printf("Vertex Already Exists\n");
        return;
    }

    graph->adj[src] = edge_create(dest, weight, graph->adj[src]);

    // vericar se é necessário adicionar a aresta no sentido contrário
    if (!graph->directed) {
        graph->adj[dest] = edge_create(src, weight, graph->adj[dest]);
    }
}

void graph_print(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        printf("%d: ", i);

        Edge *egde = graph->adj[i];
        
        while (egde != NULL) {
            printf("(%.1f)%d ", egde->weight, egde->target);
            egde = egde->next;
        }

        printf("\n");
    }
}

void graph_destruct(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        Edge *edge = graph->adj[i];

        while (edge != NULL) {
            Edge *next = edge->next;
            edge_destroy(edge);
            edge = next;
        }
    }
    free(graph->adj);
    free(graph);
}
