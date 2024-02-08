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

int main() {
    /* =================== MAIN INFOS =================== */
    const string file_path = "data/scp/jardim_da_penha_vitória_es_brasil.scp";


    /* =================== OPEN SCP FILE =================== */
    ScpFileReader scp_file_reader(file_path);
    scp_file_reader.read_file();
    scp_file_reader.calculate_coverage_matrix(RANGE);


    /* =================== GET GRAPH AND CONSTRUCTION POINTS =================== */
    string name = scp_file_reader.get_name();
    vector<Point> graph_points = scp_file_reader.get_graph_points();
    Graph graph = scp_file_reader.get_graph();
    vector<Point> points = scp_file_reader.get_construction_points();


    /* =================== READ COVERAGE MATRIX FROM FILE =================== */
    Matrix matrix = scp_file_reader.get_coverage_matrix();


    /* =================== RUN GREEDY LOCAL SEARCH =================== */
    Solution greedy_solution = GreedySetCover::run(matrix);


    /* =================== CURRENT SOLUTION =================== */
    Solution current_solution = greedy_solution;


    /* =================== VIEWER =================== */
    Graphic graphic(0, 0, 2000, 800);
    Package package(name, WIDTH, HEIGHT, RANGE, &graphic, &graph, &current_solution, &points, &graph_points);
    Thread thread(&Viewer::run, &package);
    thread.launch();


    /* =================== RUN LOCAL SEARCH =================== */
    LocalSearch local_search(matrix, MAX_ITERATIONS, TABU_SIZE, greedy_solution);
    local_search.run(current_solution, graphic);


    /* =================== SHOW RESULT =================== */
    cout << "greedy_solution.fitness_score: " << greedy_solution.fitness(matrix) << endl;
    cout << "current_solution.fitness_score: " << current_solution.fitness(matrix) << endl;

    return 0;
}
