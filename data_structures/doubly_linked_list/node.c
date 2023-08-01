
#include <stdlib.h>
#include <stdio.h>
#include "node.h"

Node *node_construct(data_type data, Node *next, Node *prev) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = next;
    node->prev = prev;
    return node;
}

void node_destroy(Node *n) {
    free(n);
}

void node_print(Node *n, void (*print_fn)(data_type)) {
    printf("(");

    if (n->prev == NULL)
        printf("NULL");
    else
        print_fn(n->prev->data);

    printf(", ");
    print_fn(n->data);
    printf(", ");

    if (n->next == NULL)
        printf("NULL");
    else
        print_fn(n->next->data);

    printf(")");
}
