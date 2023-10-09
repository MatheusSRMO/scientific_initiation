#include "local_search_set_cover.h"

// Função para verificar se todos os elementos são cobertos
bool all_covered(int **A, int m, int n, int coverage[]) {
    int i, j;
    int covered;

    for (i = 0; i < m; i++) {
        covered = 0;
        for (j = 0; j < n; j++) {
            if (A[i][j] == 1 && coverage[j] == 1) {
                covered = 1;
                break;
            }
        }
        if (covered == 0) {
            return false; // Se algum elemento não for coberto, retorna falso (false)
        }
    }
    return true; // Se todos os elementos foram cobertos, retorna verdadeiro (true)
}

// Função para avaliar a cobertura
int evaluate_coverage(int **A, int m, int n, int coverage[]) {
    int i, j, count = 0;
    for (i = 0; i < n; i++) {
        if (!coverage[i]) continue;
        for (j = 0; j < m; j++) {
            if (A[j][i]) {
                // Atualiza o contador de conjuntos cobertos
                count++;
                break;
            }
        }
    }
    return count;
}

// Função para avaliar a cobertura sem um elemento
int evaluate_without_element(int **A, int m, int n, int coverage[], int index) {
    int i, j, count = 0;
    int _coverage[n];
    for(int i = 0; i < n; i++) {
        _coverage[i] = coverage[i];
    }

    // Passo 1: Remover o conjunto do índice
    for (i = 0; i < m; i++) {
        _coverage[i] = _coverage[i] && !A[i][index];
    }

    // Passo 2: Contar os conjuntos cobertos
    count = evaluate_coverage(A, m, n, _coverage);
    return count;
}

// Função para gerar um vizinho
int* generate_neighbor(int **A, int m, int n, int *current_solution) {
    // Gerar um vizinho aleatório
    int index = rand() % n;

    int *neighbor = malloc(n * sizeof(int));
    int i;

    // Copia a solução atual para o vizinho
    for (i = 0; i < n; i++) {
        neighbor[i] = current_solution[i];
    }

    // Remove o conjunto do índice
    neighbor[index] = 0;
    return neighbor;
}

// Função principal para encontrar a cobertura mínima
int* find_minimal_coverage(int **A, int m, int n) {
    srand(time(NULL));

    int *coverage = malloc(n * sizeof(int));
    int *current_solution = malloc(n * sizeof(int));
    int iterations_without_improvement = 0;
    int i, j, k, l, count, best_count;

    // Inicializar a solução atual
    for (i = 0; i < n; i++) {
        current_solution[i] = 1;
    }

    // Inicializar o contador de iterações sem melhora
    iterations_without_improvement = 0;

    // Enquanto o contador de iterações sem melhora for menor que MAX_ITERATIONS
    while (iterations_without_improvement < MAX_ITERATIONS) {

        int *neighbor = generate_neighbor(A, m, n, current_solution);

        // Se o vizinho for pior que a solução atual ou não cobrir todos os conjuntos, continuar
        if (
            !all_covered(A, m, n, neighbor)
            || evaluate_coverage(A, m, n, neighbor) >= evaluate_coverage(A, m, n, current_solution)
        ) {
            iterations_without_improvement++;
            free(neighbor);
            continue;
        }

        // Se o vizinho for melhor que a solução atual, atualizar a solução atual
        for (i = 0; i < n; i++) {
            current_solution[i] = neighbor[i];
        }

        // Atualizar o contador de iterações sem melhora
        iterations_without_improvement = 0;

        // Liberar memória alocada para o vizinho
        free(neighbor);
    }

    // Liberar memória não utilizada
    free(coverage);

    return current_solution;
}
