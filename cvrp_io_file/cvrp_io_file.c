#include "cvrp_io_file.h"

typedef struct node {
    unsigned short int id;
    unsigned short int x;
    unsigned short int y;
    unsigned short int demand;
    bool is_depot;
} Node;

typedef struct {
    unsigned short int id;
    unsigned short int from;
    unsigned short int to;
    unsigned short int cost;
    unsigned short int demand;
    bool is_depot;
} Route;

struct cvrp_instance {
    unsigned short int id;
    unsigned short int capacity;
    unsigned short int num_nodes;
    Node *nodes;
    bool has_routes; // Indica se há informações sobre rotas
    unsigned short int num_routes;
    Route *routes;
};

CVRPInstance *cvrp_read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    CVRPInstance *instance = malloc(sizeof(CVRPInstance));
    if (instance == NULL) {
        printf("Error allocating memory for instance\n");
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t len = 0;
    int read;

    unsigned short int id;
    unsigned short int capacity;
    unsigned short int num_nodes;

    // Read instance id
    read = getline(&line, &len, file);
    sscanf(line, "NAME : %*s %hu", &id);
    instance->id = id;

    // Read capacity
    read = getline(&line, &len, file);
    sscanf(line, "CAPACITY : %hu", &capacity);
    instance->capacity = capacity;

    // Read number of nodes
    read = getline(&line, &len, file);
    sscanf(line, "DIMENSION : %hu", &num_nodes);
    instance->num_nodes = num_nodes;

    // Allocate memory for nodes
    Node *nodes = malloc(num_nodes * sizeof(Node));
    if (nodes == NULL) {
        printf("Error allocating memory for nodes\n");
        exit(EXIT_FAILURE);
    }

    // Read node coordinates and demand
    for (unsigned short int i = 0; i < num_nodes; i++) {
        read = getline(&line, &len, file);
        sscanf(line, "%hu %hu %hu %hu", &nodes[i].id, &nodes[i].x, &nodes[i].y, &nodes[i].demand);
        nodes[i].is_depot = (i == 0); // O primeiro nó é o depósito
    }

    // Assign nodes to the instance
    instance->nodes = nodes;

    // Read number of routes if available
    unsigned short int num_routes;
    read = getline(&line, &len, file);
    if (sscanf(line, "NUM_ROUTES : %hu", &num_routes) == 1) {
        instance->has_routes = true;
        instance->num_routes = num_routes;

        // Allocate memory for routes
        Route *routes = malloc(num_routes * sizeof(Route));
        if (routes == NULL) {
            printf("Error allocating memory for routes\n");
            exit(EXIT_FAILURE);
        }

        // Read route information
        for (unsigned short int i = 0; i < num_routes; i++) {
            read = getline(&line, &len, file);
            sscanf(line, "%hu %hu %hu %hu %hu %hu",
                   &routes[i].id, &routes[i].from, &routes[i].to, 
                   &routes[i].cost, &routes[i].demand, &routes[i].is_depot);
        }

        // Assign routes to the instance
        instance->routes = routes;
    } else {
        instance->has_routes = false;
        instance->num_routes = 0;
        instance->routes = NULL;
    }

    fclose(file);
    if (line)
        free(line);

    return instance;
}
