#include "file_handler.h"


struct file_handler {
    FILE *file;
    char *filename;
    void* data;
    void (*file_reader)(FILE*,void**);
    void (*file_writer)(FILE*,void*, char*);
    void (*file_destructor)(void*);
};


FileHandler* file_handler_create(char* filename, char* mode, void (*file_reader)(FILE*,void**), void (*file_writer)(FILE*,void*, char*), void (*file_destructor)(void*)) {
    FileHandler *file_handler = (FileHandler*) malloc(sizeof(FileHandler));
    file_handler->file = fopen(filename, mode);
    file_handler->filename = (char*) malloc(sizeof(char) * (strlen(filename) + 1));
    strcpy(file_handler->filename, filename);
    file_handler->data = NULL;
    file_handler->file_reader = file_reader;
    file_handler->file_writer = file_writer;
    file_handler->file_destructor = file_destructor;
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
        printf("Reading data from file %s\n", file_handler->filename);
        file_handler->file_reader(file_handler->file, &(file_handler->data));
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
