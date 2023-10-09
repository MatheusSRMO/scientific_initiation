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
void print_matrix(int **matrix, int linhas, int colunas);
void print_solution(int *solution, int colunas);


int main(int argc, char const *argv[]) {
    
    char* input_file_name = "data/scp/segurança_do_lar_vitoria_es_brasil.scp";

    FileHandler *file_handler = file_handler_create(input_file_name, scp);
    int dimension = file_handler_get_dimension(file_handler);
    int edges_dimension = file_handler_get_edges_dimension(file_handler);
    int constructions_dimension = file_handler_get_constructions_dimension(file_handler);
    printf("Dimension: %d\n", dimension);
    printf("Edges dimension: %d\n", edges_dimension);
    printf("Constructions dimension: %d\n", constructions_dimension);

    Point **points_list = scp_file_nodes_to_points_list(file_handler);
    print_points(points_list, dimension);

    Point **constructions_list = scp_file_constructs_to_points_list(file_handler);
    print_constructions(constructions_list, constructions_dimension);

    int range = 100;
    int linhas = constructions_dimension;
    int colunas = dimension;

    int **A = build_matrix_A(constructions_list, points_list, constructions_dimension, dimension, range);
    print_matrix(A, linhas, colunas);

    int* solution = find_minimal_coverage(A, linhas, colunas);
    printf("Solution: ");
    print_solution(solution, colunas);

    Graph *graph = graph_create(dimension, adj_matrix);

    EdgeList *edge_list = edge_list_create(edges_dimension);
    file_handler_to_edge_list(file_handler, edge_list);
    graph_from_edge_list(graph, edge_list);

    graph_to_dot_solve(graph, points_list, constructions_list, constructions_dimension, solution, colunas, "graph.dot");

    edge_list_destroy(edge_list);
    graph_destroy(graph);
    for(int i = 0; i < constructions_dimension; i++) {
        free(A[i]);
    }
    free(A);
    free(solution);
    point_list_destroy(points_list, dimension);
    point_list_destroy(constructions_list, constructions_dimension);
    file_handler_destroy(file_handler);
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

void print_matrix(int **matrix, int linhas, int colunas) {
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_solution(int *solution, int colunas) {
    for(int i = 0; i < colunas; i++) {
        printf("%d ", solution[i]);
    }
    printf("\n");
}
