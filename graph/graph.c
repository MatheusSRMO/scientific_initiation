#include "graph.h"

void swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

typedef struct Node {
    unsigned short int target;
    float weight;
    struct Node *next;
} Node;

// Cria um novo nó
Node *node_contruct(int target, float weight, Node *next) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->target = target;
    new_node->weight = weight;
    new_node->next = next;
    return new_node;
}

// Destroi um nó
void node_destroy(Node *node) {
    free(node);
}

// Grafo não direcionado para lista de adjacência (lista de listas encadeadas) e matriz de adjacência (triangular)
struct graph {
    int V;                      // Número de vértices
    int E;                      // Número de arestas
    float **adjacency_matrix;   // Matriz de adjacência
    Node **adjacency_list;      // Lista de adjacência
    graph_type type;            // Tipo do grafo
};

Graph *graph_create(int V, graph_type type) {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->V = V;
    graph->E = 0;
    graph->type = type;

    if (type == adj_matrix) {
        graph->adjacency_matrix = (float **) malloc(sizeof(float *) * V);
        // Aloca uma matriz triangular
        for (int i = 0; i < V; i++) {
            graph->adjacency_matrix[i] = (float *) malloc(sizeof(float) * (i + 1));
            for (int j = 0; j < i + 1; j++) {
                graph->adjacency_matrix[i][j] = 0;
            }
        }
        // seta adjancency_list para NULL para não dar segmentation fault
        graph->adjacency_list = NULL;
    }
    else if (type == adj_list) {
        graph->adjacency_list = (Node **) malloc(sizeof(Node *) * V);
        for (int i = 0; i < V; i++) {
            graph->adjacency_list[i] = NULL;
        }
        // seta adjacency_matrix para NULL para não dar segmentation fault
        graph->adjacency_matrix = NULL;
    }

    return graph;
}

void graph_add_edge(Graph *graph, int v, int w, float weight) {
    if (v > w) swap(&v, &w);

    if (graph->type == adj_matrix) {
        graph->adjacency_matrix[w][v] = weight;
    }
    else if (graph->type == adj_list) {
        float weight = graph_get_weight(graph, v, w);
        if (weight != 0) {
            return;
        }
        graph->adjacency_list[v] = node_contruct(w, weight, graph->adjacency_list[v]);
    }
    graph->E++;
}

float graph_get_weight(Graph *graph, int v, int w) {
    if (v > w) swap(&v, &w); 

    if (graph->type == adj_matrix) {
        return graph->adjacency_matrix[w][v];
    }
    else if (graph->type == adj_list) {
        Node *node = graph->adjacency_list[v];
        while (node != NULL) {
            if (node->target == w) {
                return node->weight;
            }
            node = node->next;
        }
    }
    return 0;
}

void graph_print(Graph *graph) {
    if (graph->type == adj_matrix) {
        for (int i = 0; i < graph->V; i++) {
            for (int j = 0; j < i + 1; j++) {
                printf("%.2f ", graph->adjacency_matrix[i][j]);
            }
            printf("\n");
        }
    }
    else if (graph->type == adj_list) {
        for (int i = 0; i < graph->V; i++) {
            printf("%d: ", i);
            Node *node = graph->adjacency_list[i];
            while (node != NULL) {
                printf("%d(%.2f) ", node->target, node->weight);
                node = node->next;
            }
            printf("\n");
        }
    }
}

void graph_destroy(Graph *graph) {
    if (graph->type == adj_matrix) {
        for (int i = 0; i < graph->V; i++) {
            free(graph->adjacency_matrix[i]);
        }
        free(graph->adjacency_matrix);
    }
    else if (graph->type == adj_list) {
        for (int i = 0; i < graph->V; i++) {
            Node *node = graph->adjacency_list[i];
            while (node != NULL) {
                Node *aux = node;
                node = node->next;
                node_destroy(aux);
            }
        }
        free(graph->adjacency_list);
    }
    free(graph);
}
