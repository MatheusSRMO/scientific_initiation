#include "io_file.h"

Graph* read_file(char* file_name) {
    FILE* file = fopen(file_name, "r");
    if(file == NULL) {
        printf("Error opening file %s\n", file_name);
        exit(1);
    }

    Graph* graph = graph_construct();

    int V, E;
    fscanf(file, "%d %d", &V, &E);

    int i = 0;
    while(i++ < E) {
        int data1, data2;
        fscanf(file, "%d %d", &data1, &data2);
        graph_add_vertex(graph, data1);
        graph_add_vertex(graph, data2);
        graph_add_edge(graph, data1, data2);
    }

    fclose(file);

    return graph;
}

Graph* generate_random_graph(int n, int m) {

    srand(time(NULL));
    // seed the random number generator


    Graph* graph = graph_construct();

    for(int i = 0; i < n; i++) {
        graph_add_vertex(graph, i);
    }

    for(int i = 0; i < m; i++) {
        int data1 = rand() % n;
        int data2 = rand() % n;
        graph_add_edge(graph, data1, data2);
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

    int V = graph_vertex_count(graph);
    Vector *vertices = graph_get_vertices(graph);
    

    for(int i = 0; i < V; i++) {
        
        Vertex* vertex = vector_get(vertices, i);

        Vector* outgoing_edges = vertex_get_outgoing_edges(vertex);

        for(int j = 0; j < vector_size(outgoing_edges); j++) {
            Edge* edge = vector_get(outgoing_edges, j);

            int to = edge_get_to_vertex(edge);
            
            fprintf(file, "\t%d -> %d;\n", vertex_get_data(vertex), to);
        }
    }

    fprintf(file, "}\n");

    fclose(file);
}
