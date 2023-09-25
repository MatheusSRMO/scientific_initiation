#include <stdio.h>

// Complexidade: O(2^n)
void calcularSolucaoOtima(int *a, int *b, int *solucao, int linhas, int colunas) {
    int melhorSolucao[colunas];
    int menorValor = 999999; // Valor inicial grande

    int numPossibilidades = 1 << colunas; // 2 elevado ao número de colunas
    printf("Possibilidades: %d\n", numPossibilidades);

    for (int i = 0; i < numPossibilidades; i++) {
        for (int j = 0; j < colunas; j++) {
            solucao[j] = (i >> j) & 1; // Gera as possibilidades de 0 ou 1
        }

        int valorAtual = 0;
        for (int linha = 0; linha < linhas; linha++) {
            int somaLinha = 0;
            for (int coluna = 0; coluna < colunas; coluna++) {
                somaLinha += a[linha * colunas + coluna] * solucao[coluna];
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

int main() {
    int a[6][30] = {
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        {0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1},
        {1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
        {0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0},
        {1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1}
    };

    int b[6] = {1, 1, 1, 1, 1, 1};
    int solucao[30];

    int linhas = 6;
    int colunas = 30;

    calcularSolucaoOtima((int *)a, b, solucao, linhas, colunas);

    printf("A solucao otima e: ");
    for (int i = 0; i < colunas; i++) {
        printf("%d ", solucao[i]);
    }
    printf("\n");

    return 0;
}
