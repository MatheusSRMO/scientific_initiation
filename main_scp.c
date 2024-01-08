#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "src/file_handler/file_handler.h"
#include "src/graph/graph.h"
#include "src/edge_list/edge_list.h"
#include "src/local_search_set_cover/local_search_set_cover.h"

/* HEADERS*/

int cont_sets(int *solution, int columns);

int main(int argc, char const *argv[]) {
    // recebe o nome do arquivo de entrada e o raio de cobertura
    if(argc < 3) {
        printf("Usage: %s <input_file_name> <greedy|local_search>\n", argv[0]);
        exit(1);
    }

    int lines, columns;
    int **A = read_matrix((char *)argv[1], &lines, &columns);

    int* solution = NULL;
    if(strcmp(argv[2], "--greedy") == 0) {
        solution = greedy_set_cover(A, lines, columns);
    }
    else if(strcmp(argv[2], "--local_search") == 0) {
        solution = local_search_set_cover(A, lines, columns);
    }
    else {
        printf("Invalid method\n");
        exit(1);
    }
    printf("%d\n", cont_sets(solution, columns));

    for(int i = 0; i < lines; i++) free(A[i]);
    free(A); free(solution);
    return 0;
}

int cont_sets(int *solution, int columns) {
    int cont = 0;
    for(int i = 0; i < columns; i++) {
        cont += solution[i];
    }
    return cont;
}
