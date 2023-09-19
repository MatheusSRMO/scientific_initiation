#include "vrp.h"

typedef struct node {
    int id;
    int x;
    int y;
    int demand;
} Node;

struct vrp {
    char* name;
    char* comment;
    char* type;
    int dimension;
    char* edge_weight_type;
    int capacity;
    Node* nodes;
};

void vrp_file_reader(FILE* file, void** data) {
    Vrp *vrp = (Vrp*) malloc(sizeof(Vrp));

    vrp->name = (char*) malloc(sizeof(char) * 256);
    vrp->comment = (char*) malloc(sizeof(char) * 256);
    vrp->type = (char*) malloc(sizeof(char) * 256);
    vrp->edge_weight_type = (char*) malloc(sizeof(char) * 256);
    vrp->dimension = 0;
    vrp->capacity = 0;
    vrp->nodes = NULL;

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strncmp(buffer, "NAME :", 6) == 0) {
            sscanf(buffer, "NAME : %[^\n]", vrp->name);
        }
        else if (strncmp(buffer, "COMMENT :", 9) == 0) {
            sscanf(buffer, "COMMENT : %[^\n]", vrp->comment);
        }
        else if (strncmp(buffer, "TYPE :", 6) == 0) {
            sscanf(buffer, "TYPE : %[^\n]", vrp->type);
        }
        else if (strncmp(buffer, "DIMENSION :", 11) == 0) {
            sscanf(buffer, "DIMENSION : %d", &vrp->dimension);
        }
        else if (strncmp(buffer, "EDGE_WEIGHT_TYPE :", 18) == 0) {
            sscanf(buffer, "EDGE_WEIGHT_TYPE : %[^\n]", vrp->edge_weight_type);
        }
        else if (strncmp(buffer, "CAPACITY :", 10) == 0) {
            sscanf(buffer, "CAPACITY : %d", &vrp->capacity);
        }
        else if (strncmp(buffer, "NODE_COORD_SECTION", 18) == 0) {
            vrp->nodes = malloc(sizeof(Node) * vrp->dimension);

            for (int i = 0; i < vrp->dimension; i++) {
                fgets(buffer, sizeof(buffer), file);
                sscanf(buffer, "%d %d %d", &vrp->nodes[i].id, &vrp->nodes[i].x, &vrp->nodes[i].y);
            }
        }
        else if (strncmp(buffer, "DEMAND_SECTION", 14) == 0) {
            for (int i = 0; i < vrp->dimension; i++) {
                fgets(buffer, sizeof(buffer), file);
                sscanf(buffer, "%d %d", &vrp->nodes[i].id, &vrp->nodes[i].demand);
            }
        }
        else if (strncmp(buffer, "DEPOT_SECTION", 13) == 0) {
            fgets(buffer, sizeof(buffer), file);
        }
        else if (strncmp(buffer, "-1", 2) == 0) {
            break;
        }
    }

    *data = (void*) vrp;
}

void vrp_file_data_to_edge_list(void* data, EdgeList* edge_list) {
    Vrp *vrp = (Vrp*) data;
    for (int i = 0; i < vrp->dimension; i++) {
        for (int j = i + 1; j < vrp->dimension; j++) {
            float weight = sqrt(pow(vrp->nodes[i].x - vrp->nodes[j].x, 2) + pow(vrp->nodes[i].y - vrp->nodes[j].y, 2));
            edge_list_add(edge_list, vrp->nodes[i].id-1, vrp->nodes[j].id-1, weight);
        }
    }
}

void vrp_file_writer(FILE* file, void* data, char* file_name) {
    Vrp *vrp = (Vrp*) data;
    printf("NAME : %s\n", vrp->name);
    printf("COMMENT : %s\n", vrp->comment);
    printf("TYPE : %s\n", vrp->type);
    printf("DIMENSION : %d\n", vrp->dimension);
    printf("EDGE_WEIGHT_TYPE : %s\n", vrp->edge_weight_type);
    printf("CAPACITY : %d\n", vrp->capacity);
    printf("NODE_COORD_SECTION\n");
    for (int i = 0; i < vrp->dimension; i++) {
        printf("%d %d %d\n", vrp->nodes[i].id, vrp->nodes[i].x, vrp->nodes[i].y);
    }
    printf("DEMAND_SECTION\n");
    for (int i = 0; i < vrp->dimension; i++) {
        printf("%d %d\n", vrp->nodes[i].id, vrp->nodes[i].demand);
    }
    printf("DEPOT_SECTION\n");
    printf("1\n");
    printf("-1\n");
    printf("EOF\n");
}

void vrp_file_destructor(void* data) {
    Vrp *vrp = (Vrp*) data;
    free(vrp->name);
    free(vrp->comment);
    free(vrp->type);
    free(vrp->edge_weight_type);
    free(vrp->nodes);
    free(vrp);
}

int vrp_file_get_dimension(void* data) {
    Vrp *vrp = (Vrp*) data;
    return vrp->dimension;
}
