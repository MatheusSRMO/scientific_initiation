1 - [x] - Estrutura que armazene os arquivos de entrada para a cvrplib (arquivos .vrp)
2 - [x] - Função que leia os arquivos de entrada e armazene os dados em uma estrutura (arquivos .vrp)
3 - [x] - Estrutura que armazene os arquivos de entrada para minha instância (arquivos .scp)
4 - [x] - Função que leia os arquivos de entrada e armazene os dados em uma estrutura (arquivos .scp)
5 - [x] - Fazer uma representação de grafos (não direcionado) com lista de adjacência
6 - [x] - Fazer uma representação de grafos (não direcionado) com matriz de adjacência
7 - [x] - MST com krustal
8 - [x] - tour com Euler
9 - [] - plotar o grafo em diferentes estados no caminhamento (MST, tour, etc) com graphviz
10 - [] - Escrever uma função que leia um arquivo de entrada e retorne uma lista de pontos de interesse e de coleta

## Problema de Cobertura de Conjuntos
Definição: Dado um conjunto de elementos U e um conjunto S de subconjuntos de U, o problema de cobertura de conjuntos consiste em encontrar o menor subconjunto de S cuja união é igual a U.
Ou seja, para nosso problema, dado um conjunto de esquinas e um conjunto de pontos de interesse, o problema de cobertura de conjuntos consiste em encontrar o menor subconjunto de esquinas que cubra todos os pontos de interesse.

## Problema do Particionamento de Conjuntos
Definição: Dado um conjunto de elementos U e um inteiro k, o problema do particionamento de conjuntos consiste em encontrar k subconjuntos de U cuja união é igual a U.
Ou seja, para nosso problema, dado um conjunto de residencias e um inteiro k, o problema de particionamento de conjustos consiste em encontrar k esquinas que cubram todas as residências.

## Problema de empacotamento de conjuntos
Definição: Dado um conjunto de elementos U e um inteiro k, o problema de empacotamento de conjuntos consiste em encontrar k subconjuntos de U cuja interseção é vazia.
ou seja, para nosso problema, dado um conjunto de residencias e um inteiro k, o problema do empacotamento de conjuntos consiste em encontrar k esquinas de forma que duas esquinas não cubram a mesma residencia.

## Problema de cobertura de vértices
Definição: Dado um grafo G = (V, E), o problema de cobertura de vértices consiste em encontrar o menor subconjunto de V cuja união é igual a E.

## Problema de empacotamento de vértices
Definição: Dado um grafo G = (V, E), o problema de empacotamento de vértices consiste em encontrar o maior subconjunto de V cuja interseção é vazia.

## Modelando o problema para que cada esquina (vértice) cubra todas as residencias (pontos de interesse)

*Entrada:*
- Grafo G = (V, E) onde V = {v1, v2, ..., vn} e E = {e1, e2, ..., em}. V representa as esquinas e E representa as ruas.
- Conjunto de pontos de interesse P = {p1, p2, ..., pk} onde P representa os pontos de interesse.
- Inteiro r ≥ 0 onde r é o raio de cobertura de cada esquina.

*Saída:*
- Conjunto de esquinas C = {c1, c2, ..., cl} onde C representa as esquinas que cobrem todos os pontos de interesse.

*Restrições:*
1. A soma de Xij para todo i de 1 a l deve ser maior ou igual a 1 para todo j de 1 a k.
   - Cada ponto de interesse deve ser coberto por no mínimo uma esquina.

2. Xij = 0 se a distância entre a esquina i e o ponto de interesse j for maior que r.

3. Xij = 1 se a distância entre a esquina i e o ponto de interesse j for menor ou igual a r.

*Função Objetivo:*
Minimizar o número de esquinas que cubram todos os pontos de interesse.

*Variáveis de Decisão:*
Variável binária Xij é igual a 1 se a esquina i cobre o ponto de interesse j e 0 caso contrário.

Solução: 0 1 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0

Vértices = {2, 13, 23}
