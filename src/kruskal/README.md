# Kruskal's Algorithm

Este é um módulo C que implementa o algoritmo de Kruskal para encontrar a Árvore Geradora Mínima (Minimum Spanning Tree) em um grafo ponderado não direcionado. O algoritmo de Kruskal é amplamente utilizado em problemas de otimização de redes e grafos.

## Como usar

### Incluir os arquivos de cabeçalho

Você deve incluir os arquivos de cabeçalho necessários em seu projeto.

```c
#include "kruskal.h"
#include "../union_find/union_find.h"
#include "../edge/edge.h"
#include "../graph/graph.h"
```

### Executar Kruskal's Algorithm

Para usar o algoritmo de Kruskal, você precisa passar um array de arestas ordenadas como entrada. O algoritmo retornará a Árvore Geradora Mínima como um array de arestas.

```c
Edge* edges; // Um array de arestas ordenadas
int n;      // O número de arestas
int dimension; // O número de vértices

Edge* minimumSpanningTree = kruskal(edges, n, dimension);
```

### Estrutura de Dados Requerida

Certifique-se de que você já tenha definido a estrutura de dados para representar as arestas e o grafo. O algoritmo de Kruskal depende dessas estruturas para funcionar corretamente.

### Liberação de Memória

Lembre-se de liberar a memória alocada para o array de arestas da Árvore Geradora Mínima quando não precisar mais dele.

```c
free(minimumSpanningTree);
```