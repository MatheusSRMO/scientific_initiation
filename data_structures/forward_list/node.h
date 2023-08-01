
#ifndef _NODE_H_
#define _NODE_H_

#include "../types.h"

typedef struct Node {
    data_type value;
    struct Node *next;
} Node;

Node *node_construct(data_type value, Node *next);
void node_destroy(Node *n);

#endif