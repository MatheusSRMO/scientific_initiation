#ifndef _READ_FILE_H_
#define _READ_FILE_H_


#include "../adjacency_list/graph.h"
#include <time.h>


// Read a graph from a file
// @param filename: the name of the file
// @return: the graph
Graph* read_file(char* file_name);

/// @brief Generate a random graph
/// @param n The number of vertices
/// @param m The number of edges
/// @return Graph*
Graph* generate_random_graph(int n, int m);

/// @brief Generate a graphviz file
/// @param graph  The graph
/// @param file_name  The name of the file
void generate_graphviz_file(Graph* graph, char* file_name);


#endif  // _READ_FILE_H_