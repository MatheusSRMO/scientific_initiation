#include "local_search_set_cover.h"

void print_vector(int* vector, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", vector[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Função para verificar se todos os elementos são cobertos
bool all_covered(int **A, int m, int n, int coverage[]) {
    for (int i = 0; i < m; i++) {
        bool covered = false;
        for (int j = 0; j < n; j++) {
            if (A[i][j] == 1 && coverage[j] == 1) {
                covered = true;
                break;
            }
        }
        if (!covered) {
            return false; // Se algum elemento não for coberto, retorna falso (false)
        }
    }
    return true; // Se todos os elementos foram cobertos, retorna verdadeiro (true)
}


int fitness(int** A, int* X, int m, int n) {
    if (!all_covered(A, m, n, X)) return 99999999;

    int uncovered = 0;
    for (int i = 0; i < m; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += A[i][j] * X[j];
        }
        uncovered += sum;
    }

    int C = 0;
    for (int i = 0; i < n; i++) {
        C += X[i];
    }

    // Adiciona penalidade para elementos cobertos mais de uma vez
    int penalty = 0;
    for (int i = 0; i < n; i++) {
        if (X[i] > 1) {
            penalty += (X[i] - 1); // A penalidade é proporcional à quantidade de vezes que o elemento é coberto
        }
    }

    return uncovered + C + penalty;
}


// Which solution is better?
bool better(int* X1, int* X2, int** A, int m, int n) {
    return fitness(A, X1, m, n) < fitness(A, X2, m, n);
}

bool better_or_equal(int* X1, int* X2, int** A, int m, int n) {
    return fitness(A, X1, m, n) <= fitness(A, X2, m, n);
}


// Find the best neighbor
int* best_neighbor(int* X, int** A, int m, int n) {
    int* best = (int*)malloc(n * sizeof(int));
    int* temp = (int*)malloc(n * sizeof(int));

    // Inicializa o 'melhor' com os valores de X
    for (int i = 0; i < n; i++) {
        best[i] = X[i];
    }

    // Verifica se o vizinho é melhor que o atual
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == i) {
                temp[j] = 1 - X[j];
            }
            else {
                temp[j] = X[j];
            }
        }

        if (better_or_equal(temp, best, A, m, n)) {
            for (int k = 0; k < n; k++) {
                best[k] = temp[k];
            }
        }
    }

    free(temp);
    return best;
}


int* set_cover(int** A, int* X, int m, int n) {
    int iterations = 0;
    int no_improvement_counter = 0;

    while (iterations < MAX_ITERATIONS && no_improvement_counter < 20) {
        int* Y = best_neighbor(X, A, m, n);
        // print_vector(Y, n);

        if (!better(Y, X, A, m, n)) {
            no_improvement_counter++; // Incrementa o contador se não houver melhora
            printf("No improvement: %d\n", no_improvement_counter);
            free(Y);
            continue;
        } 

        no_improvement_counter = 0; // Reseta o contador se houver melhora
        free(X);
        X = Y;
        iterations++;
    }

    return X;
}



// Função principal para encontrar a cobertura mínima
int* find_minimal_coverage(int **A, int m, int n) {
    srand(time(NULL));

    int *current_solution = greedy_set_cover(A, m, n); // Solução inicial
    // int *current_solution = (int*)malloc(n * sizeof(int));
    // for (int i = 0; i < n; i++) {
    //     current_solution[i] = 1;
    // }

    // Mostra a solução inicial
    printf("Solução inicial: ");
    int i, cont = 0;
    for (i = 0; i < n; i++) {
        printf("%d ", current_solution[i]);
        if (current_solution[i] == 1) {
            cont++;
        }
    }
    printf("\n");
    printf("Number of sets: %d\n", cont);

    int *X = set_cover(A, current_solution, m, n); // Solução final
    return X;
}