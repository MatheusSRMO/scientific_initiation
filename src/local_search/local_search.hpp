#ifndef _LOCAL_SEARCH_H_
#define _LOCAL_SEARCH_H_

#include "../solution/solution.hpp"
#include "../tabu_list/tabu_list.hpp"
#include "../graphic/graphic.hpp"

class LocalSearch {
    Matrix A;
    TabuList tabu_list;
    Solution initial_solution;
    Solution best_solution;
    Solution best_legal_solution;
    int max_iterations;

    public:
        LocalSearch(Matrix &A, int max_iterations, int max_tabu_size, Solution &initial_solution);
        ~LocalSearch();
        void run(Solution &current, Graphic &graphic);
        int fitness(Solution &s);
        bool is_feasible(Solution &s);
        void get_best_neighbors(int &best_fitness, vector<Solution> &neighbors, vector<Solution> &best_neighbors);
        void select_random_best_neighbor(vector<Solution> &best_neighbors, Solution &current);
        bool is_better();
};

#endif // _LOCAL_SEARCH_H_