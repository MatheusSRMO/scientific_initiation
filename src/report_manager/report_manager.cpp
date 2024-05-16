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

void ReportManager::add_partial_solution(Solution &solution, int iteration) {
    Point point = Point(iteration, solution.get_fitness_score());
    this->points.push_back(point);
}

void ReportManager::write_report() {
    ofstream file(this->file_name);
    if (!file.is_open()) {
        cout << "Error: could not open file " << this->file_name << endl;
        return;
    }
    file << "x y" << endl;
    for (Point point : this->points) {
        file << point.get_x() << " " << point.get_y() << endl;
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
void ReportManager::write_cvrp_intance(ScpFileReader &file_reader, string file_name, Solution &solution) {
    ofstream file(file_name);
    if (!file.is_open()) {
        cout << "Error: could not open file " << file_name << endl;
        return;
    }
    file << "NAME : " << file_reader.get_name() << endl;
    file << "COMMENT : " << "ARQUIVO TESTE" << endl;
    file << "TYPE : " << "CVRP" << endl;
    file << "DIMENSION : " << solution.get_fitness_score() << endl;
    file << "EDGE_WEIGHT_TYPE : " << "EUC_2D" << endl;
    file << "NODE_COORD_SECTION" << endl;

    // matriz de distâncias
    vector<vector<double>> distances = vector<vector<double>>(
        solution.get_fitness_score(),
        vector<double>(solution.get_fitness_score(), 0)
    );

    // vetor com os pontos selecionados
    vector<Point> points = vector<Point>();
    
    // grafo
    Graph &graph = file_reader.get_graph();
    
    // escreve os pontos e calcula as distâncias
    int i = 0;
    for (Point &point : file_reader.get_graph_points()) {
        if(solution.get(i++)){
            file << point.get_id() << " " << point.get_x() << " " << point.get_y() << endl;
            points.push_back(point);
        }
    }

    // printa os pontos
    for (Point &point : points) {
        cout << point.get_id() << " " << point.get_x() << " " << point.get_y() << endl;
    }

    // calcula as distâncias de todos os pontos até todos os outros
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j <= i; j++) {
            distances[i][j] = graph.get_min_distance(
                points[i].get_id()-1,
                points[j].get_id()-1
            );
        }
    }

    // printa a matriz de distâncias
    for (int i = 0; i < solution.get_fitness_score(); i++) {
        for (int j = 0; j < i; j++) {
            cout << distances[i][j] << " ";
        }
        cout << endl;
    }

    // // escreve as distâncias
    // file << "EDGE_WEIGHT_SECTION" << endl;
    // for (int i = 0; i < solution.get_fitness_score(); i++) {
    //     for (int j = 0; j < i; j++) {
    //         file << distances[i][j] << " ";
    //     }
    //     file << endl;
    // }

    file << "DEPOT_SECTION" << endl;
    file << "1" << endl;
    file << "-1" << endl;
    file << "EOF" << endl;
    file.close();
}