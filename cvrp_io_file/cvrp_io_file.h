#ifndef _CVRP_IO_FILE_H_
#define _CVRP_IO_FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>


typedef struct cvrp_instance CVRPInstance;

CVRPInstance *cvrp_read_file(const char *filename);

void cvrp_write_file(const char *filename, CVRPInstance *instance);

void cvrp_free_instance(CVRPInstance *instance);


#endif // _CVRP_IO_FILE_H_