#include "file_handler.h"



float euclidean_distance(float x1, float y1, float x2, float y2) {
    float x = x1 - x2;
    float y = y1 - y2;
    return sqrt(x * x + y * y);
}

typedef struct construct {
    int id;
    float x;
    float y;
} Construct;

typedef struct node {
    int id;
    float x;
    float y;
    int demand;
} Node;

typedef struct Edge {
    unsigned short int from;
    unsigned short int to;
    float weight; // Euclidean distance between the two nodes
} Edge;

struct file_handler {
    FILE *file;
    char *file_name;
    char* name;
    char* comment;
    char* type;
    int dimension;
    char* edge_weight_type;
    int capacity;
    int edges_dimension;
    int constructions_dimension;
    Node* nodes;
    Edge* edges;
    Construct* constructs;
    ProblemType problem_type;
};

FileHandler* file_handler_create(char* file_name, ProblemType problem_type) {
    FileHandler* file_handler = (FileHandler*) malloc(sizeof(FileHandler));
    file_handler->file = fopen(file_name, "r");
    file_handler->file_name = file_name;
    file_handler->problem_type = problem_type;

    // Aloca memória para os campos do FileHandler que são strings
    file_handler->name = (char*) malloc(sizeof(char) * 256);
    file_handler->comment = (char*) malloc(sizeof(char) * 256);
    file_handler->type = (char*) malloc(sizeof(char) * 256);
    file_handler->edge_weight_type = (char*) malloc(sizeof(char) * 256);

    // Inicializa os campos do FileHandler que são strings como vazios
    file_handler->name[0] = '\0';
    file_handler->comment[0] = '\0';
    file_handler->type[0] = '\0';
    file_handler->edge_weight_type[0] = '\0';

    // Inicializa os campos do FileHandler que são inteiros
    file_handler->dimension = 0;
    file_handler->capacity = 0;
    file_handler->edges_dimension = 0;
    file_handler->constructions_dimension = 0;

    // Inicializa os campos do FileHandler que são ponteiros como NULL
    file_handler->nodes = NULL;
    file_handler->edges = NULL;
    file_handler->constructs = NULL;

    // Chama a função que lê o arquivo
    if (file_handler->problem_type == cvrp)
        cvrp_file_reader(file_handler->file, file_handler);
    else if (file_handler->problem_type == scp)
        scp_file_reader(file_handler->file, file_handler);
    else if (file_handler->problem_type == tsp)
        tsp_file_reader(file_handler->file, file_handler);

    return file_handler;
}

int file_handler_get_dimension(FileHandler* file_handler) {
    return file_handler->dimension;
}

int file_handler_get_capacity(FileHandler* file_handler) {
    return file_handler->capacity;
}

int file_handler_get_edges_dimension(FileHandler* file_handler) {
    if (file_handler->problem_type == cvrp || 
        file_handler->problem_type == tsp) {
        return (file_handler->dimension * (file_handler->dimension - 1)) / 2;
    }
    else if (file_handler->problem_type == scp) {
        return file_handler->edges_dimension;
    }
}

int file_handler_get_constructions_dimension(FileHandler* file_handler) {
    return file_handler->constructions_dimension;
}

void file_handler_to_edge_list(FileHandler* file_handler, EdgeList* edge_list) {
    if (file_handler->problem_type == cvrp)
        cvrp_file_data_to_edge_list(file_handler, edge_list);
    else if (file_handler->problem_type == scp)
        scp_file_data_to_edge_list(file_handler, edge_list);
    else if (file_handler->problem_type == tsp)
        tsp_file_data_to_edge_list(file_handler, edge_list);
}

