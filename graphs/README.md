
# Graph Library

Esta é uma biblioteca simples para manipulação de grafos utilizando tanto listas de adjacências quanto matriz de adjacências.

## Estruturas de Dados

- `Vector`: Estrutura de dados que representa um vetor dinâmico.
- `Matrix`: Estrutura de dados que representa uma matriz esparsa.
- `Graph`: Estrutura de dados principal que representa um grafo.
- `Vertex`: Estrutura que representa um vértice no grafo.
- `Edge`: Estrutura que representa uma aresta entre vértices no grafo.

## Funções

- `Graph* graph_construct()`: Cria um novo grafo vazio e retorna um ponteiro para ele.

- `void graph_add_vertex(Graph* graph, int data)`: Adiciona um vértice com o dado fornecido ao grafo.

- `void graph_add_edge(Graph* graph, int data1, int data2)`: Adiciona uma aresta entre dois vértices com os dados fornecidos ao grafo.

- `void graph_remove_vertex(Graph* graph, int data)`: Remove um vértice com o dado fornecido do grafo, juntamente com todas as suas arestas.

- `void graph_remove_edge(Graph* graph, int data1, int data2)`: Remove uma aresta entre os vértices com os dados fornecidos do grafo.

- `bool graph_empty(Graph* graph)`: Verifica se o grafo está vazio.

- `int graph_vertex_count(Graph* graph)`: Retorna o número total de vértices no grafo.

- `int graph_edge_count(Graph* graph)`: Retorna o número total de arestas no grafo.

- `void graph_print(Graph* graph)`: Exibe o grafo na saída padrão.

- `void graph_destruct(Graph* graph)`: Libera a memória alocada para o grafo e seus componentes.

## Exemplo de Uso

Aqui está um exemplo de uso da biblioteca para criar um grafo, adicionar vértices e arestas, imprimir o grafo e, finalmente, destruir o grafo:

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

int main() {
    Graph* graph = graph_construct();

    graph_add_vertex(graph, 1);
    graph_add_vertex(graph, 2);
    graph_add_vertex(graph, 3);

    graph_add_edge(graph, 1, 2);
    graph_add_edge(graph, 1, 3);
    graph_add_edge(graph, 2, 3);

    graph_print(graph);

    graph_destruct(graph);

    return 0;
}
```

## Compilação

Para compilar o exemplo acima, você pode usar um comando como o seguinte:

Lista de adjacências:
```bash
make adjacency_list
```

Matriz de adjacências:
```bash
make adjacency_matrix
```

Certifique-se de que os arquivos de cabeçalho e implementação estejam no mesmo diretório ou devidamente especificados no comando de compilação.

## Autor

Matheus Souza Ribeiro

