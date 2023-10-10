#include "greedy_set_cover.h"

/*
Greedy Set Cover(X, F)
    C = 0
    U = X
    while U != 0
        choose S in F that maximizes |S ∩ U|
        C = C ∪ {S}
        U = U \ S
    return C
*/
int* greedy_set_cover(int** A, int m, int n) {
    int* V = (int*)malloc(n * sizeof(int)); // Inicializa vetor V

    // Inicializa V com 0
    for (int i = 0; i < n; i++) {
        V[i] = 0;
    }

    int* U = (int*)malloc(m * sizeof(int)); // Inicializa vetor U

    // Inicializa U com 1
    for (int i = 0; i < m; i++) {
        U[i] = 1;
    }

    int done = 0;

    while (!done) {
        done = 1;

        // Escolhe conjunto S em F que maximiza |S ∩ U|
        int max_intersection = 0;
        int max_set = -1;

        for (int j = 0; j < n; j++) {
            if (V[j] == 0) {
                int intersection = 0;
                for (int i = 0; i < m; i++) {
                    if (U[i] == 1 && A[i][j] == 1) {
                        intersection++;
                    }
                }

                if (intersection > max_intersection) {
                    max_intersection = intersection;
                    max_set = j;
                }
            }
        }

        if (max_set != -1) {
            V[max_set] = 1;

            // Atualiza U
            for (int i = 0; i < m; i++) {
                if (A[i][max_set] == 1) {
                    U[i] = 0;
                }
            }

            done = 0;
        }
    }

    free(U); // Libera memória alocada para U

    return V;
}
