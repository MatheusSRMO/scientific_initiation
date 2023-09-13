#ifndef _GRAPH_ADJACENCY_LIST_H_
#define _GRAPH_ADJACENCY_LIST_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Edge {
    int target;
    float weight;
    struct Edge *next;
} Edge;

typedef struct graph {
    int V;
    int E;
    bool directed;
    Edge **adj;
} Graph;

Graph *graph_construct(int V, int E, bool directed);

void graph_add_vertex(Graph* graph, int data);

void graph_add_edge(Graph* graph, int src, float weight, int dest);

void graph_print(Graph* graph);

void graph_destruct(Graph* graph);

#endif // _GRAPH_ADJACENCY_LIST_H_