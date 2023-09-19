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
        // Aloca uma matriz triangular
        // Aassumindo que a distancia do vertice para ele mesmo é 0 
        // Que o grafo é não direcionado
        graph->adjacency_matrix = (float **) malloc(sizeof(float *) * V);
        for (int i = 0; i < V; i++) {
            graph->adjacency_matrix[i] = (float *) malloc(sizeof(float) * (i));
            for (int j = 0; j < i; j++) {
                graph->adjacency_matrix[i][j] = 0;
            }
        }
        graph->adjacency_list = NULL;
    }
    else if (type == adj_list) {
        graph->adjacency_list = (Node **) malloc(sizeof(Node *) * V);
        for (int i = 0; i < V; i++) {
            graph->adjacency_list[i] = NULL;
        }
        graph->adjacency_matrix = NULL;
    }

    return graph;
}

void graph_add_edge(Graph *graph, int v, int w, float weight) {
    if (v == w) return;
    if (weight == 0) return;
    if (v > w) swap(&v, &w);

    if (graph->type == adj_matrix) {
        graph->adjacency_matrix[w][v] = weight;
    }
    else if (graph->type == adj_list) {
        if (graph_get_weight(graph, v, w) != 0) return;
        graph->adjacency_list[v] = node_contruct(w, weight, graph->adjacency_list[v]);
    }
    graph->E++;
}

float graph_get_weight(Graph *graph, int v, int w) {
    if (v == w) return 0;
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
        printf("\t");
        for (int i = 0; i < graph->V; i++) {
            printf("%d\t", i);
        }
        printf("\n");
        for (int i = 0; i < graph->V; i++) {
            printf("%d\t", i);
            for (int j = 0; j < i; j++) {
                printf("%.2f\t", graph_get_weight(graph, i, j));
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

void graph_to_edge_list(Graph *graph, EdgeList *edge_list) {
    if(graph == NULL || edge_list == NULL) return;

    if(graph->type == adj_matrix) {
        for(int i = 0; i < graph->V; i++) {
            for(int j = 0; j < i; j++) {
                float weight = graph_get_weight(graph, i, j);
                if(weight != 0) {
                    edge_list_add(edge_list, i, j, weight);
                }
            }
        }
    }
    else if(graph->type == adj_list) {
        for(int i = 0; i < graph->V; i++) {
            Node *node = graph->adjacency_list[i];
            while(node != NULL) {
                edge_list_add(edge_list, i, node->target, node->weight);
                node = node->next;
            }
        }
    }
}

void graph_of_edge_list(Graph *graph, EdgeList *edge_list) {
    if(graph == NULL || edge_list == NULL) return;

    int size = edge_list_get_size(edge_list);
    for(int i = 0; i < size; i++) {
        int v = edge_list_get_v(edge_list, i);
        int w = edge_list_get_w(edge_list, i);
        float weight = edge_list_get_weight(edge_list, i);
        graph_add_edge(graph, v, w, weight);
    }
}