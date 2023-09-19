#include "scp.h"

/*
FORMAT OF THE FILE:
NAME: <string>
TYPE: SCP
COMMENT: <string>
DIMENSION: <int>
EDGES_DIMENSION: <int>
CONSTRUCTIONS_DIMENSION: <int>
EDGE_WEIGHT_TYPE: EUC_2D
NODE_COORD_SECTION
<int> <float> <float>
<int> <float> <float>
...
<int> <float> <float>
EDGES_SECTION
<int> <int>
<int> <int>
...
<int> <int>
CONSTRUCTIONS_SECTION // id, x, y
<int> <float> <float>
<int> <float> <float>
...
<int> <float> <float>
*/

typedef struct point {
    float x;
    float y;
} Point;

typedef struct construct {
    int id;
    Point point;
} Construct;

typedef struct node {
    int id;
    Point point;
} Node;

typedef struct Edge {
    int from;
    int to;
    int weight; // Euclidean distance between the two nodes
} Edge;

struct scp {
    char* name;
    char* comment;
    int dimension;
    int edges_dimension;
    int constructions_dimension;
    char* edge_weight_type;
    Node* nodes;
    Edge* edges;
    Construct* constructs;
};

float euclidean_distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void scp_file_reader(FILE* file, void** data) {
    Scp *scp = (Scp*) malloc(sizeof(Scp));

    scp->name = (char*) malloc(sizeof(char) * 256);
    scp->comment = (char*) malloc(sizeof(char) * 256);
    scp->edge_weight_type = (char*) malloc(sizeof(char) * 256);
    scp->dimension = 0;
    scp->edges_dimension = 0;
    scp->constructions_dimension = 0;
    scp->nodes = NULL;
    scp->edges = NULL;
    scp->constructs = NULL;

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strncmp(buffer, "NAME :", 6) == 0) {
            sscanf(buffer, "NAME : %[^\n]", scp->name);
        }
        if(strncmp(buffer, "TYPE :", 6) == 0) {
            char type[256];
            sscanf(buffer, "TYPE : %[^\n]", type);

            if (strcmp(type, "SCP") != 0) {
                printf("Error: file is not a SCP file\n");
                exit(1);
            }
        }
        else if (strncmp(buffer, "COMMENT :", 9) == 0) {
            sscanf(buffer, "COMMENT : %[^\n]", scp->comment);
        }
        else if (strncmp(buffer, "DIMENSION :", 11) == 0) {
            sscanf(buffer, "DIMENSION : %d", &scp->dimension);
        }
        else if (strncmp(buffer, "EDGES_DIMENSION :", 17) == 0) {
            sscanf(buffer, "EDGES_DIMENSION : %d", &scp->edges_dimension);
        }
        else if (strncmp(buffer, "CONSTRUCTIONS_DIMENSION :", 25) == 0) {
            sscanf(buffer, "CONSTRUCTIONS_DIMENSION : %d", &scp->constructions_dimension);
        }
        else if (strncmp(buffer, "EDGE_WEIGHT_TYPE :", 18) == 0) {
            sscanf(buffer, "EDGE_WEIGHT_TYPE : %[^\n]", scp->edge_weight_type);
        }
        else if (strncmp(buffer, "NODE_COORD_SECTION", 18) == 0) {
            scp->nodes = malloc(sizeof(Node) * scp->dimension);

            for (int i = 0; i < scp->dimension; i++) {
                fgets(buffer, sizeof(buffer), file);
                sscanf(buffer, "%d %f %f", &scp->nodes[i].id, &scp->nodes[i].point.x, &scp->nodes[i].point.y);
            }
        }
        else if (strncmp(buffer, "EDGES_SECTION", 13) == 0) {
            scp->edges = malloc(sizeof(Edge) * scp->edges_dimension);

            for (int i = 0; i < scp->edges_dimension; i++) {
                fgets(buffer, sizeof(buffer), file);
                sscanf(buffer, "%d %d", &scp->edges[i].from, &scp->edges[i].to);
                scp->edges[i].weight = 0;
                Point p1 = scp->nodes[scp->edges[i].from - 1].point;
                Point p2 = scp->nodes[scp->edges[i].to - 1].point;

                scp->edges[i].weight = euclidean_distance(p1, p2);
            }
        }
        else if (strncmp(buffer, "CONSTRUCTIONS_SECTION", 21) == 0) {
            scp->constructs = malloc(sizeof(Construct) * scp->constructions_dimension);

            for (int i = 0; i < scp->constructions_dimension; i++) {
                fgets(buffer, sizeof(buffer), file);
                sscanf(buffer, "%d %f %f", &scp->constructs[i].id, &scp->constructs[i].point.x, &scp->constructs[i].point.y);
            }
        }
    }

    *data = scp;
}

void scp_file_data_to_edge_list(void* data, EdgeList* edge_list) {
    Scp *scp = (Scp*) data;
    for (int i = 0; i < scp->edges_dimension; i++) {
        edge_list_add(edge_list, scp->edges[i].from-1, scp->edges[i].to-1, scp->edges[i].weight);
    }
}

void scp_file_writer(FILE* file, void* data, char* file_name) {
    Scp* scp = (Scp*) data;

    printf("NAME : %s\n", scp->name);
    printf("COMMENT : %s\n", scp->comment);
    printf("DIMENSION : %d\n", scp->dimension);
    printf("EDGES_DIMENSION : %d\n", scp->edges_dimension);
    printf("CONSTRUCTIONS_DIMENSION : %d\n", scp->constructions_dimension);
    printf("EDGE_WEIGHT_TYPE : %s\n", scp->edge_weight_type);
    printf("NODE_COORD_SECTION\n");

    for (int i = 0; i < scp->dimension; i++) {
        printf("%d %f %f\n", scp->nodes[i].id, scp->nodes[i].point.x, scp->nodes[i].point.y);
    }

    printf("EDGES_SECTION\n");

    for (int i = 0; i < scp->edges_dimension; i++) {
        printf("%d %d %d\n", scp->edges[i].from, scp->edges[i].to, scp->edges[i].weight);
    }

    printf("CONSTRUCTIONS_SECTION\n");

    for (int i = 0; i < scp->constructions_dimension; i++) {
        printf("%d %f %f\n", scp->constructs[i].id, scp->constructs[i].point.x, scp->constructs[i].point.y);
    }
}

void scp_file_destructor(void* data) {
    Scp* scp = (Scp*) data;

    free(scp->name);
    free(scp->comment);
    free(scp->edge_weight_type);
    free(scp->nodes);
    free(scp->edges);
    free(scp->constructs);
    free(scp);
}

int scp_file_get_dimension(void* data) {
    Scp* scp = (Scp*) data;
    return scp->dimension;
}

int scp_file_get_edges_dimension(void* data) {
    Scp* scp = (Scp*) data;
    return scp->edges_dimension;
}
