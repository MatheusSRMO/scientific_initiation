#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "src/file_handler/file_handler.h"
#include "src/graph/graph.h"
#include "src/edge_list/edge_list.h"
#include "src/local_search_set_cover/local_search_set_cover.h"

/* HEADERS*/
void print_points(Point **points_list, int dimension);
void print_constructions(Point **constructions_list, int constructions_dimension);
int **build_matrix_A(Point **constructions_list, Point **points_list, int constructions_dimension, int dimension, int range);
void print_matrix(int **matrix, int lines, int columns);
void print_solution(int *solution, int columns);
int cont_sets(int *solution, int columns);


int main(int argc, char const *argv[]) {
    // recebe o nome do arquivo de entrada e o raio de cobertura
    if(argc < 4) {
        printf("Usage: %s <input_file_name> <range> <greedy|local_search>\n", argv[0]);
        exit(1);
    }
    char *input_file_name = malloc((strlen(argv[1]) + 1) * sizeof(char));
    strcpy(input_file_name, argv[1]);
    int range = atoi(argv[2]);
    char *method = malloc((strlen(argv[3]) + 1) * sizeof(char));
    strcpy(method, argv[3]);

    // char* input_file_name = "data/scp/jardim_da_penha_vitoria_es_brasil.scp";


    // // Create file handler
    // FileHandler *file_handler = file_handler_create(input_file_name, scp);
    // int dimension = file_handler_get_dimension(file_handler);
    // int edges_dimension = file_handler_get_edges_dimension(file_handler);
    // int constructions_dimension = file_handler_get_constructions_dimension(file_handler);
    // // printf("Dimension: %d\n", dimension);
    // // printf("Edges dimension: %d\n", edges_dimension);
    // // printf("Constructions dimension: %d\n", constructions_dimension);
    // Point **points_list = scp_file_nodes_to_points_list(file_handler);
    // Point **constructions_list = scp_file_constructs_to_points_list(file_handler);


    // // Set line and column dimensions
    // int lines = constructions_dimension;
    // int columns = dimension;


    // builds coverage matrix A
    // int **A = build_matrix_A(constructions_list, points_list, constructions_dimension, dimension, range);
    
    int lines, columns;
    int **A = read_matrix(input_file_name, &lines, &columns);

    int* solution = NULL;
    if(strcmp(method, "--greedy") == 0) {
        solution = greedy_set_cover(A, lines, columns);
    }
    else if(strcmp(method, "--local_search") == 0) {
        solution = local_search_set_cover(A, lines, columns);
    }
    else {
        printf("Invalid method\n");
        exit(1);
    }
    printf("%d", cont_sets(solution, columns));


    // // Generate graph and edge list
    // Graph *graph = graph_create(dimension, adj_matrix);
    // EdgeList *edge_list = edge_list_create(edges_dimension);
    // file_handler_to_edge_list(file_handler, edge_list);
    // graph_from_edge_list(graph, edge_list);


    // // Generate graph.dot and graph.jpg
    // graph_to_dot_solve(graph, points_list, constructions_list, constructions_dimension, solution, columns, range, "graph.dot");
    // system("neato -Tjpg graph.dot -o graph.jpg");
    // remove("graph.dot"); // delete graph.dot


    // /* Frees Allocated Memory */
    // edge_list_destroy(edge_list);
    // graph_destroy(graph);
    for(int i = 0; i < lines; i++) {
        free(A[i]);
    }
    free(A);
    free(solution);
    // point_list_destroy(points_list, dimension);
    // point_list_destroy(constructions_list, constructions_dimension);
    // file_handler_destroy(file_handler);
    free(input_file_name);
    free(method);
    return 0;
}

void print_points(Point **points_list, int dimension) {
    for(int i = 0; i < dimension; i++) {
        float x = point_get_x(points_list[i]);
        float y = point_get_y(points_list[i]);
        int id = point_get_id(points_list[i]);
        printf("Point %d: (%f, %f)\n", id, x, y);
    }
}

void print_constructions(Point **constructions_list, int constructions_dimension) {
    for(int i = 0; i < constructions_dimension; i++) {
        float x = point_get_x(constructions_list[i]);
        float y = point_get_y(constructions_list[i]);
        int id = point_get_id(constructions_list[i]);
        printf("Construction %d: (%f, %f)\n", id, x, y);
    }
}

int **build_matrix_A(Point **constructions_list, Point **points_list, int constructions_dimension, int dimension, int range) {
    int **A = calloc(constructions_dimension, sizeof(int*));
    for(int i = 0; i < constructions_dimension; i++) {
        A[i] = calloc(dimension, sizeof(int));
    }
    for(int i = 0; i < constructions_dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            A[i][j] = point_in_range(constructions_list[i], points_list[j], range, eucledian);
        }
    }
    return A;
}

void print_matrix(int **matrix, int lines, int columns) {
    for(int i = 0; i < lines; i++) {
        for(int j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_solution(int *solution, int columns) {
    int cont = 0;
    printf("Solution: ");
    for(int i = 0; i < columns; i++) {
        printf("%d ", solution[i]);
        if(solution[i]) cont++;
    }
    printf("\n");
    printf("Number of sets: %d\n", cont);
}

int cont_sets(int *solution, int columns) {
    int cont = 0;
    for(int i = 0; i < columns; i++) {
        if(solution[i]) cont++;
    }
    return cont;
}