void file_handler_print(FileHandler* file_handler) {
    printf("File name: %s\n", file_handler->file_name);
    printf("Name: %s\n", file_handler->name);
    printf("Comment: %s\n", file_handler->comment);
    printf("Type: %s\n", file_handler->type);
    if(file_handler->dimension > 0)
        printf("Dimension: %d\n", file_handler->dimension);
    printf("Edge weight type: %s\n", file_handler->edge_weight_type);
    if(file_handler->capacity > 0)
        printf("Capacity: %d\n", file_handler->capacity);
    if(file_handler->edges_dimension > 0)
        printf("Edges dimension: %d\n", file_handler->edges_dimension);
    if(file_handler->constructions_dimension > 0)
        printf("Constructions dimension: %d\n", file_handler->constructions_dimension);
    printf("NODE_COORD_SECTION\n");
    printf("ID\tX\tY\n");
    for (int i = 0; i < file_handler->dimension; i++) {
        printf("%d\t%.2f\t%.2f\n", file_handler->nodes[i].id, file_handler->nodes[i].x, file_handler->nodes[i].y);
    }
    if (file_handler->edges_dimension > 0) {
        printf("Edges:\n");
        printf("From\tTo\tWeight\n");
        for (int i = 0; i < file_handler->edges_dimension; i++) {
            printf("%d\t%d\t%f\n", file_handler->edges[i].from, file_handler->edges[i].to, file_handler->edges[i].weight);
        }
    }
    if (file_handler->constructions_dimension > 0) {
        printf("Constructs:\n");
        printf("ID\tX\tY\n");
        for (int i = 0; i < file_handler->constructions_dimension; i++) {
            printf("%d\t%f\t%f\n", file_handler->constructs[i].id, file_handler->constructs[i].x, file_handler->constructs[i].y);
        }
    }
}

void file_handler_destroy(FileHandler* file_handler) {
    fclose(file_handler->file);
    free(file_handler->name);
    free(file_handler->comment);
    free(file_handler->type);
    free(file_handler->edge_weight_type);
    free(file_handler->nodes);
    free(file_handler->edges);
    free(file_handler->constructs);
    free(file_handler);
}


void cvrp_file_reader(FILE* file, FileHandler* file_handler) {
    strcpy(file_handler->type, "CVRP");
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strncmp(buffer, "NAME :", 6) == 0) {
            sscanf(buffer, "NAME : %[^\n]", file_handler->name);
        }
        if(strncmp(buffer, "TYPE :", 6) == 0) {
            char type[256];
            sscanf(buffer, "TYPE : %[^\n]", type);
            printf("%s\n", type);

            if (strcmp(type, "CVRP") != 0) {
                printf("Error: file is not a CVRP file\n");
                exit(1);
            }
        }
        else if (strncmp(buffer, "COMMENT :", 9) == 0) {
            sscanf(buffer, "COMMENT : %[^\n]", file_handler->comment);
        }
        else if (strncmp(buffer, "DIMENSION :", 11) == 0) {
            sscanf(buffer, "DIMENSION : %d", &file_handler->dimension);
        }
        else if (strncmp(buffer, "EDGE_WEIGHT_TYPE :", 18) == 0) {
            sscanf(buffer, "EDGE_WEIGHT_TYPE : %[^\n]", file_handler->edge_weight_type);
        }
        else if (strncmp(buffer, "CAPACITY :", 10) == 0) {
            sscanf(buffer, "CAPACITY : %d", &file_handler->capacity);
        }
        else if (strncmp(buffer, "NODE_COORD_SECTION", 18) == 0) {
            file_handler->nodes = malloc(sizeof(Node) * file_handler->dimension);

            for (int i = 0; i < file_handler->dimension; i++) {
                fgets(buffer, sizeof(buffer), file);
                sscanf(
                    buffer,
                    "%d %f %f",
                    &file_handler->nodes[i].id,
                    &file_handler->nodes[i].x, 
                    &file_handler->nodes[i].y
                );
            }
        }
        else if (strncmp(buffer, "DEMAND_SECTION", 14) == 0) {
            for (int i = 0; i < file_handler->dimension; i++) {
                fgets(buffer, sizeof(buffer), file);
                sscanf(buffer, "%d %d", &file_handler->nodes[i].id, &file_handler->nodes[i].demand);
            }
        }
        else if (strncmp(buffer, "DEPOT_SECTION", 13) == 0) {
            fgets(buffer, sizeof(buffer), file);
        }
        else if (strncmp(buffer, "-1", 2) == 0) {
            break;
        }
    }
}

