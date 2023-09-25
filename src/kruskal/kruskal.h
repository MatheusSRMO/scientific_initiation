#ifndef _KRUSKAL_H_
#define _KRUSKAL_H_

#include "../union_find/union_find.h"
#include "../edge_list/edge_list.h"
#include "../graph/graph.h"


/// @brief Kruskal's algorithm
/// @param edges sorted edges
/// @param n number of edges
/// @param dimension number of vertices
/// @return Edge* Minimum Spanning Tree
EdgeList* kruskal(EdgeList* edges, int n);


#endif // _KRUSKAL_H_