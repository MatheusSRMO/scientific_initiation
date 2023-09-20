#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../edge_list/edge_list.h"

enum graph_type {
    adj_matrix,
    adj_list
};

typedef enum graph_type graph_type;

typedef struct graph Graph;

Graph *graph_create(int V, graph_type type);

void graph_add_edge(Graph *graph, int v, int w, float weight);

float graph_get_weight(Graph *graph, int v, int w);

int graph_get_V(Graph *graph);

void graph_print(Graph *graph);

void graph_destroy(Graph *graph);

void graph_to_edge_list(Graph *graph, EdgeList *edge_list);

void graph_of_edge_list(Graph *graph, EdgeList *edge_list);

#endif