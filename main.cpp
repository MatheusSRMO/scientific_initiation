#include <iostream>
#include "src/graph/graph.hpp"
#include "src/graphic/graphic.hpp"
#include "src/point/point.hpp"
#include "src/matrix/matrix.hpp"
#include "src/viewer/viewer.hpp"
#include "src/local_search/local_search.hpp"
#include "src/scp_file_reader/scp_file_reader.hpp"
#include "src/greedy_local_search/greedy_local_search.hpp"
#include "src/report_manager/report_manager.hpp"
#include <cstring> // for strcmp
#include <filesystem>

#include <iostream>
#include <filesystem>
#include <string>

using namespace std;


#define WIDTH 800
#define HEIGHT 600
#define RANGE 300
#define MAX_ITERATIONS 1e4
#define TABU_SIZE 1e1

void execute_type_1(string path);
void execute_type_2(string path);
void execute_type_3(string path, int range = RANGE);

// exemplo de execução: ./main data/OR-Library-Custom/scp41.txt 
int main(int argc, char* argv[]) {
    // 3 types of execution:
    // 1. ./main 1 data/OR-Library-Custom/
    // 2. ./main 2 data/OR-Library-Custom/scp41.txt
    // 3. ./main 3 data/scp/jardim_da_penha_vitória_es_brasil.scp 300

    if(argc < 2) {
        std::cout << "Usage: ./main <type> <file_path>" << std::endl;
        return 1;
    }

    if(strcmp(argv[1], "1") == 0) {
        execute_type_1(argv[2]);
        return 0;
    }

    if(strcmp(argv[1], "2") == 0) {
        execute_type_2(argv[2]);
        return 0;
    }

    if(argc < 3) {
        std::cout << "Usage: ./main <type> <file_path> <range>" << std::endl;
        return 1;
    }

    if(strcmp(argv[1], "3") == 0) {
        execute_type_3(argv[2], atoi(argv[3]));
        return 0;
    }

    cout << "Invalid type" << endl;
    return 1;
}

void execute_type_1(string path) {
    for (const auto& entry : filesystem::directory_iterator(path)) {
        if (filesystem::is_regular_file(entry.path())) {
            std::cout << entry.path().filename() << std::endl;
            execute_type_2(entry.path());
        }
    }

}

void execute_type_2(string path) {
    /* =================== READ COVERAGE MATRIX FROM FILE =================== */
    Matrix matrix = Matrix::read_from_file(path);
    
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

void execute_type_3(string path, int range) {
    /* =================== OPEN SCP FILE =================== */
    ScpFileReader scp_file_reader(path);
    string name = scp_file_reader.get_name();
    scp_file_reader.read_file();
    scp_file_reader.calculate_coverage_matrix(range);
    ReportManager report_manager("report.txt");

    /* =================== GET GRAPH AND CONSTRUCTION POINTS =================== */
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
    Package package(name, WIDTH, HEIGHT, range, &graphic, &graph, &current_solution, &points, &graph_points);
    Thread thread(&Viewer::run, &package);
    thread.launch();

    /* =================== RUN LOCAL SEARCH =================== */
    LocalSearch local_search(matrix, MAX_ITERATIONS, TABU_SIZE, greedy_solution);
    local_search.run(current_solution, graphic);

    /* =================== SHOW RESULT =================== */
    cout << "greedy_solution.fitness_score: " << greedy_solution.fitness(matrix) << endl;
    cout << "current_solution.fitness_score: " << current_solution.fitness(matrix) << endl;

    /* =================== WRITE REPORT =================== */
    report_manager.write_cvrp_intance(scp_file_reader, "report_instance.txt");
}