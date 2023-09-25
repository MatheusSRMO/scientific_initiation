#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "src/file_handler/file_handler.h"
#include "src/graph/graph.h"
#include "src/edge_list/edge_list.h"
#include "src/linear_programing/linear_programing.h"


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
    for(int i = 0; i < dimension; i++) {
        float x = point_get_x(points_list[i]);
        float y = point_get_y(points_list[i]);
        int id = point_get_id(points_list[i]);
        printf("Point %d: (%f, %f)\n", id, x, y);
    }

    Point **constructions_list = scp_file_constructs_to_points_list(file_handler);
    for(int i = 0; i < constructions_dimension; i++) {
        float x = point_get_x(constructions_list[i]);
        float y = point_get_y(constructions_list[i]);
        int id = point_get_id(constructions_list[i]);
        printf("Construction %d: (%f, %f)\n", id, x, y);
    }

    int range = 100;
    int linhas = constructions_dimension;
    int colunas = dimension;

    // Constroi a matriz A, que tem valores 0 ou 1, onde 1 indica se a construção i está no raio de alcance do ponto j
    int **A = calloc(linhas, sizeof(int*));
    for(int i = 0; i < linhas; i++) {
        A[i] = calloc(colunas, sizeof(int));
    }
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            A[i][j] = point_in_range(constructions_list[i], points_list[j], range, eucledian);
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }


    // Constroi o vetor b, que tem valores 0 ou 1, lado direito da inequação
    int *b = calloc(linhas, sizeof(int));
    for(int i = 0; i < linhas; i++) {
        b[i] = 1;
    }

    int* solucao = calloc(colunas, sizeof(int));
    printf("Solucao inicial:\n");
    for(int i = 0; i < colunas; i++) {
        solucao[i] = 0;
        printf("%d ", solucao[i]);
    }
    printf("\n");

    // calcularSolucaoOtima(A, b, solucao, constructions_dimension, dimension);

    // printf("Solucao otima:\n");
    // for(int i = 0; i < colunas; i++) {
    //     printf("%d ", solucao[i]);
    // }

    // LinearPrograming *lp = linear_programing_create(colunas, linhas, LP_MIN, LP_GREATER_EQUAL);
    // linear_programing_set_constraint_matrix(lp, A);


    // linear_programing_set_right_hand_side(lp, b);

    // lp_solve(lp);

    // linear_programing_get_solution(lp, solucao);

    // printf("Solucao otima:\n");
    // for(int i = 0; i < colunas; i++) {
    //     printf("%d ", solucao[i]);
    // }
    // printf("\n");


    int sol[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}; // solução ótima

    // Constrói o grafo
    Graph *graph = graph_create(dimension, adj_matrix);

    EdgeList *edge_list = edge_list_create(edges_dimension);
    file_handler_to_edge_list(file_handler, edge_list);
    graph_from_edge_list(graph, edge_list);

    graph_to_dot_solve(graph, points_list, constructions_list, constructions_dimension, sol, colunas, "graph.dot");




    // linear_programing_destroy(lp);
    edge_list_destroy(edge_list);
    graph_destroy(graph);
    for(int i = 0; i < constructions_dimension; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(solucao);
    point_list_destroy(points_list, dimension);
    point_list_destroy(constructions_list, constructions_dimension);
    file_handler_destroy(file_handler);



    return 0;
}
