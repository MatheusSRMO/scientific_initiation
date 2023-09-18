#include <stdio.h>
#include <stdlib.h>
#include "file_handler.h"
#include "vrp/vrp.h"
#include "scp/scp.h"

int main() {
    FileHandler *file_handler = file_handler_create("text.scp", "r", scp_file_reader, scp_file_writer, scp_file_destructor);

    file_handler_read_data(file_handler);

    file_handler_write_data(file_handler, "text2.vrp");

    file_handler_destroy(file_handler);

    return 0;
}
