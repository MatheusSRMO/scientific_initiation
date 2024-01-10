#include "local_search.hpp"

#include <iostream>

using namespace std;

LocalSearch::LocalSearch(Matrix &A, int max_iterations, int max_tabu_size, Solution &initial_solution) : A(A), tabu_list(TabuList(max_tabu_size)), initial_solution(initial_solution), best_solution(initial_solution), best_legal_solution(initial_solution) {
    this->max_iterations = max_iterations;
}

LocalSearch::~LocalSearch() {
    // nothing to do
}

// Complexity: O(i * n² * m), where i is the number of iterations, n is the number of columns and m is the number of rows
void LocalSearch::run(Solution &current) {
    int iterations_without_improvement = 0;

    while (iterations_without_improvement < this->max_iterations) {
        cout << 
        "Fitness: " << this->best_solution.fitness(this->A) << 
        "\tIteration: " << iterations_without_improvement << endl;
        
        vector<Solution> neighbors = this->best_solution.get_neighbors(this->A);
        vector<Solution> best_neighbors = vector<Solution>();
        best_neighbors.push_back(neighbors[0]);
        int best_fitness = this->fitness(neighbors[0]);

        this->get_best_neighbors(best_fitness, neighbors, best_neighbors);

        this->select_random_best_neighbor(best_neighbors, current);

        current = this->best_solution;

        // Se o vizinho escolhido for melhor que a melhor solução e for viável, atualiza a melhor solução
        if (this->is_better()) {
            this->best_legal_solution = this->best_solution;
            iterations_without_improvement = 0;
            continue;
        }
        iterations_without_improvement++;
    }

    current = this->best_legal_solution;
}

int LocalSearch::fitness(Solution &s) {
    return s.fitness(this->A);
}

bool LocalSearch::is_feasible(Solution &s) {
    return s.is_feasible(this->A);
}

void LocalSearch::get_best_neighbors(int &best_fitness, vector<Solution> &neighbors, vector<Solution> &best_neighbors) {
    // Complexidade: O(n), onde n é o número de colunas
    for (int i = 1; i < (int)neighbors.size(); i++) { // Para cada vizinho
        // Se tiver na lista tabu, não considera
        if (this->tabu_list.contains(neighbors[i]))
            continue;

        // Caso contrario, se for melhor que o fitness do melhor vizinho, atualiza e limpa o vetor de melhores vizinhos

        int fitness = this->fitness(neighbors[i]);
        if (fitness < best_fitness) {
            best_fitness = fitness;
            best_neighbors.clear();
            best_neighbors.push_back(neighbors[i]);
        }

        // Caso contrario, se for igual ao fitness do melhor vizinho, adiciona ao vetor de melhores vizinhos
        else if (fitness == best_fitness) {
            best_neighbors.push_back(neighbors[i]);
        }
    }
}

void LocalSearch::select_random_best_neighbor(vector<Solution> &best_neighbors, Solution &current) {
    // Escolhe um vizinho aleatorio entre os melhores vizinhos
    int index = best_neighbors.size() > 1 ? rand() % best_neighbors.size() : 0;
    this->best_solution = best_neighbors[index];

    // Adiciona o vizinho escolhido a lista tabu
    this->tabu_list.add(this->best_solution);
}

bool LocalSearch::is_better() {
    bool is_better = this->fitness(this->best_solution) < this->fitness(this->best_legal_solution);
    return is_better;
}
