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
Ou seja, para nosso problema, dado um conjunto de esquinas e um conjunto de pontos de interesse, o problema do particionamento de conjuntos consiste em encontrar k subconjuntos de esquinas que cubram todos os pontos de interesse.

## Problema de empacotamento de conjuntos
Definição: Dado um conjunto de elementos U e um inteiro k, o problema de empacotamento de conjuntos consiste em encontrar k subconjuntos de U cuja interseção é vazia.
Ou seja, para nosso problema, dado um conjunto de esquinas e um conjunto de pontos de interesse, o problema de empacotamento de conjuntos consiste em encontrar k subconjuntos de esquinas que cubram todos os pontos de interesse.

## Problema de cobertura de vértices
Definição: Dado um grafo G = (V, E), o problema de cobertura de vértices consiste em encontrar o menor subconjunto de V cuja união é igual a E.

## Problema de empacotamento de vértices
Definição: Dado um grafo G = (V, E), o problema de empacotamento de vértices consiste em encontrar o maior subconjunto de V cuja interseção é vazia.

## Modelando o problema para que cada esquina (vértice) cubra todas as residencias (pontos de interesse)

### Entrada
- Grafo G = (V, E) // V = {v1, v2, ..., vn} e E = {e1, e2, ..., em} V = Esquinas e E = Ruas
- Conjunto de pontos de interesse P = {p1, p2, ..., pk} // P = {p1, p2, ..., pk} P = Pontos de interesse
- Int r // r = 1, 2, ..., r r = Raio de cobertura de cada esquina

### Saída
- Conjunto de esquinas C = {c1, c2, ..., cl} // C = {c1, c2, ..., cl} C = Esquinas que cobrem todos os pontos de interesse

### Restrições
- Cada esquina só pode cobrir pontos de interesse que estejam a uma distância r

### Função objetivo
- Minimizar o número de esquinas que cubram todos os pontos de interesse

### Variáveis de decisão
- Variável binária xij = 1 se a esquina i cobre o ponto de interesse j e 0 caso contrário

### Modelo matemático
- Minimizar a função objetivo
- Sujeito a:
    - Somatório de xij = 1 para todo j = 1, 2, ..., k
    - Somatório de xij <= 1 para todo i = 1, 2, ..., l
    - xij = 0 se a distância entre a esquina i e o ponto de interesse j for maior que r
    - xij = 1 se a distância entre a esquina i e o ponto de interesse j for menor ou igual a r


Seja Sj o subconjunto de esquinas que cobrem o ponto de interesse j, então: Sj = {i | xij = 1}

## Modelando o problema para que cada esquina (vértice) cubra todas as residencias (pontos de interesse) e cada esquina tenha um custo de instalação

### Entrada
- Grafo G = (V, E) // V = {v1, v2, ..., vn} e E = {e1, e2, ..., em} V = Esquinas e E = Ruas
- Conjunto de pontos de interesse P = {p1, p2, ..., pk} // P = {p1, p2, ..., pk} P = Pontos de interesse
- Int r // r = 1, 2, ..., r r = Raio de cobertura de cada esquina
- Int c // c = 1, 2, ..., c c = Custo de instalação de cada esquina

### Saída
- Conjunto de esquinas C = {c1, c2, ..., cl} // C = {c1, c2, ..., cl} C = Esquinas que cubram todos os pontos de interesse

### Restrições
- Cada esquina só pode cobrir pontos de interesse que estejam a uma distância r

### Função objetivo
- Minimizar o custo total de instalação das esquinas que cubram todos os pontos de interesse

### Variáveis de decisão
- Variável binária xij = 1 se a esquina i cobre o ponto de interesse j e 0 caso contrário

### Modelo matemático
- Minimizar a função objetivo
- Sujeito a:
    - Somatório de xij = 1 para todo j = 1, 2, ..., k
    - Somatório de xij <= 1 para todo i = 1, 2, ..., l
    - xij = 0 se a distância entre a esquina i e o ponto de interesse j for maior que r
    - xij = 1 se a distância entre a esquina i e o ponto de interesse j for menor ou igual a r

0 1 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0
2
13
23
