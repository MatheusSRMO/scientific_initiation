#include "report_manager.hpp"

ReportManager::ReportManager() {
    this->file_name = "report.txt";
    this->points = vector<Point>();
    this->iterations = 0;
}

ReportManager::ReportManager(string file_name) {
    this->file_name = file_name;
    this->points = vector<Point>();
    this->iterations = 0;
}

void ReportManager::add_partial_solution(Solution solution) {
    Point point = Point(++this->iterations, solution.get_fitness_score());
    this->points.push_back(point);
}

void ReportManager::write_report() {
    ofstream file(this->file_name);
    if (!file.is_open()) {
        cout << "Error: could not open file " << this->file_name << endl;
        return;
    }
    for (Point point : this->points) {
        file << point << endl;
    }
    file.close();
}

/*
Formato do arquivo de instância:
NAME : p-n16-k8
COMMENT : 16 customers, 8 vehicles, Euclidean
TYPE : CVRP
DIMENSION : 16
EDGE_WEIGHT_TYPE : EUC_2D
NODE_COORD_SECTION
1 40 50
...
16 45 68
DEPOT_SECTION
1
-1
EOF
*/
void ReportManager::write_cvrp_intance(ScpFileReader &file_reader, string file_name) {
    ofstream file(file_name);
    if (!file.is_open()) {
        cout << "Error: could not open file " << file_name << endl;
        return;
    }
    file << "NAME : " << file_reader.get_name() << endl;
    file << "COMMENT : " << "ARQUIVO TESTE" << endl;
    file << "TYPE : " << "CVRP" << endl;
    file << "DIMENSION : " << file_reader.get_dimension() << endl;
    file << "EDGE_WEIGHT_TYPE : " << "EUC_2D" << endl;
    file << "NODE_COORD_SECTION" << endl;
    int i = 0;
    for (Point point : file_reader.get_graph_points()) {
        file << point.get_id() << " " << point.get_x() << " " << point.get_y() << endl;
    }
    file << "DEPOT_SECTION" << endl;
    file << "1" << endl;
    file << "-1" << endl;
    file << "EOF" << endl;
    file.close();
}