#include "edge_list.h"

typedef struct edge {
    unsigned short int v;
    unsigned short int w;
    float weight;
} Edge;

struct edge_list {
    Edge *edges;
    int size;
    int current;
};

int edge_compare(const void* a, const void* b) {
    return ((Edge*) a)->weight - ((Edge*) b)->weight;
}

EdgeList *edge_list_create(int size) {
    EdgeList *edge_list = (EdgeList *) malloc(sizeof(EdgeList));
    edge_list->edges = (Edge *) malloc(sizeof(Edge) * size);
    edge_list->size = size;
    edge_list->current = 0;
    return edge_list;
}

int edge_list_get_size(EdgeList *edge_list) {
    return edge_list->current;
}

void edge_list_add(EdgeList *edge_list, unsigned short int v, unsigned short int w, float weight) {
    // if (edge_list->current >= edge_list->size) {
    //     printf("EdgeList is full\n");
    //     return;
    // }
    edge_list->edges[edge_list->current].v = v;
    edge_list->edges[edge_list->current].w = w;
    edge_list->edges[edge_list->current].weight = weight;
    edge_list->current++;
}

unsigned short int edge_list_get_v(EdgeList *edge_list, int index) {
    return edge_list->edges[index].v;
}

unsigned short int edge_list_get_w(EdgeList *edge_list, int index) {
    return edge_list->edges[index].w;
}

void edge_list_get_vw(EdgeList *edge_list, int index, unsigned short int *v, unsigned short int *w) {
    *v = edge_list->edges[index].v;
    *w = edge_list->edges[index].w;
}

float edge_list_get_weight(EdgeList *edge_list, int index) {
    return edge_list->edges[index].weight;
}

void edge_list_sort(EdgeList *edge_list) {
    qsort(edge_list->edges, edge_list->current, sizeof(Edge), edge_compare);
}

void edge_list_print(EdgeList *edge_list) {
    printf("v\tw\tweight\n");
    for (int i = 0; i < edge_list->current; i++) {
        printf("%d\t%d\t%.2f\n", edge_list->edges[i].v, edge_list->edges[i].w, edge_list->edges[i].weight);
    }
}

void edge_list_destroy(EdgeList *edge_list) {
    free(edge_list->edges);
    free(edge_list);
}
