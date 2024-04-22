#include <iostream>
#include "src/graph/graph.hpp"
#include "src/graphic/graphic.hpp"
#include "src/point/point.hpp"
#include "src/matrix/matrix.hpp"
#include "src/viewer/viewer.hpp"
#include "src/local_search/local_search.hpp"
#include "src/scp_file_reader/scp_file_reader.hpp"
#include "src/greedy_local_search/greedy_local_search.hpp"

using namespace std;


#define WIDTH 800
#define HEIGHT 600
#define RANGE 300
#define MAX_ITERATIONS 1e4
#define TABU_SIZE 1e1

// exemplo de execução: ./main data/OR-Library-Custom/scp41.txt 
int main() {
    srand(2);

    /* =================== READ COVERAGE MATRIX FROM FILE =================== */
    Matrix matrix = Matrix::read_from_file("data/OR-Library-Custom/scp46.txt");

    /* =================== RUN GREEDY LOCAL SEARCH =================== */
    Solution greedy_solution = GreedySetCover::run(matrix);

    /* =================== CURRENT SOLUTION =================== */
    Solution current_solution = greedy_solution;
    Graphic graphic(0, 0, 0, 0);

    /* =================== RUN LOCAL SEARCH =================== */
    LocalSearch local_search(matrix, MAX_ITERATIONS, TABU_SIZE, greedy_solution);
    local_search.run(current_solution, graphic);


    /* =================== SHOW RESULT =================== */
    cout << "greedy_solution.fitness_score: " << greedy_solution.fitness(matrix) << endl;
    cout << "current_solution.fitness_score: " << current_solution.fitness(matrix) << endl;
}