#include "local_search_set_cover.h"

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

// Fitness = NrOfUncoveredElements+|C|
double fitness(int** A, int* X, int m, int n) {
    double cont = 0;
    for(int i = 0; i < n; i++) {
        cont += X[i];
    }

    for(int i = 0; i < m; i++) {
        bool covered = false;
        for(int j = 0; j < n; j++) {
            if(A[i][j] == 1 && X[j] == 1) {
                covered = true;
                break;
            }
        }
        cont += !covered;
    }

    return cont;
}

bool better(int* X1, int* X2, int** A, int m, int n) {
    return fitness(A, X1, m, n) < fitness(A, X2, m, n);
}

bool equal(int* X1, int* X2, int** A, int m, int n) {
    return fitness(A, X1, m, n) == fitness(A, X2, m, n);
}

bool better_or_equal(int* X1, int* X2, int** A, int m, int n) {
    return fitness(A, X1, m, n) <= fitness(A, X2, m, n);
}

void add_remove_set(int* X, int** A, int m, int n, int* temp, int set_idx) {
    // Faz uma cópia de X para temp
    memcpy(temp, X, n * sizeof(int));

    // Adiciona ou remove o conjunto set_idx de temp
    temp[set_idx] = 1 - temp[set_idx];
}

void random_perturbation(int* X, int** A, int m, int n, int* best, int* temp) {
    // Faz uma cópia de X para temp
    memcpy(temp, X, n * sizeof(int));

    // Escolhe aleatoriamente um índice e inverte o valor
    int rand_idx = rand() % n;
    temp[rand_idx] = 1 - temp[rand_idx];

    memcpy(best, temp, n * sizeof(int)); // Atualiza o 'melhor'
}

void combine_solutions(int* X, int* Y, int* temp, int n) {
    // Combina as soluções X e Y (por exemplo, faz a união dos conjuntos selecionados)
    for (int i = 0; i < n; i++) {
        temp[i] = X[i] || Y[i];
    }
}

void best_neighbor(int* X, int** A, int m, int n, int* best, int* temp) {
    // Inicializa o 'melhor' com os valores de X
    memcpy(best, X, n * sizeof(int));

    // Cria uma cópia temporária de X
    memcpy(temp, X, n * sizeof(int));

    for (int i = 0; i < n; i++) {
        // Adiciona ou remove o conjunto i de temp
        add_remove_set(best, A, m, n, temp, i);
        if(better(temp, best, A, m, n)) {
            memcpy(best, temp, n * sizeof(int));
        }
        else if(equal(temp, best, A, m, n)) {
            memcpy(best, temp, n * sizeof(int));
            combine_solutions(X, best, temp, n);
        }
    }
}


int* local_search(int** A, int* X, int m, int n) {
    int* best = (int*)malloc(n * sizeof(int));
    int* temp = (int*)malloc(n * sizeof(int));

    int iterations = 0;

    while (iterations < MAX_ITERATIONS) {
        best_neighbor(X, A, m, n, best, temp);
        // print_vector(best, n);

        if (!better(best, X, A, m, n)) break;

        memcpy(X, best, n * sizeof(int));

        iterations++;
    }

    free(temp);
    free(best);

    return X;
}

// Função principal para encontrar a cobertura mínima
int* local_search_set_cover(int **A, int m, int n) {
    // Encontra a solução inicial
    int *current_solution = greedy_set_cover(A, m, n);

    // Encontra a solução final
    int *X = local_search(A, current_solution, m, n); // Solução final
    return X;
}