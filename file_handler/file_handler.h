#ifndef _CVRP_IO_FILE_H_
#define _CVRP_IO_FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef struct file_handler FileHandler;
typedef struct cvrp_file CVRPFile;

FileHandler* file_handler_create(char* filename, char* mode, void (*file_reader)(FILE*,void**), void (*file_writer)(FILE*,void*, char*), void (*file_destructor)(void*));

void file_handler_destroy(FileHandler *file_handler);

void file_handler_read_data(FileHandler *file_handler);

void file_handler_write_data(FileHandler *file_handler, char* file_name);

void file_handler_destroy_data(FileHandler *file_handler);


#endif // _CVRP_IO_FILE_H_