#ifndef _SCP_H_	
#define _SCP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../file_handler.h"

typedef struct scp Scp;

void scp_file_reader(FILE* file, void** data);
void scp_file_data_to_edge_list(void* data, EdgeList* edge_list);
void scp_file_writer(FILE* file, void* data, char* file_name);
void scp_file_destructor(void* data);

int scp_file_get_dimension(void*);
int scp_file_get_edges_dimension(void*);

#endif