#include "utils.h"

void print_vector(int *vector, int size) {
    printf("[");
    for(int i = 0; i < size; i++) {
        printf("%d", vector[i]);
        if(i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}