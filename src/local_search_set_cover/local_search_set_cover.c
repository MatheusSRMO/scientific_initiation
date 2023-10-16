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


int fitness(int** A, int* X, int m, int n, int *coverage) {
    if (!all_covered(A, m, n, X)) return 99999999;

    int C = 0; // Número de conjuntos utilizados
    int R = 0; // Número de elementos cobertos por mais de um conjunto
    int T = 0; // Número total de elementos

    for (int i = 0; i < m; i++) {
        coverage[i] = 0;
        for (int j = 0; j < n; j++) {
            if (A[i][j] == 1) {
                T++;
                if (X[j] == 1) {
                    coverage[i]++;
                }
            }
        }
        if (coverage[i] > 1) {
            R += coverage[i] - 1;
        }
        C += (coverage[i] > 0);
    }

    return C*C + R - T;
}




// Which solution is better?
bool better(int* X1, int* X2, int** A, int m, int n, int* coverage) {
    return fitness(A, X1, m, n, coverage) < fitness(A, X2, m, n, coverage);
}

bool better_or_equal(int* X1, int* X2, int** A, int m, int n, int* coverage) {
    return fitness(A, X1, m, n, coverage) <= fitness(A, X2, m, n, coverage);
}


// Find the best neighbor
void best_neighbor(int* X, int** A, int m, int n, int* best, int* temp, int* coverage) {
    
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
        bool is_better_or_equal = better_or_equal(temp, best, A, m, n, coverage);
        // printf("Better? %d -> ", is_better_or_equal);
        // print_vector(temp, n);

        if (is_better_or_equal) {
            for (int k = 0; k < n; k++) {
                best[k] = temp[k];
            }
        }
    }
}


int* set_cover(int** A, int* X, int m, int n) {
    int* best = (int*)malloc(n * sizeof(int));
    int* temp = (int*)malloc(n * sizeof(int));
    int* coverage = (int*)malloc(m * sizeof(int)); // Agora aloca para m (número de conjuntos)

    int iterations = 0;

    while (iterations < MAX_ITERATIONS) {
        best_neighbor(X, A, m, n, best, temp, coverage);
        print_vector(best, n);

        if (!better(best, X, A, m, n, coverage)) {
            break;
        } 

        for (int i = 0; i < n; i++) {
            X[i] = best[i];
        }
        iterations++;
    }

    free(temp);
    free(best);
    free(coverage);

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