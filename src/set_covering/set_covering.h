/**
    Modelando o problema para que cada esquina (vértice) cubra todas as residencias (pontos de interesse)

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
 **/

#ifndef _SET_COVERING_H_
#define _SET_COVERING_H_

#include "../graph/graph.h"
#include "../point/point.h"

typedef struct set_covering SetCovering;

/**
 * Cria uma nova instância do problema de cobertura de conjunto.
 *
 * @param n Número de esquinas.
 * @param m Número de pontos de interesse.
 * @param r Raio de cobertura.
 * @param locations Ponteiro para o vetor de pontos de coleta.
 * @param points Ponteiro para o vetor de pontos de interesse.
 * @param distance_type Tipo de distância.
 * @return Um ponteiro para a nova instância do problema de cobertura de conjunto.
 */
SetCovering* set_covering_create(int n, int m, int r, Point **locations, Point **points, DistanceType distance_type);

/**
 * Resolve uma instância do problema de cobertura de conjunto.
 * 
 * @param set_covering Ponteiro para a instância do problema de cobertura de conjunto.
 */
void set_covering_solve(SetCovering *set_covering);

/**
 * Libera a memória alocada para uma instância do problema de cobertura de conjunto.
 *
 * @param set_covering Ponteiro para a instância do problema de cobertura de conjunto.
 */
void set_covering_destroy(SetCovering *set_covering);

/**
 * Obtém o número de esquinas de uma instância do problema de cobertura de conjunto.
 *
 * @param set_covering Ponteiro para a instância do problema de cobertura de conjunto.
 * @return O número de esquinas.
 */
int set_covering_get_n(SetCovering *set_covering);

/**
 * Obtém o número de pontos de interesse de uma instância do problema de cobertura de conjunto.
 *
 * @param set_covering Ponteiro para a instância do problema de cobertura de conjunto.
 * @return O número de pontos de interesse.
 */
int set_covering_get_m(SetCovering *set_covering);

/**
 * Obtém o raio de cobertura de uma instância do problema de cobertura de conjunto.
 *
 * @param set_covering Ponteiro para a instância do problema de cobertura de conjunto.
 * @return O raio de cobertura.
 */
int set_covering_get_r(SetCovering *set_covering);

/**
 * Obtém o grafo de uma instância do problema de cobertura de conjunto.
 *
 * @param set_covering Ponteiro para a instância do problema de cobertura de conjunto.
 * @return O grafo.
 */
Graph* set_covering_get_graph(SetCovering *set_covering);

/**
 * Obtém o vetor de pontos de interesse de uma instância do problema de cobertura de conjunto.
 *
 * @param set_covering Ponteiro para a instância do problema de cobertura de conjunto.
 * @return O vetor de pontos de interesse.
 */
Point** set_covering_get_points(SetCovering *set_covering);

/**
 * Obtém a solução de uma instância do problema de cobertura de conjunto.
 *
 * @param set_covering Ponteiro para a instância do problema de cobertura de conjunto.
 * @return O vetor de esquinas que cobrem todos os pontos de interesse.
 */
int* set_covering_get_solution(SetCovering *set_covering);

/**
 * Obtém o tamanho da solução de uma instância do problema de cobertura de conjunto.
 *
 * @param set_covering Ponteiro para a instância do problema de cobertura de conjunto.
 * @return O tamanho da solução.
 */
int set_covering_get_solution_size(SetCovering *set_covering);

/**
 * Define a solução de uma instância do problema de cobertura de conjunto.
 *
 * @param set_covering Ponteiro para a instância do problema de cobertura de conjunto.
 */
void set_covering_set_solution(SetCovering *set_covering);

/**
 * Verifica se uma esquina cobre um ponto de interesse.
 *
 * @param set_covering Ponteiro para a instância do problema de cobertura de conjunto.
 * @param i Índice da esquina.
 * @param j Índice do ponto de interesse.
 * @return 1 se a esquina cobre o ponto de interesse e 0 caso contrário.
 */
int set_covering_covers(SetCovering *set_covering, int i, int j);




#endif // _SET_COVERING_H_
