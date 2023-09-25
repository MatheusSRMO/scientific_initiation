# Algorithms Library

Este é um módulo C que implementa várias funções relacionadas a algoritmos em grafos. Ele fornece funcionalidades para executar algoritmos como Kruskal's Algorithm, Depth-First Search (DFS), e Euler Tour em um grafo.

## Como usar

### Incluir o arquivo de cabeçalho

Você deve incluir o arquivo de cabeçalho necessário em seu projeto.

```c
#include "algorithms.h"
```

### Kruskal's Algorithm

O algoritmo de Kruskal é usado para encontrar a Árvore Geradora Mínima (Minimum Spanning Tree) em um grafo ponderado não direcionado. Você pode usar a função `graph_dfs` para executar o algoritmo de Kruskal.

```c
Graph* graph; // Seu grafo
int startVertex = 0; // Vértice de início
int tourSize;
uint16_t* dfsTour = graph_dfs(graph, startVertex, &tourSize);
```

### Depth-First Search (DFS)

O Depth-First Search é um algoritmo de busca em grafos que é útil para explorar os vértices e arestas de um grafo. Você pode usar a função `depth_first_search` para executar o DFS em uma Árvore Geradora Mínima (MST) ou em qualquer grafo.

```c
Edge* minimumSpanningTree; // Sua Árvore Geradora Mínima (MST)
int mstSize; // Tamanho da MST
Edge* dfsResult = depth_first_search(minimumSpanningTree, mstSize);
```

### Euler Tour

O Euler Tour é um ciclo que passa por todas as arestas de um grafo exatamente uma vez. Você pode usar a função `euler_tour` para encontrar o Euler Tour em um grafo.

```c
Graph* graph; // Seu grafo
int startVertex = 0; // Vértice de início
int* eulerTour = euler_tour(graph, startVertex);
```

### Liberação de Memória

Certifique-se de liberar a memória alocada para os resultados quando não precisar mais deles.

```c
free(dfsTour);
free(dfsResult);
free(eulerTour);
```