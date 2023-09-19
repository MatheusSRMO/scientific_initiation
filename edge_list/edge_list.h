#ifndef _EDGE_LIST_H_
#define _EDGE_LIST_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct edge_list EdgeList;

/// @brief EdgeList constructor
/// @param size 
/// @return EdgeList pointer
EdgeList *edge_list_create(int size);

/// @brief Get the size of the list
/// @param edge_list 
/// @return size of the list
int edge_list_get_size(EdgeList *edge_list);

/// @brief  Add an edge to the list
/// @param edge_list pointer to the list
/// @param v id of the first vertex
/// @param w id of the second vertex
/// @param weight weight of the edge
void edge_list_add(EdgeList *edge_list, unsigned short int v, unsigned short int w, float weight);

/// @brief Get the id of the first vertex of the edge at index
/// @param edge_list pointer to the list
/// @param index index of the edge
/// @return id of the first vertex of the edge at index
unsigned short int edge_list_get_v(EdgeList *edge_list, int index);

/// @brief Get the id of the second vertex of the edge at index
/// @param edge_list pointer to the list
/// @param index index of the edge
/// @return id of the second vertex of the edge at index
unsigned short int edge_list_get_w(EdgeList *edge_list, int index);

/// @brief Get the ids of the edge at index
/// @param edge_list pointer to the list
/// @param index index of the edge
/// @param v pointer to the id of the first vertex of the edge at index
/// @param w pointer to the id of the second vertex of the edge at index
void edge_list_get_vw(EdgeList *edge_list, int index, unsigned short int *v, unsigned short int *w);

/// @brief Get the weight of the edge at index
/// @param edge_list pointer to the list
/// @param index index of the edge
/// @return weight of the edge at index
float edge_list_get_weight(EdgeList *edge_list, int index);

/// @brief Sort the list by weight
/// @param edge_list pointer to the list
void edge_list_sort(EdgeList *edge_list);

/// @brief Print the list
/// @param edge_list pointer to the list
void edge_list_print(EdgeList *edge_list);

/// @brief Destroy the list
/// @param edge_list pointer to the list
void edge_list_destroy(EdgeList *edge_list);

#endif // _EDGE_LIST_H_