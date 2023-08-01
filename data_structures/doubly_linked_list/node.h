
#ifndef _NODE_H_
#define _NODE_H_

#include "../types.h"

typedef struct Node {
    data_type data;
    struct Node *next;
    struct Node *prev;
} Node;

Node *node_construct(data_type data, Node *next, Node *prev);
void node_destroy(Node *node);
void node_print(Node *n, void (*print_fn)(data_type));

#endif