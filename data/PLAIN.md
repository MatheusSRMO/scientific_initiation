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
Ref: http://www.mat.uc.pt/~jsoares/teaching/oc/1112/RelatorioOC.pdf

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
Pesquisa Local Iterada (ILS), Recozimento Simulado (SA) e Pesquisa de Vizinhança Variável (VNS); e dois algoritmos baseados em população: Algoritmo Genético (GA) e Otimização por Enxame de Partículas (PSO).

https://pdf.sciencedirectassets.com/271697/1-s2.0-S0167637700X00697/1-s2.0-0167637789900023/main.pdf?X-Amz-Security-Token=IQoJb3JpZ2luX2VjELz%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLWVhc3QtMSJHMEUCIQDUPP4Urhd3pUB8H7cgfeVudO83aCLf47wb9EwaquechgIgAIMm1Lu4Qf702hcEtYpUFN0Oxq47IHow9Y%2FTTtnHVWgquwUIxP%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FARAFGgwwNTkwMDM1NDY4NjUiDAX21usWC9%2B4e0mq6CqPBRq%2FDoPb7qJ2nZQj4SFA4O8SzFDDq0Um144NmTiT454304rFDf1uS42BGYWbyOrr1gTT2jxa5YnChcLE0nOw2pFVQn6dG%2Bgv0L30%2B9pI0OLHwjnwLt%2FTNeSeUXBFzidNDjz%2FFQKPsWtdKd2Qjnv45Ci7huqVTmpOiZ40ILbpNZHI64mF1DWEQaVKr1J070lC13QpCwRGmJasTuOQrz6wk%2FmK2nYwKuQUqMd8qOpxhmXu6iOf0WZY8rSyzkmDI0j2%2FOY24rB4wfdDyInwGA37pqeG%2FVnjHS9OxCf0Sn8WbY8H8vaOwnIqGjrtQJwMSc3jHaWjjK4L8hqsqGNFpr4%2F8R1cVLHLUxf3Jp%2BqAt2WTwbCdEDP2l8u07EKrxigHVYdwFjV7lRMWhwofbCG6bFRy8xd%2BZXYyJ%2BI0VCEIUun8y%2BwHFcDdZTgRHJmdgehd7ttxgahaCe4Q%2BxjCyWaVRsvuNE1UWCc4fdRNrEE1cO%2FioAPM9FRfjn5Hehl1uNzX63W0dvReMHD9krgvjJvhiZMcG6sokuOIQ3tkm6sDQnFkbKTJwhPhXdR%2F7g4AQerV0PqIx8N%2FCySXdY0lzkTYwTf4cxxxmcpYEMdAeIBTzsU1wObe%2F7S1LuqhfWZAFoxxAz0wUj%2BmtvNA15NrRUZz88%2B1aBtmzVU%2FUzt4XQitN%2BLtJHYCazEKiF2u5vUJdTntPX1urdurE95I0ME8YRbbP3hCL%2BFNLt9f1YuljSzcC5hOLQ37jF9n1IE81%2BfEQlrp3mZ1y8Oogfc27oTctlWSXsUiUG4wEX2tyMue690XPapT78RztyqnHLg0aDCn2qoVK%2BvuUIdTwwml0H1wG2iwENRGbTLADgeQHDW0ICt13vPx3QwsJ2RqQY6sQE%2BaRC2MTvGM26ZL6aPL6%2Bc%2BFIXfQfkEZxN0b%2F%2BRqby8YNGlabkGeab8CJg2oKU2JhgnRN7HLUJcv6bGY%2FHE57O7hRp7MJKKyWfqmm4Nq9bZiT2B%2BXIe3b3qQDNDRIbk%2FXPUC63FQsMsliLaq9O5iEKg4FP5tk41p7nPbTbvn7V4R%2BuIVFAo6VOMJQOcBGZnrFkGCHIs1WEO3EBTmKp%2F2MJGSahwOl8YprX4Wjj5itTUoM%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20231009T203004Z&X-Amz-SignedHeaders=host&X-Amz-Expires=300&X-Amz-Credential=ASIAQ3PHCVTYQR5XHJGB%2F20231009%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=816c58f7a3f2a9511200fab3db14ce4439c21e55da5da571fe5cf19b10313f33&hash=47195b5a8952d4bdb39568cb266d7f535a745dc378dab3f1e98da39193b94abe&host=68042c943591013ac2b2430a89b270f6af2c76d8dfd086a07176afe7c76c2c61&pii=0167637789900023&tid=spdf-75f8e1f9-c733-48d1-805b-656a25bb542b&sid=8e5ec53b5d05c5483079c48830ed5df48a34gxrqa&type=client&tsoh=d3d3LnNjaWVuY2VkaXJlY3QuY29t&ua=041156565559565654&rr=8139611d3eaa26a1&cc=br

https://www.cs.ucr.edu/~neal/Young08SetCover.pdf

35.3 Capitulo do Kormen