void scp_file_reader(FILE* file, FileHandler* file_handler) {
    strcpy(file_handler->type, "SCP");

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strncmp(buffer, "NAME :", 6) == 0) {
            sscanf(buffer, "NAME : %[^\n]", file_handler->name);
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
            sscanf(buffer, "COMMENT : %[^\n]", file_handler->comment);
        }
        else if (strncmp(buffer, "DIMENSION :", 11) == 0) {
            sscanf(buffer, "DIMENSION : %d", &file_handler->dimension);
        }
        else if (strncmp(buffer, "EDGES_DIMENSION :", 17) == 0) {
            sscanf(buffer, "EDGES_DIMENSION : %d", &file_handler->edges_dimension);
        }
        else if (strncmp(buffer, "CONSTRUCTIONS_DIMENSION :", 25) == 0) {
            sscanf(buffer, "CONSTRUCTIONS_DIMENSION : %d", &file_handler->constructions_dimension);
        }
        else if (strncmp(buffer, "EDGE_WEIGHT_TYPE :", 18) == 0) {
            sscanf(buffer, "EDGE_WEIGHT_TYPE : %[^\n]", file_handler->edge_weight_type);
        }
        else if (strncmp(buffer, "NODE_COORD_SECTION", 18) == 0) {
            file_handler->nodes = malloc(sizeof(Node) * file_handler->dimension);

            for (int i = 0; i < file_handler->dimension; i++) {
                fgets(buffer, sizeof(buffer), file);
                sscanf(buffer, "%d %f %f", &file_handler->nodes[i].id, &file_handler->nodes[i].x, &file_handler->nodes[i].y);
            }
        }
        else if (strncmp(buffer, "EDGES_SECTION", 13) == 0) {
            file_handler->edges = malloc(sizeof(Edge) * file_handler->edges_dimension);

            for (int i = 0; i < file_handler->edges_dimension; i++) {
                fgets(buffer, sizeof(buffer), file);
                sscanf(buffer, "%hd %hd", &file_handler->edges[i].from, &file_handler->edges[i].to);
                file_handler->edges[i].weight = 0;
                Node node1 = file_handler->nodes[file_handler->edges[i].from-1];
                Node node2 = file_handler->nodes[file_handler->edges[i].to-1];
                file_handler->edges[i].weight = euclidean_distance(node1.x, node1.y, node2.x, node2.y);
            }
        }
        else if (strncmp(buffer, "CONSTRUCTIONS_SECTION", 21) == 0) {
            file_handler->constructs = malloc(sizeof(Construct) * file_handler->constructions_dimension);

            for (int i = 0; i < file_handler->constructions_dimension; i++) {
                fgets(buffer, sizeof(buffer), file);
                sscanf(buffer, "%d %f %f", &file_handler->constructs[i].id, &file_handler->constructs[i].x, &file_handler->constructs[i].y);
            }
        }
    }
}

void tsp_file_reader(FILE* file, FileHandler* file_handler) {
    strcpy(file_handler->type, "TSP");

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strncmp(buffer, "NAME:", 5) == 0) {
            sscanf(buffer, "NAME: %[^\n]", file_handler->name);
        }
        if(strncmp(buffer, "TYPE:", 5) == 0) {
            char type[256];
            sscanf(buffer, "TYPE: %[^\n]", type);

            if (strcmp(type, "TSP") != 0) {
                printf("Error: file is not a TSP file\n");
                exit(1);
            }
        }
        else if (strncmp(buffer, "COMMENT:", 8) == 0) {
            sscanf(buffer, "COMMENT: %[^\n]", file_handler->comment);
        }
        else if (strncmp(buffer, "DIMENSION:", 10) == 0) {
            sscanf(buffer, "DIMENSION: %d", &file_handler->dimension);
        }
        else if (strncmp(buffer, "EDGE_WEIGHT_TYPE:", 17) == 0) {
            sscanf(buffer, "EDGE_WEIGHT_TYPE: %[^\n]", file_handler->edge_weight_type);
        }
        else if (strncmp(buffer, "NODE_COORD_SECTION", 17) == 0) {
            file_handler->nodes = malloc(sizeof(Node) * file_handler->dimension);

            for (int i = 0; i < file_handler->dimension; i++) {
                fgets(buffer, sizeof(buffer), file);
                Node* node = &file_handler->nodes[i];
                sscanf(buffer, "%d %f %f", &node->id, &node->x, &node->y);
            }
        }
    }
}

