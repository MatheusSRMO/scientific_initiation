#include "greedy_local_search.hpp"


Solution GreedySetCover::run(Matrix &matrix) {
    vector<bool> V(matrix.get_n(), 0);
    vector<bool> U(matrix.get_m(), 1);

    bool done = false;
    while (!done) {
        done = true;
        int max_intersection = 0;
        int max_set = -1;
        for (int j = 0; j < matrix.get_n(); j++) {
            if (V[j] == 0) {
                int intersection = 0;
                for (int i = 0; i < matrix.get_m(); i++) {
                    if (U[i] == 1 && matrix.get(i, j) == 1) {
                        intersection += 1;
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
            for (int i = 0; i < matrix.get_m(); i++) {
                if (matrix.get(i, max_set) == 1) {
                    U[i] = 0;
                }
            }
            done = false;
        }
    }

    return Solution(V);
}
