#ifndef DL_LIST_H
#define DL_LIST_H


#include "node.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct dl_list DlList;

/// @brief  Cria uma lista
/// @return Ponteiro para a lista criada
DlList* dl_list_contruct();

/// @brief Adiciona um item no início da lista
/// @param  dl_list Ponteiro para a lista
void dl_list_push_front(DlList* dl_list, data_type data);

/// @brief Adiciona um item no final da lista
/// @param dl_list  Ponteiro para a lista
/// @param data    Dado a ser inserido
void dl_list_push_back(DlList* dl_list, data_type data);

/// @brief Remove o primeiro elemento
/// @param dl_list  Ponteiro para a lista
/// @return Dado removido
data_type dl_list_pop_front(DlList* dl_list);

/// @brief Remove o último elemento
/// @param dl_list  Ponteiro para a lista
/// @return Dado removido
data_type dl_list_pop_back(DlList* dl_list);

/// @brief Exibe a lista na tela
/// @param dl_list   Ponteiro para a lista
/// @param print_fn Função para exibir um dado
void dl_list_print(DlList* dl_list, void (*print_fn)(data_type));

/// @brief Destrói a lista
/// @param dl_list  Ponteiro para a lista
void dl_list_destruct(DlList* dl_list);

#endif // DL_LIST_H