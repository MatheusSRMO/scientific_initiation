#include "io_file.h"

Graph* read_file(char* file_name) {
    FILE* file = fopen(file_name, "r");
    if(file == NULL) {
        printf("Error opening file %s\n", file_name);
        exit(1);
    }


    int V, E;
    fscanf(file, "%d %d", &V, &E);

    Graph* graph = graph_construct(V, E, true);

    int i = 0;
    while(i++ < E) {
        int data1, data2;
        fscanf(file, "%d %d", &data1, &data2);
        graph_add_edge(graph, data1, data2 - data1, data2);
    }

    fclose(file);

    return graph;
}

Graph* generate_random_graph(int n, int m) {

    srand(time(NULL));
    // seed the random number generator


    Graph* graph = graph_construct(n, m, true);

    // for(int i = 0; i < n; i++) {
    //     graph_add_vertex(graph, i);
    // }

    for(int i = 0; i < m; i++) {
        int src = rand() % n;
        int dest = rand() % n;
        int weight = rand() % 100;
        graph_add_edge(graph, src, weight, dest);
    }

    return graph;
}

void generate_graphviz_file(Graph* graph, char* file_name) {
    FILE* file = fopen(file_name, "w");
    if(file == NULL) {
        printf("Error opening file %s\n", file_name);
        exit(1);
    }

    fprintf(file, "digraph G {\n");

    fprintf(file, "\tlayout=sfdp\n");

    int V = graph->V;
    

    for(int i = 0; i < V; i++) {
        
        Edge* current = graph->adj[i];
        while(current != NULL) {
            fprintf(file, "\t%d -> %d [label=\"%.2f\"];\n", i, current->target, current->weight);
            current = current->next;
        }
    }

    fprintf(file, "}\n");

    fclose(file);
}
