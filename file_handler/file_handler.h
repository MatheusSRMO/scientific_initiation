#ifndef _CVRP_IO_FILE_H_
#define _CVRP_IO_FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include "../edge_list/edge_list.h"

typedef struct file_handler FileHandler;

FileHandler* file_handler_create(
    char* filename,
    char* mode,
    void (*file_reader)(FILE*,void**),
    void (*file_data_to_edge_list)(void*, EdgeList*),
    void (*file_writer)(FILE*,void*, char*),
    void (*file_destructor)(void*),
    int (*file_get_dimension)(void*),
    int (*file_get_edges_dimension)(void*)
);

void file_handler_destroy(FileHandler *file_handler);

void file_handler_read_data(FileHandler *file_handler);

void file_handler_write_data(FileHandler *file_handler, char* file_name);

void file_handler_destroy_data(FileHandler *file_handler);

int file_handler_get_dimension(FileHandler *file_handler);

int file_handler_get_edges_dimension(FileHandler *file_handler);


void file_handler_data_to_edge_list(FileHandler *file_handler, EdgeList *edge_list);


#endif // _CVRP_IO_FILE_H_