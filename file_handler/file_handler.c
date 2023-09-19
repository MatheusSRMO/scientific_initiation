#include "file_handler.h"


struct file_handler {
    FILE *file;
    char *filename;
    void* data;
    void (*file_reader)(FILE*,void**);
    void (*file_data_to_edge_list)(void*, EdgeList*);
    void (*file_writer)(FILE*,void*, char*);
    void (*file_destructor)(void*);
    int (*file_get_dimension)(void*);
    int (*file_get_edges_dimension)(void*);
};


FileHandler* file_handler_create(
    char* filename,
    char* mode,
    void (*file_reader)(FILE*,void**),
    void (*file_data_to_edge_list)(void*, EdgeList*),
    void (*file_writer)(FILE*,void*, char*),
    void (*file_destructor)(void*),
    int (*file_get_dimension)(void*),
    int (*file_get_edges_dimension)(void*)
) {
    FileHandler *file_handler = (FileHandler*) malloc(sizeof(FileHandler));
    file_handler->file = fopen(filename, mode);
    file_handler->filename = (char*) malloc(sizeof(char) * (strlen(filename) + 1));
    strcpy(file_handler->filename, filename);
    file_handler->data = NULL;
    file_handler->file_reader = file_reader;
    file_handler->file_data_to_edge_list = file_data_to_edge_list;
    file_handler->file_writer = file_writer;
    file_handler->file_destructor = file_destructor;
    file_handler->file_get_dimension = file_get_dimension;
    file_handler->file_get_edges_dimension = file_get_edges_dimension;
    return file_handler;
}

void file_handler_destroy(FileHandler *file_handler) {
    if (file_handler->file != NULL) {
        fclose(file_handler->file);
    }
    if (file_handler->filename != NULL) {
        free(file_handler->filename);
    }
    if (file_handler->data != NULL) {
        file_handler_destroy_data(file_handler);
    }
    free(file_handler);
}

void file_handler_read_data(FileHandler *file_handler) {
    if (file_handler->file != NULL && file_handler->file_reader != NULL) {
        file_handler->file_reader(file_handler->file, &(file_handler->data));
    }
}

void file_handler_data_to_edge_list(FileHandler *file_handler, EdgeList *edge_list){
    if (file_handler->data != NULL && file_handler->file_data_to_edge_list != NULL) {
        file_handler->file_data_to_edge_list(file_handler->data, edge_list);
    }
}

void file_handler_write_data(FileHandler *file_handler, char* file_name) {
    if (file_handler->file != NULL && file_handler->file_writer != NULL) {
        file_handler->file_writer(file_handler->file, file_handler->data, file_name);
    }
}

void file_handler_destroy_data(FileHandler *file_handler) {
    if (file_handler->data != NULL && file_handler->file_destructor != NULL) {
        file_handler->file_destructor(file_handler->data);
    }
}

int file_handler_get_dimension(FileHandler *file_handler) {
    if (file_handler->data != NULL && file_handler->file_get_dimension != NULL) {
        return file_handler->file_get_dimension(file_handler->data);
    }
    return -1;
}

int file_handler_get_edges_dimension(FileHandler *file_handler) {
    if (file_handler->data != NULL && file_handler->file_get_edges_dimension != NULL) {
        return file_handler->file_get_edges_dimension(file_handler->data);
    }
    return -1;
}
