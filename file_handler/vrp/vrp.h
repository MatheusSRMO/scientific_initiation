#ifndef _VRP_H_	
#define _VRP_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "../file_handler.h"

typedef struct vrp Vrp;

void vrp_file_reader(FILE* file, void** data);
void vrp_file_data_to_edge_list(void*, EdgeList*);
void vrp_file_writer(FILE* file, void* data, char* file_name);
void vrp_file_destructor(void* data);

int vrp_file_get_dimension(void* data);

#endif // _VRP_H_