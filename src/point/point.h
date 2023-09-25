#ifndef _POINT_H_
#define _POINT_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Enumeração que representa os tipos de distância disponíveis.
 */
typedef enum {
    eucledian,    /**< Distância euclidiana */
    manhattan,    /**< Distância de Manhattan */
    chebyshev,    /**< Distância de Chebyshev */
    geographical /**< Distância geográfica */
} DistanceType;

/**
 * Estrutura que representa um ponto no plano cartesiano.
 */
typedef struct point Point;

/**
 * Cria um novo ponto.
 *
 * @param id Identificador do ponto.
 * @param x Coordenada x do ponto.
 * @param y Coordenada y do ponto.
 * @return Um ponteiro para o novo ponto criado.
 */
Point* point_create(int id, double x, double y);

/**
 * Libera a memória alocada para um ponto.
 *
 * @param point Ponteiro para o ponto a ser liberado.
 */
void point_destroy(Point* point);

/**
 * Obtém o identificador de um ponto.
 *
 * @param point Ponteiro para o ponto.
 * @return O identificador do ponto.
 */
int point_get_id(Point* point);

/**
 * Obtém a coordenada x de um ponto.
 *
 * @param point Ponteiro para o ponto.
 * @return A coordenada x do ponto.
 */
double point_get_x(Point* point);

/**
 * Obtém a coordenada y de um ponto.
 *
 * @param point Ponteiro para o ponto.
 * @return A coordenada y do ponto.
 */
double point_get_y(Point* point);

/**
 * Calcula a distância entre dois pontos, de acordo com o tipo de distância especificado.
 *
 * @param point1 Ponteiro para o primeiro ponto.
 * @param point2 Ponteiro para o segundo ponto.
 * @param distance_type Tipo de distância a ser calculada.
 * @return A distância entre os pontos.
 */
double point_distance(Point* point1, Point* point2, DistanceType distance_type);

/**
 * Imprime as coordenadas de um ponto.
 *
 * @param point Ponteiro para o ponto a ser impresso.
 */
void point_print(Point* point);

/**
 * Imprime uma lista de pontos.
 *
 * @param point_list Array de ponteiros para os pontos.
 * @param dimension Número de pontos na lista.
 */
void point_print_list(Point** point_list, int dimension);

/**
 * Imprime as distâncias entre os pontos em uma lista, de acordo com o tipo de distância especificado.
 *
 * @param point_list Array de ponteiros para os pontos.
 * @param dimension Número de pontos na lista.
 * @param distance_type Tipo de distância a ser calculada.
 */
void point_print_list_with_distances(Point** point_list, int dimension, DistanceType distance_type);

/**
 * Imprime as distâncias entre os pontos em uma lista em um arquivo, de acordo com o tipo de distância especificado.
 *
 * @param point_list Array de ponteiros para os pontos.
 * @param dimension Número de pontos na lista.
 * @param distance_type Tipo de distância a ser calculada.
 * @param file_name Nome do arquivo de saída.
 */
void point_print_list_with_distances_to_file(Point** point_list, int dimension, DistanceType distance_type, char* file_name);

/**
 * Cria uma lista de pontos.
 *
 * @param dimension Número de pontos na lista.
 * @return Um array de ponteiros para os pontos.
 */
Point** point_list_create(int dimension);


Point* point_list_get_by_id(Point** point_list, int dimension, int id);

/**
 * Libera a memória alocada para uma lista de pontos.
 *
 * @param point_list Array de ponteiros para os pontos.
 * @param dimension Número de pontos na lista.
 */
void point_list_destroy(Point** point_list, int dimension);

/**
 * Imprime uma lista de pontos.
 *
 * @param point_list Array de ponteiros para os pontos.
 * @param dimension Número de pontos na lista.
 */
void point_list_print(Point** point_list, int dimension);

/**
 * Imprime as distâncias entre os pontos em uma lista, de acordo com o tipo de distância especificado.
 *
 * @param point_list Array de ponteiros para os pontos.
 * @param dimension Número de pontos na lista.
 * @param distance_type Tipo de distância a ser calculada.
 */
void point_list_print_with_distances(Point** point_list, int dimension, DistanceType distance_type);

/**
 * Imprime as distâncias entre os pontos em uma lista em um arquivo, de acordo com o tipo de distância especificado.
 *
 * @param point_list Array de ponteiros para os pontos.
 * @param dimension Número de pontos na lista.
 * @param distance_type Tipo de distância a ser calculada.
 * @param file_name Nome do arquivo de saída.
 */
void point_list_print_with_distances_to_file(Point** point_list, int dimension, DistanceType distance_type, char* file_name);

/**
 * Cria uma lista de pontos a partir de um arquivo.
 *
 * @param file_name Nome do arquivo de entrada.
 * @param dimension Número de pontos na lista.
 * @return Um array de ponteiros para os pontos.
 */
Point** point_list_from_file(char* file_name, int dimension);

/**
 * Salva uma lista de pontos em um arquivo.
 *
 * @param point_list Array de ponteiros para os pontos.
 * @param dimension Número de pontos na lista.
 * @param file_name Nome do arquivo de saída.
 */
void point_list_to_file(Point** point_list, int dimension, char* file_name);

/**
 * Salva as distâncias entre os pontos em uma lista em um arquivo, de acordo com o tipo de distância especificado.
 *
 * @param point_list Array de ponteiros para os pontos.
 * @param dimension Número de pontos na lista.
 * @param distance_type Tipo de distância a ser calculada.
 * @param file_name Nome do arquivo de saída.
 */
void point_list_to_file_with_distances(Point** point_list, int dimension, DistanceType distance_type, char* file_name);

/**
 * Salva as distâncias entre os pontos em uma lista em um arquivo, de acordo com o tipo de distância especificado.
 *
 * @param point_list Array de ponteiros para os pontos.
 * @param dimension Número de pontos na lista.
 * @param distance_type Tipo de distância a ser calculada.
 * @param file_name Nome do arquivo de saída.
 */
void point_list_to_file_with_distances_to_file(Point** point_list, int dimension, DistanceType distance_type, char* file_name);

/**
 * Verifica se um ponto está dentro de um raio de cobertura de outro ponto.
 *
 * @param point1 Ponteiro para o primeiro ponto.
 * @param point2 Ponteiro para o segundo ponto.
 * @param distance_type Tipo de distância a ser calculada.
 * @param range Raio de cobertura.
 * @return 1 se o ponto está dentro do raio de cobertura, 0 caso contrário.
 */
int point_in_range(Point* point1, Point* point2, int range, DistanceType distance_type);

#endif // _POINT_H_
