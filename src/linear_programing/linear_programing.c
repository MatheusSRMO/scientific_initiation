#include "linear_programing.h"

typedef struct {
    int *x; // Variáveis de decisão
    int z;  // Valor da função objetivo
} Solution;

LinearPrograming *linear_programing_create(int n, int m, LPObjective objective, LPConstraint constraints) {
    LinearPrograming *lp = (LinearPrograming *) malloc(sizeof(LinearPrograming));
    lp->n = n;
    lp->m = m;
    lp->solution = (int *) malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) {
        lp->solution[i] = 0;
    }
    lp->solution_size = 0;

    lp->A = (int **) malloc(sizeof(int *) * m);
    for(int i = 0; i < m; i++) {
        lp->A[i] = (int *) malloc(sizeof(int) * n);
        for(int j = 0; j < n; j++) {
            lp->A[i][j] = 0;
        }
    }
    lp->b = (int *) malloc(sizeof(int) * m);
    for(int i = 0; i < m; i++) {
        lp->b[i] = 1; // set all b values to 1 
    }
    lp->c = (int *) malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) {
        lp->c[i] = 1; // set all c values to 1
    }
    lp->objective = objective;
    lp->constraints = constraints;
    return lp;
}

void linear_programing_set_objective(LinearPrograming *lp, int *c) {
    for(int i = 0; i < lp->n; i++) {
        lp->c[i] = c[i];
    }
}

void linear_programing_set_right_hand_side(LinearPrograming *lp, int *b) {
    for(int i = 0; i < lp->m; i++) {
        lp->b[i] = b[i];
    }
}

void linear_programing_set_constraint_matrix(LinearPrograming *lp, int **A) {
    for(int i = 0; i < lp->m; i++) {
        for(int j = 0; j < lp->n; j++) {
            lp->A[i][j] = A[i][j];
        }
    }
}

void linear_programing_destroy(LinearPrograming *lp) {
    for(int i = 0; i < lp->m; i++) {
        free(lp->A[i]);
    }
    free(lp->A);
    free(lp->b);
    free(lp->c);
    free(lp->solution);
    free(lp);
}

Solution implicit_enumeration(int n, int m, int **A, int *b, int *c) {
    Solution best_solution;
    best_solution.x = (int *)malloc(sizeof(int) * n);
    best_solution.z = INT_MIN;

    for (int i = 0; i < (1 << n); i++) {
        int valid_solution = 1;
        int *x = (int *)malloc(sizeof(int) * n);

        for (int j = 0; j < n; j++) {
            x[j] = (i >> j) & 1;
        }

        for (int j = 0; j < m; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[j][k] * x[k];
            }
            if (sum > b[j]) {
                valid_solution = 0;
                break;
            }
        }

        if (valid_solution) {
            int z = 0;
            for (int j = 0; j < n; j++) {
                z += c[j] * x[j];
            }
            if (z > best_solution.z) {
                best_solution.z = z;
                memcpy(best_solution.x, x, sizeof(int) * n);
            }
        }

        free(x);
    }

    return best_solution;
}

void calcularSolucaoOtima(int **a, int *b, int *solucao, int linhas, int colunas) {
    int melhorSolucao[colunas];
    int menorValor = 999999; // Valor inicial grande

    int numPossibilidades = 1 << colunas; // 2 elevado ao número de colunas

    for (int i = 0; i < numPossibilidades; i++) {
        for (int j = 0; j < colunas; j++) {
            solucao[j] = (i >> j) & 1; // Gera as possibilidades de 0 ou 1
        }

        int valorAtual = 0;
        for (int linha = 0; linha < linhas; linha++) {
            int somaLinha = 0;
            for (int coluna = 0; coluna < colunas; coluna++) {
                somaLinha += a[linha][coluna] * solucao[coluna];
            }
            valorAtual += (somaLinha - b[linha]) * (somaLinha - b[linha]);
        }

        if (valorAtual < menorValor) {
            menorValor = valorAtual;
            for (int coluna = 0; coluna < colunas; coluna++) {
                melhorSolucao[coluna] = solucao[coluna];
            }
        }
    }

    for (int i = 0; i < colunas; i++) {
        solucao[i] = melhorSolucao[i];
    }
}


LPStatus lp_solve(LinearPrograming *lp) {
    Solution solution = implicit_enumeration(lp->n, lp->m, lp->A, lp->b, lp->c);

    if (solution.z != INT_MIN) {
        for (int i = 0; i < lp->n; i++) {
            lp->solution[i] = solution.x[i];
        }
        lp->solution_size = lp->n;
        free(solution.x);
        return LP_SUCCESS;
    } else {
        return LP_ERROR;
    }
}

void linear_programing_get_solution(LinearPrograming *lp, int *solution) {
    for(int i = 0; i < lp->n; i++) {
        solution[i] = lp->solution[i];
    }
}