#ifndef _CVRP_IO_FILE_H_
#define _CVRP_IO_FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../edge_list/edge_list.h"
#include "../point/point.h"

typedef enum {
    cvrp,
    scp,
    tsp
} ProblemType;

typedef struct file_handler FileHandler;


FileHandler* file_handler_create(char* file_name, ProblemType problem_type);
void file_handler_to_edge_list(FileHandler* file_handler, EdgeList* edge_list);
void file_handler_print(FileHandler* file_handler);
void file_handler_destroy(FileHandler* file_handler);

int file_handler_get_dimension(FileHandler* file_handler);
int file_handler_get_capacity(FileHandler* file_handler);
int file_handler_get_edges_dimension(FileHandler* file_handler);
int file_handler_get_constructions_dimension(FileHandler* file_handler);

void cvrp_file_data_to_edge_list(FileHandler* file_handler, EdgeList* edge_list);
void scp_file_data_to_edge_list(FileHandler* file_handler, EdgeList* edge_list);
void tsp_file_data_to_edge_list(FileHandler* file_handler, EdgeList* edge_list);

Point** scp_file_constructs_to_points_list(FileHandler* file_handler);
Point** scp_file_nodes_to_points_list(FileHandler* file_handler);

void cvrp_file_reader(FILE* file, FileHandler* file_handler);
void scp_file_reader(FILE* file, FileHandler* file_handler);
void tsp_file_reader(FILE* file, FileHandler* file_handler);


void file_handler_write_mst(FileHandler* file_handler, EdgeList* mst_list);

int **read_matrix(char *file_name, int *n, int *m);

#endif // _CVRP_IO_FILE_H_