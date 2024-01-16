#include <iostream>
#include "src/graph/graph.hpp"
#include "src/point/point.hpp"
#include "src/matrix/matrix.hpp"
#include "src/viewer/viewer.hpp"
#include "src/local_search/local_search.hpp"
#include "src/scp_file_reader/scp_file_reader.hpp"
#include "src/greedy_local_search/greedy_local_search.hpp"

using namespace std;


int main() {
    /* =================== MAIN INFOS =================== */
    const string file_path = "data/scp/jardim_da_penha_vitória_es_brasil.scp";
    const double range = 300;

    const int width = 800;
    const int height = 600;

    const int max_iterations = 1e3;
    const int tabu_size = 1e1;


    /* =================== OPEN SCP FILE =================== */
    ScpFileReader scp_file_reader(file_path);
    scp_file_reader.read_file();
    scp_file_reader.calculate_coverage_matrix(range);


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
    // Package package(name, width, height, range, &graph, &current_solution, &points, &graph_points);
    // Thread thread(&Viewer::run, &package);
    // thread.launch();


    /* =================== RUN LOCAL SEARCH =================== */
    LocalSearch local_search(matrix, max_iterations, tabu_size, greedy_solution);
    local_search.run(current_solution);


    /* =================== SHOW RESULT =================== */
    cout << "greedy_solution.fitness_score: " << greedy_solution.fitness(matrix) << endl;
    cout << "current_solution.fitness_score: " << current_solution.fitness(matrix) << endl;

    return 0;
}
