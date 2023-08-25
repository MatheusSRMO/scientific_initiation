#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../data_structures/vector/vector.h"


typedef struct graph Graph;

typedef struct vertex Vertex;

typedef struct edge Edge;

typedef int (*vertex_cmp_fn)(Vertex, Vertex);

typedef void (*vertex_print_fn)(Vertex);

typedef void (*vertex_destruct_fn)(Vertex);

typedef int (*edge_cmp_fn)(Edge, Edge);

typedef void (*edge_print_fn)(Edge, Edge);

typedef void (*edge_destruct_fn)(Edge);



/// @brief  Cria um grafo
/// @return Ponteiro para o grafo criado
Graph* graph_construct(
    vertex_cmp_fn vertex_cmp,
    vertex_print_fn vertex_print,
    vertex_destruct_fn vertex_destruct,
    edge_cmp_fn edge_cmp,
    edge_print_fn edge_print,
    edge_destruct_fn edge_destruct
);

/// @brief Adiciona um vértice no grafo
/// @param graph Ponteiro para o grafo
/// @param data  Dado a ser inserido
void graph_add_vertex(Graph* graph, data_type data);

/// @brief Adiciona uma aresta no grafo
/// @param graph Ponteiro para o grafo
/// @param data1 Dado do vértice de origem
/// @param data2 Dado do vértice de destino
void graph_add_edge(Graph* graph, data_type data1, data_type data2);

/// @brief Remove um vértice do grafo
/// @param graph Ponteiro para o grafo
/// @param data  Dado a ser removido
void graph_remove_vertex(Graph* graph, data_type data);

/// @brief Remove uma aresta do grafo
/// @param graph Ponteiro para o grafo
/// @param data1 Dado do vértice de origem
/// @param data2 Dado do vértice de destino
void graph_remove_edge(Graph* graph, data_type data1, data_type data2);

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
void graph_print(Graph* graph, void (*print_fn)(data_type));

/// @brief Destrói o grafo
/// @param graph Ponteiro para o grafo
void graph_destruct(Graph* graph);

#endif // _GRAPH_H_