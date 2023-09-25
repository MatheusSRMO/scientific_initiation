#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../graph/graph.h"


/// @brief Kruskal's algorithm
/// @param graph Graph
/// @param start Start vertex
/// @param tour_size Size of the tour
/// @return uint16_t* DFS
uint16_t* graph_dfs(Graph* graph, int start, int* tour_size);


/// @brief Euler Tour
/// @param graph Graph
/// @param start Start vertex
/// @return int* Euler Tour
int *euler_tour(Graph *graph, int start);

#endif // _ALGORITHMS_H_