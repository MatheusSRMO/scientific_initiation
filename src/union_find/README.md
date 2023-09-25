
# UF - Union-Find

Este é um módulo C simples para a estrutura de dados Union-Find (também conhecida como Disjoint-Set Union) implementada em linguagem C. A estrutura de dados Union-Find é usada para resolver problemas de conectividade em grafos e conjuntos disjuntos.

## Como usar

### Incluir o arquivo de cabeçalho

```c
#include "uf.h"
```

### Inicialização

Para começar a usar a estrutura Union-Find, primeiro você precisa inicializá-la com o número de vértices que você deseja.

```c
uint16_t N = 10; // Número de vértices
UF* uf = UF_init(N);
```

### Verificar a Conectividade

Você pode verificar se dois vértices estão conectados usando a função `UF_connected`.

```c
uint16_t p = 2;
uint16_t q = 5;
if (UF_connected(uf, p, q)) {
    printf("Os vértices %d e %d estão conectados.\n", p, q);
} else {
    printf("Os vértices %d e %d não estão conectados.\n", p, q);
}
```

### Unir Conjuntos

Para unir dois conjuntos, use a função `UF_union`.

```c
uint16_t p = 2;
uint16_t q = 5;
UF_union(uf, p, q);
```

### Encontrar o Root

Você pode encontrar o representante (raiz) de um conjunto usando a função `UF_find`.

```c
uint16_t vertex = 2;
uint16_t root = UF_find(uf, vertex);
printf("A raiz do conjunto que contém o vértice %d é %d.\n", vertex, root);
```

### Liberar Memória

Certifique-se de liberar a memória alocada quando não precisar mais da estrutura Union-Find.

```c
UF_free(uf);
```
