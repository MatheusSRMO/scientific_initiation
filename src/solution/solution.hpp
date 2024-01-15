#if !defined SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <iostream>
#include "../matrix/matrix.hpp"
#include "../point/point.hpp"

using namespace std;

/**
 * @brief Represents a solution for a problem.
 * 
 * This class stores information about a solution, including the number of subsets,
 * the fitness score, the vector of subsets, and whether the solution is feasible or not.
 * It provides various constructors, getters, and setters to manipulate the solution.
 * The class also includes methods to calculate the fitness score, check feasibility,
 * and perform operations such as getting neighbors and printing the solution.
 */
class Solution {
    private:
        int fitness_score; // = cost() + num_of_elements_uncovered()
        vector<bool> V;

        void nums(Matrix &matrix, int &num_of_elements_uncovered, int &num_of_elements_covered_by_more_than_one_subset);

    public:
        int get_n() const { return this->V.size(); }
        vector<Solution> get_neighbors(Matrix &matrix);

        Solution();

        Solution(int n, bool default_value = false);

        Solution(int *V, int n);

        /**
         * @brief Constructs a Solution object with the given vector of booleans.
         * 
         * @param V The vector of booleans to initialize the Solution object.
         */
        Solution(vector<bool> V);

        Solution(const Solution &s);

        /**
         * @brief Sets the fitness score of the solution.
         * 
         * @param score The fitness score to set.
         */
        void set_fitness_score(int score) { this->fitness_score = score;}

        /**
         * @brief Gets the fitness score.
         * 
         * @return The fitness score.
         */
        int get_fitness_score() const { return this->fitness_score; }
                
        ~Solution();
        
        void print();
                
        string to_string();
                        
        void set(int i, bool value);
                        
        bool get(int i);
                
        int cost();
                        
        int num_of_elements_uncovered(Matrix &matrix);
                        
        int num_of_elements_covered_by_more_than_one_subset(Matrix &matrix);
                        
        int fitness(Matrix &matrix);

        void fitness_with_cache(Matrix &matrix, Solution &s, int i);

        bool solution_cover_line(Matrix &matrix, int line, int column = -1);

        bool is_feasible(Matrix &matrix);
        
        Solution &operator=(const Solution &s);
        bool operator==(const Solution &s) const;
        bool operator!=(const Solution &s) const;

};
        

#endif // SOLUTION_H