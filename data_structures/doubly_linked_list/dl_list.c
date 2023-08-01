#include "dl_list.h"


struct dl_list {
    int size;
    Node* head;
    Node* rear;
};


DlList* dl_list_contruct() {
    DlList* dl_list = malloc(sizeof(DlList));

    dl_list->size = 0;
    dl_list->head = NULL;
    dl_list->rear = NULL;

    return dl_list;
}

void dl_list_push_front(DlList* dl_list, data_type data) {
    // cria um novo nó
    Node* node = node_construct(data, dl_list->head, NULL);
    
    if(dl_list->head == NULL) {
        // Caso a lista esteja vazia, os nós head e rear devem receber os mesmos, pois ele será o primeiro
        dl_list->head = dl_list->rear = node;
    }
    else {
        // Se já tiver um elemento, atualiza o 'prev' do nó head atual e depois atualiza o 'head' para o novo nó (lembrando que atrinuições ocorrem da direita para esquerda)
        dl_list->head = dl_list->head->prev = node;
    }
    // Atualiza o tamanho da dl_list
    dl_list->size++;
}

void dl_list_push_back(DlList* dl_list, data_type data) {
    // Cria um novo nó
    Node* node = node_construct(data, NULL, dl_list->rear);

    if(dl_list->rear == NULL) {
        // Caso a lista esteja vazia, os nós head e rear devem receber os mesmos, pois ele será o primeiro
        dl_list->head = dl_list->rear = node;
    }
    else {
        // se já tiver um elemento, primeiro atualiza o 'next' do rear atual e depois muda o rear para o novo nó (lembrando que atrinuições ocorrem da direita para esquerda)
        dl_list->rear = dl_list->rear->next = node;
    }
    // Atualiza o tamanho da dl_list
    dl_list->size++;
}

data_type dl_list_pop_front(DlList* dl_list) {
    // Verifica se existe um head, se não existir, a lista esta vazia, e não é possivel remover um elemento de uma lista vazia
    if(dl_list->head == NULL) {
        exit(printf("Error: list is empty!\n"));
    }
    // Guarda 'head' atual para ser destruido depois
    Node* node = dl_list->head;
    // Guarda 'data' para ser retornado ao final da função
    data_type data = node->data;

    // atualiza 'head' para o proximo elemento
    dl_list->head = dl_list->head->next;
    if(dl_list->head != NULL) {
        // Caso o novo 'head' exista, atualiza o prev dele para nulo, pois agora ele é o primeiro
        dl_list->head->prev = NULL;
    }

    // Destroi o 'head' antigo
    node_destroy(node);
    // Atualiza o tamanho do dl_list
    dl_list->size--;

    // Verifica se o tamanho é menor ou igual a 1
    if(dl_list->size <= 1) {
        // Caso seja, 'head' e 'rear' devem ser iguais
        dl_list->rear = dl_list->head;
    }

    // retorna o valor do nó removido
    return data;
}

data_type dl_list_pop_back(DlList* dl_list) {
    // Verifica se exite um 'rear', se não existir, a lista está vazia, e retorna um erro, pois não é possível retirar um elemento de uma lista vazia
    if(dl_list->rear == NULL) {
        exit(printf("Error: list is empty!\n"));
    }
    // Guarda o 'rear' para ser removido posteriormente 
    Node* node = dl_list->rear;
    // Guarda o 'data' do atual ultimo nó
    data_type data = node->data;

    // Atualiza o 'rear'
    dl_list->rear = dl_list->rear->prev;
    if(dl_list->rear != NULL) {
        // Se o novo 'rear' existir, atualiza o 'next' dele
        dl_list->rear->next = NULL;
    }

    // Destroi o 'rear' anterior
    node_destroy(node);
    // Atualiza o tamanho do dl_list
    dl_list->size--;

    // Verifica se o tamanho é menor ou igual a 1
    if(dl_list->size <= 1) {
        // Caso seja, 'head' e 'rear' devem ser iguais
        dl_list->head = dl_list->rear;
    }

    // retorna o valor do nó removido
    return data;
}

void dl_list_print(DlList* dl_list, void (*print_fn)(data_type)) {
    printf("[");
    Node* node = dl_list->head;
    while(node != NULL) {
        node_print(node, print_fn);
        if(node->next != NULL) {
            printf(", ");
        }
        node = node->next;
    }
    printf("]\n");
}

void dl_list_destruct(DlList* dl_list) {
    Node* node = dl_list->head;
    while(node != NULL) {
        Node* next = node->next;
        node_destroy(node);
        node = next;
    }
    free(dl_list);
}