// Complexidade O(n(n-1)/2) = O(n^2)
void cvrp_file_data_to_edge_list(FileHandler* file_handler, EdgeList* edge_list) {
    for (int i = 0; i < file_handler->dimension; i++) {
        for (int j = i + 1; j < file_handler->dimension; j++) {
            float x1 = file_handler->nodes[i].x;
            float y1 = file_handler->nodes[i].y;
            float x2 = file_handler->nodes[j].x;
            float y2 = file_handler->nodes[j].y;
            float weight = euclidean_distance(x1, y1, x2, y2);
            edge_list_add(edge_list, file_handler->nodes[i].id-1, file_handler->nodes[j].id-1, weight);
        }
    }
}

// Complexidade O(n)
void scp_file_data_to_edge_list(FileHandler* file_handler, EdgeList* edge_list) {
    for (int i = 0; i < file_handler->edges_dimension; i++) {
        edge_list_add(edge_list, file_handler->edges[i].from-1, file_handler->edges[i].to-1, file_handler->edges[i].weight);
    }
}

// Complexidade O(n(n-1)/2) = O(n^2)
void tsp_file_data_to_edge_list(FileHandler* file_handler, EdgeList* edge_list) {
    for (size_t i = 0; i < file_handler->dimension; i++) {
        for (size_t j = i + 1; j < file_handler->dimension; j++) {
            Node node1 = file_handler->nodes[i];
            Node node2 = file_handler->nodes[j];
            
            float weight = euclidean_distance(node1.x, node1.y, node2.x, node2.y);
            edge_list_add(edge_list, node1.id-1, node2.id-1, weight);
        }
    }
}

void file_handler_write_mst(FileHandler* file_handler, EdgeList* mst_list) {
    char* file_name = malloc(sizeof(char) * 256);
    // tira o .tsp do nome do arquivo
    strncpy(file_name, file_handler->file_name, strlen(file_handler->file_name) - 3);
    
    char* extension = ".mst";
    strcat(file_name, extension);
    FILE* file = fopen(file_name, "w");
    fprintf(file, "NAME: %s\n", file_handler->name);
    fprintf(file, "TYPE: MST\n");
    fprintf(file, "DIMENSION: %d\n", file_handler->dimension);
    fprintf(file, "MST_SECTION\n");
    for (int i = 0; i < edge_list_get_size(mst_list); i++) {
        fprintf(file, "%d %d\n", edge_list_get_v(mst_list, i)+1, edge_list_get_w(mst_list, i)+1);
    }
    fprintf(file, "EOF\n");
    fclose(file);
    free(file_name);
}

Point** scp_file_constructs_to_points_list(FileHandler* file_handler) {
    Point** point_list = point_list_create(file_handler->constructions_dimension);
    for (int i = 0; i < file_handler->constructions_dimension; i++) {
        point_list[i] = point_create(file_handler->constructs[i].id ,file_handler->constructs[i].x, file_handler->constructs[i].y);
    }
    return point_list;
}

Point** scp_file_nodes_to_points_list(FileHandler* file_handler) {
    Point** point_list = point_list_create(file_handler->dimension);
    for (int i = 0; i < file_handler->dimension; i++) {
        point_list[i] = point_create(file_handler->nodes[i].id ,file_handler->nodes[i].x, file_handler->nodes[i].y);
    }
    return point_list;
}

// not alocated matrix A, only the pointers
/*
Formato do arquivo:
n m // n = número de linhas, m = número de colunas
a11 a12 a13 ... a1m
a21 a22 a23 ... a2m
a31 a32 a33 ... a3m
...
an1 an2 an3 ... anm
*/
int **read_matrix(char *file_name, int *n, int *m) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", file_name);
        exit(1);
    }
    fscanf(file, "%d %d", n, m);
    int **A = calloc(*n, sizeof(int*));
    for(int i = 0; i < *n; i++) {
        A[i] = calloc(*m, sizeof(int));
    }
    for(int i = 0; i < *n; i++) {
        for(int j = 0; j < *m; j++) {
            fscanf(file, "%d", &A[i][j]);
        }
    }
    fclose(file);
    return A;
}

