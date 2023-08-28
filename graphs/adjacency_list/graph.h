#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../data_structures/vector/vector.h"


typedef struct graph Graph;

typedef struct vertex Vertex;

typedef struct edge Edge;


int vertex_get_data(Vertex* vertex);
Vector* vertex_get_outgoing_edges(Vertex* vertex);
Vector* vertex_get_incoming_edges(Vertex* vertex);
int edge_get_from_vertex(Edge* edge);
int edge_get_to_vertex(Edge* edge);
float edge_get_weight(Edge* edge);

/// @brief  Cria um grafo
/// @return Ponteiro para o grafo criado
Graph* graph_construct();

/// @brief Adiciona um vértice no grafo
/// @param graph Ponteiro para o grafo
/// @param data  Dado a ser inserido
void graph_add_vertex(Graph* graph, int data);


/// @brief Retorna um vértice do grafo
/// @param graph Ponteiro para o grafo
/// @return Ponteiro para o vértice
Vector* graph_get_vertices(Graph* graph);

/// @brief Adiciona uma aresta no grafo
/// @param graph Ponteiro para o grafo
/// @param data1 Dado do vértice de origem
/// @param data2 Dado do vértice de destino
void graph_add_edge(Graph* graph, int data1, int data2);

/// @brief Remove um vértice do grafo
/// @param graph Ponteiro para o grafo
/// @param data  Dado a ser removido
void graph_remove_vertex(Graph* graph, int data);

/// @brief Remove uma aresta do grafo
/// @param graph Ponteiro para o grafo
/// @param data1 Dado do vértice de origem
/// @param data2 Dado do vértice de destino
void graph_remove_edge(Graph* graph, int data1, int data2);

/// @brief Verifica se o grafo está vazio
/// @param graph Ponteiro para o grafo
/// @return true se o grafo estiver vazio, false caso contrário
bool graph_empty(Graph* graph);

/// @brief Retorna o número de vértices e arestas do grafo
/// @param graph Ponteiro para o grafo
/// @return Número de vértices e arestas do grafo
int graph_vertex_count(Graph* graph);

/// @brief Retorna o número de arestas do grafo
/// @param graph Ponteiro para o grafo
/// @return Número de arestas do grafo
int graph_edge_count(Graph* graph);

/// @brief Exibe o grafo na tela
/// @param graph    Ponteiro para o grafo
/// @param print_fn Função para exibir um dado
void graph_print(Graph* graph);

/// @brief Destrói o grafo
/// @param graph Ponteiro para o grafo
void graph_destruct(Graph* graph);

#endif // _GRAPH_H_
