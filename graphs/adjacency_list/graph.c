#include "graph.h"


struct graph {
    int V;                   // Número de vértices (vertices)
    int E;                   // Número de arestas (edges)
    Vector* vertices;
};

struct vertex {
    int data;
    Vector* outgoing_edges;  // Arestas que saem deste vértice
    Vector* incoming_edges;  // Arestas que entram neste vértices
};

struct edge {
    Vertex* from_vertex;     // Vértice de origem
    Vertex* to_vertex;       // Vértice de destino
    float weight;            // Peso da aresta
};


int vertex_get_data(Vertex* vertex) {
    return vertex->data;
}

Vector* vertex_get_outgoing_edges(Vertex* vertex) {
    return vertex->outgoing_edges;
}

Vector* vertex_get_incoming_edges(Vertex* vertex) {
    return vertex->incoming_edges;
}

int edge_get_from_vertex(Edge* edge) {
    return edge->from_vertex->data;
}

int edge_get_to_vertex(Edge* edge) {
    return edge->to_vertex->data;
}

float edge_get_weight(Edge* edge) {
    return edge->weight;
}

int vertex_compare(data_type a, data_type b) {
    Vertex* v1 = a;
    Vertex* v2 = b;
    return v1->data - v2->data;
}

int edge_compare(data_type a, data_type b) {
    Edge* e1 = a;
    Edge* e2 = b;
    return vertex_compare(e1->from_vertex, e2->to_vertex);
}


Graph* graph_construct() {    
    Graph* graph = malloc(sizeof(Graph));
    graph->V = 0;
    graph->E = 0;
    graph->vertices = vector_construct(vertex_compare);
    return graph;
}

void graph_add_vertex(Graph* graph, int data) {
    // Verifica se o vértice já existe
    for(int i = 0; i < graph->V; i++) {
        Vertex* vertex = vector_get(graph->vertices, i);
        if(vertex->data == data) {
            return;
        }
    }
    
    Vertex* vertex = malloc(sizeof(Vertex));
    vertex->data = data;
    vertex->outgoing_edges = vector_construct(edge_compare);
    vertex->incoming_edges = vector_construct(edge_compare);
    vector_push_back(graph->vertices, vertex);
    graph->V++;
}

void graph_add_edge(Graph* graph, int data1, int data2) {
    Vertex* v1 = NULL;
    Vertex* v2 = NULL;

    for(int i = 0; i < graph->V; i++) {
        Vertex* vertex = vector_get(graph->vertices, i);
        if(vertex->data == data1) {
            v1 = vertex;
        }
        if(vertex->data == data2) {
            v2 = vertex;
        }
    }

    Edge* edge = malloc(sizeof(Edge));
    edge->from_vertex = v1;
    edge->to_vertex = v2;
    vector_push_back(v1->outgoing_edges, edge);
    vector_push_back(v2->incoming_edges, edge);
    graph->E++;
}

int graph_vertex_count(Graph* graph) {
    return graph->V;
}

int graph_edge_count(Graph* graph) {
    return graph->E;
}

Vector* graph_get_vertices(Graph* graph) {
    return graph->vertices;
}

void graph_print(Graph* graph) {
    printf("V = %d, E = %d\n", graph->V, graph->E);
    for(int i = 0; i < graph->V; i++) {
        Vertex* vertex = vector_get(graph->vertices, i);
        printf("%d: ", vertex->data);
        for(int j = 0; j < vector_size(vertex->outgoing_edges); j++) {
            Edge* edge = vector_get(vertex->outgoing_edges, j);
            printf("%d ", edge->to_vertex->data);
        }
        printf("\n");
    }
}

void graph_destruct(Graph* graph) {
    for(int i = 0; i < graph->V; i++) {
        Vertex* vertex = vector_get(graph->vertices, i);
        for(int j = 0; j < vector_size(vertex->outgoing_edges); j++) {
            Edge* edge = vector_get(vertex->outgoing_edges, j);
            free(edge);
        }
        vector_destroy(vertex->outgoing_edges);
        vector_destroy(vertex->incoming_edges);
        free(vertex);
    }
    vector_destroy(graph->vertices);
    free(graph);
}


