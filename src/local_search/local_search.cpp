#include "local_search.hpp"

#include <iostream>
#include <random>

using namespace std;

LocalSearch::LocalSearch(Matrix &A, int max_iterations, int max_tabu_size, Solution &initial_solution) : A(A), tabu_list(TabuList(max_tabu_size)), initial_solution(initial_solution), best_solution(initial_solution), best_legal_solution(initial_solution) {
    this->max_iterations = max_iterations;
    this->upper_bound = numeric_limits<int>::max();
}

LocalSearch::~LocalSearch() {
    // nothing to do
}

// Complexity: O(i * n² * m), where i is the number of iterations, n is the number of columns and m is the number of rows
void LocalSearch::run(Solution &current, Graphic &graphic, ReportManager &report_manager) {
    
    this->upper_bound = this->best_solution.cost();
    this->best_solution.fitness(this->A);
    int iteration = 0;
    report_manager.add_partial_solution(this->best_solution, iteration);
    
    int iterations_without_improvement = 0;
    while (iterations_without_improvement < this->max_iterations) {
        iteration++;
        this->best_solution.fitness(this->A);
        // cout << 
        // "Fitness: " << this->best_solution.fitness(this->A) << 
        // "\tIteration: " << iterations_without_improvement << "\t\tUpper bound: " << this->upper_bound << endl;
        
        vector<Solution> neighbors = this->best_solution.get_neighbors(this->A, this->upper_bound);
        vector<Solution> best_neighbors;
        
        int best_fitness = numeric_limits<int>::max();

        this->get_best_neighbors(best_fitness, neighbors, best_neighbors);

        // seleciona o melhor vizinho
        this->select_random_best_neighbor(best_neighbors, current);

        // verifica o indice o conjunto flipado
        int fliped_set = -1;
        for (int i = 0; i < this->initial_solution.get_n(); i++) {
            if(current.get(i) != this->best_solution.get(i)) {
                fliped_set = i;
                break;
            }
        }

        // Adiciona o movimento a lista tabu
        Move move(
            fliped_set,
            this->best_solution.get(fliped_set > 0 ? fliped_set : 0),
                        current.get(fliped_set > 0 ? fliped_set : 0)
        );
        this->tabu_list.add(move);
        
        // this->tabu_list.print();

        // // mostra a solução atual
        // cout << "Best solution:    "; this->best_solution.print();
        // cout << "Current solution: "; current.print();

        // Atualiza a melhor solução
        current = this->best_solution;
        graphic.update(this->best_solution.fitness(this->A)); // Aqui é onde atualiza o gráfico

        // Se o vizinho escolhido for melhor que a melhor solução e for viável, atualiza a melhor solução
        if (this->is_better()) {
            this->best_legal_solution = this->best_solution;
            this->upper_bound = this->best_solution.cost();
            iterations_without_improvement = 0;
            report_manager.add_partial_solution(this->best_solution, iteration);
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
    for (int i = 0; i < (int)neighbors.size(); i++) { // Para cada vizinho
        // Controi o movimento
        Move move(i, neighbors[i].get(i), this->best_solution.get(i));
        int fitness = this->fitness(neighbors[i]);
        
        // Se tiver na lista tabu, não considera, critera de aspiração: se for melhor que a melhor solução, considera
        if (!(fitness <= best_fitness) && this->tabu_list.contains(move))
            continue;

        // Caso contrario, se for melhor que o fitness do melhor vizinho, atualiza e limpa o vetor de melhores vizinhos

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
    // int index = best_neighbors.size() > 1 ? rand() % best_neighbors.size() : 0;
    // this->best_solution = best_neighbors[index];

    // Nome da biblioteca de random do c++: <random>
    // seleciona um vizinho aleatorio entre os melhores vizinhos com essa biblioteca
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, best_neighbors.size()-1);
    this->best_solution = best_neighbors[dis(gen)];

    

    // // Adiciona o vizinho escolhido a lista tabu
    // this->tabu_list.add(this->best_solution);
}

bool LocalSearch::is_better() {
    bool is_better = this->fitness(this->best_solution) < this->fitness(this->best_legal_solution);
    return is_better;
}
