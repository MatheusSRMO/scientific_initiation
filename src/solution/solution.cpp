#include "solution.hpp"
#include <iostream>

using namespace std;


Solution::Solution() {
    this->V = vector<bool>();
    this->fitness_score = -1;
}


Solution::Solution(int n, bool default_value) {
    this->V = vector<bool>(n, default_value);
    this->fitness_score = -1;
}

Solution::Solution(const Solution &s) {
    *this = s;
}


Solution::Solution(int *V, int n) {
    this->V = vector<bool>(n);
    for (int i = 0; i < n; i++) {
        this->V[i] = V[i] == 1;
    }
    this->fitness_score = -1;
}


Solution::Solution(vector<bool> V) {
    this->V = V;
    this->fitness_score = -1;
}


Solution::~Solution() {
    // nothing to do, vector is automatically destroyed
}


// Complexity: O(n), where n is the number of elements
void Solution::print() {
    cout << this->to_string() << endl;
}


// Complexity: O(n), where n is the number of elements
string Solution::to_string() {
    string s = "[";
    for (int i = 0; i < (int)this->V.size(); i++) {
        s += std::to_string(this->V[i]);
        if (i < (int)this->V.size() - 1) {
            s += ", ";
        }
    }
    s += "]";
    return s;
}


// Complexity: O(1)
void Solution::set(int i, bool value) {
    this->V[i] = value;
}


// Complexity: O(1)
bool Solution::get(int i) {
    return this->V[i];
}


// Complexity: O(n), where n is the number of elements
int Solution::cost() {
    int cost = 0;
    for (int i = 0; i < (int)this->V.size(); i++)
        cost += this->V[i];
    return cost;
}


// Complexity: O(n * m), where n is the number of subsets and m is the number of elements
int Solution::fitness(Matrix &matrix) {
    if(this->fitness_score != -1) {
        return this->fitness_score; // if fitness score has already been calculated, return it
    }

    int elements_uncovered, elements_covered_more_one;
    this->nums(matrix, elements_uncovered, elements_covered_more_one);
    
    this->fitness_score = this->cost() + elements_uncovered;
    
    return this->fitness_score;
}


// A Ideia é olhar apenas para o subconjunto que foi alterado, e não para todos os subconjuntos
void Solution::fitness_with_cache(Matrix &matrix, Solution &old_solution, int j) {
    bool current_value = this->get(j);
    int current_fitness_score = old_solution.fitness_score + current_value - !current_value;

    vector<bool> current_subset = matrix.get_column(j);

    for (int i = 0; i < (int)current_subset.size(); i++) {
        if(!current_subset[i]) continue;
        
        bool old_solution_cover_line = old_solution.solution_cover_line(matrix, i);

        if (current_value && !old_solution_cover_line) {
            current_fitness_score--;
            continue;
        }

        if (!current_value && old_solution_cover_line && !this->solution_cover_line(matrix, i, j)) {
            current_fitness_score++;
        }
    }

    this->fitness_score = current_fitness_score;
}

bool Solution::solution_cover_line(Matrix &matrix, int line, int column) {
    for (int j = 0; j < matrix.get_n(); j++) {
        if (j == column) continue;
        if (matrix.get(line, j) && this->get(j)) {
            return true;
        }
    }
    return false;
}


// Complexity: O(n * m), where n is the number of subsets and m is the number of elements
bool Solution::is_feasible(Matrix &matrix) {
    return this->num_of_elements_uncovered(matrix) == 0;
}


// Complexity: O(n), where n is the number of elements
vector<Solution> Solution::get_neighbors(Matrix &matrix, int upper_bound) {
    vector<Solution> neighbors;
    for (int i = 0; i < (int)this->V.size(); i++) {
        Solution neighbor(*this); // copy constructor
        neighbor.set(i, !neighbor.get(i)); // flip bit
        neighbor.fitness_with_cache(matrix, *this, i);

        // // se foi um movimento de REMOVE_SET, adiciona o vizinho
        // if (this->get(i) && !neighbor.get(i)) {
        //     neighbors.push_back(neighbor);
        //     continue;
        // }

        // se foi um movimento de ADD_SET, adiciona o vizinho se o número de conjuntos na solução atual for menor que upperbound - 1
        
        //the move ADD SET can be applied in the current solution only if the number of sets in the current solution is less than upperbound − 1.

        // cout << "neighbor.cost(): " << neighbor.cost() << " upper_bound: " << upper_bound << endl;

        // if (neighbor.cost() < upper_bound -1) {
            neighbors.push_back(neighbor);
        // }
    }

    // cout << "neighbors.size(): " << neighbors.size() << endl;
    return neighbors;
}


// Complexity: O(n * m), where n is the number of subsets and m is the number of elements
int Solution::num_of_elements_uncovered(Matrix &matrix) {
    int elements_uncovered, elements_covered_more_one;
    this->nums(matrix, elements_uncovered, elements_covered_more_one);
    return elements_uncovered;
}


// Complexity: O(n * m), where n is the number of subsets and m is the number of elements
int Solution::num_of_elements_covered_by_more_than_one_subset(Matrix &matrix) {
    int elements_uncovered, elements_covered_more_one;
    this->nums(matrix, elements_uncovered, elements_covered_more_one);
    return elements_covered_more_one;
}


// Complexity: O(n * m), where n is the number of subsets and m is the number of elements
void Solution::nums(Matrix &matrix, int &elements_uncovered, int &elements_covered_more_one) {
    elements_uncovered = 0;
    elements_covered_more_one = 0;

    for (int i = 0; i < matrix.get_m(); i++) {
        int sum = 0;
        for (int j = 0; j < matrix.get_n(); j++) {
            sum += matrix.get(i, j) && this->V[j];
            if(sum > 1) break; // optimization (if sum > 1, there is no need to continue summing
        }
        if (sum == 0) {
            elements_uncovered++;
            continue;
        }
        elements_covered_more_one++;
    }
}

// Sobrecarga de operadores (=)
Solution &Solution::operator=(const Solution &s) {
    this->V = s.V;
    this->fitness_score = s.fitness_score;
    return *this;
}

// Sobrecarga de operadores (==) // Complexity: O(n), where n is the number of elements
bool Solution::operator==(const Solution &s) const {
    return equal(this->V.begin(), this->V.end(), s.V.begin());
}

// Sobrecarga de operadores (!=) // Complexity: O(n), where n is the number of elements
bool Solution::operator!=(const Solution &s) const {
    return *this == s ? false : !(*this == s);
}
