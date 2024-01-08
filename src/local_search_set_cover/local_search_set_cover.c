#include "local_search_set_cover.h"

typedef struct {
    int size;
    int capacity;
    int **tabu;
} TabuList;

TabuList *tabu_list_create(int n) {
    TabuList *tabu_list = (TabuList *)malloc(sizeof(TabuList));
    tabu_list->size = 0;
    tabu_list->capacity = n;
    tabu_list->tabu = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) {
        tabu_list->tabu[i] = calloc(n, sizeof(int));
    }
    return tabu_list;
}

void tabu_list_destroy(TabuList *tabu_list) {
    for(int i = 0; i < tabu_list->capacity; i++) {
        free(tabu_list->tabu[i]);
    }
    free(tabu_list->tabu);
    free(tabu_list);
}

void tabu_list_add(TabuList *tabu_list, int *X) {
    // add circularly
    if(tabu_list->size == tabu_list->capacity) {
        tabu_list->size = 0;
    }
    memcpy(tabu_list->tabu[tabu_list->size++], X, tabu_list->capacity * sizeof(int));

}

bool tabu_list_contains(TabuList *tabu_list, int *X) {
    for (int i = 0; i < tabu_list->size; i++) {
        if (memcmp(tabu_list->tabu[i], X, tabu_list->capacity * sizeof(int)) == 0) {
            return true;
        }
    }
    return false;
}



int get_cost(int *X, int m) {
    int cost = 0;
    for(int i = 0; i < m; i++) {
        cost += X[i];
    }
    return cost;
}

int number_of_uncovered_elements(int **A, int *S, int m, int n) {
    int cont = 0;
    for(int i = 0; i < m; i++) {
        int sum = 0;
        for(int j = 0; j < n; j++) {
            sum += A[i][j] * S[j];
        }
        if(sum == 0) cont++;
    }
    return cont;
}

int fitness(int **A, int *S, int m, int n) { // Fitness = NrOfUncoveredElements + |C|
    return get_cost(S, n) + number_of_uncovered_elements(A, S, m, n);
}

bool all_elements_covered(int **A, int *S, int m, int n) {
    return number_of_uncovered_elements(A, S, m, n) == 0;
}

bool is_feasible(int **A, int *S, int m, int n) {
    return all_elements_covered(A, S, m, n);
}

int **get_neighbors(int *S, int n) {
    int **neighbors = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) {
        neighbors[i] = (int *)malloc(n * sizeof(int));
        memcpy(neighbors[i], S, n * sizeof(int));
    }
    for(int i = 0; i < n; i++) {
        neighbors[i][i] = 1 - neighbors[i][i];
    }
    return neighbors;
}

int *get_best_neighbor(int **A, int *S, int m, int n, TabuList *tabu_list) {
    
}

/*
 def run(self):
    self.best_legal_solution = self.X.copy()
    best_neighbor = self.get_best_neighbor(self.X)
    i = 0
    while i < 1e2*3:
        best_neighbor = self.get_best_neighbor(best_neighbor)
        print("fitness: ", self.fitness(best_neighbor), i)
        if self.fitness(best_neighbor) < self.fitness(self.best_legal_solution) and self.is_feasible(best_neighbor):
            i = 0
            self.best_legal_solution = best_neighbor.copy()
            continue
        i+=1

    return self.best_legal_solution 
*/
int *local_search(int **A, int *X, int m, int n) {
    srand(time(NULL));
    int *best_legal_solution = (int *)malloc(n * sizeof(int));
    memcpy(best_legal_solution, X, n * sizeof(int));

    TabuList *tabu_list = tabu_list_create(n);

    int *best_neighbor = get_best_neighbor(A, X, m, n, tabu_list);
    int i = 0;
    while(i < 1e3*3) {
        best_neighbor = get_best_neighbor(A, best_neighbor, m, n, tabu_list);
        printf("fitness: %d, i: %d\n", fitness(A, best_neighbor, m, n), i);
        if(fitness(A, best_neighbor, m, n) < fitness(A, best_legal_solution, m, n) && is_feasible(A, best_neighbor, m, n)) {
            i = 0;
            memcpy(best_legal_solution, best_neighbor, n * sizeof(int));
            continue;
        }
        i++;
    }
    free(best_neighbor);
    tabu_list_destroy(tabu_list);
    return best_legal_solution;
}


int* local_search_set_cover(int **A, int m, int n) {
    // int *current_solution = greedy_set_cover(A, m, n);
    int *current_solution = calloc(n, sizeof(int));

    int *X = local_search(A, current_solution, m, n);
    return X;
}