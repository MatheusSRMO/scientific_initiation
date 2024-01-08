#include "scp_file_reader.hpp"

ScpFileReader::ScpFileReader(string file_path) {
    this->file_path = file_path;
    this->name = "";
    this->dimension = 0;
    this->edges_dimension = 0;
    this->construction_dimension = 0;
    this->matrix = Matrix(0, 0);
    this->file_stream.open(this->file_path);
    if (!this->file_stream.is_open()) {
        cout << "Error opening file: " << this->file_path << endl;
        exit(1);
    }
}


ScpFileReader::~ScpFileReader() {
    this->file_stream.close();
}


void ScpFileReader::read_file() {
    string line;
    int dim_counter = 0;
    while (getline(this->file_stream, line)) {
        if (line.find("NAME") != string::npos) {
            this->name = line.substr(line.find(":") + 2);
        }
        else if(line.find("DIMENSION") != string::npos) {
            dim_counter++;
            if(dim_counter == 1)
                this->dimension = stoi(line.substr(line.find(":") + 2));
            else if(dim_counter == 2)
                this->edges_dimension = stoi(line.substr(line.find(":") + 2));
            else if(dim_counter == 3)
                this->construction_dimension = stoi(line.substr(line.find(":") + 2));
        }
        else if(line.find("NODE_COORD_SECTION") != string::npos) {
            for (int i = 0; i < this->dimension; i++) {
                getline(this->file_stream, line);
                int id = stoi(line.substr(0, line.find(" ")));
                double x = stod(line.substr(line.find(" ") + 1, line.find_last_of(" ")));
                double y = stod(line.substr(line.find_last_of(" ") + 1));
                this->graph_points.push_back(Point(id, x, y));
            }
        }
        else if(line.find("EDGES_SECTION") != string::npos) {
            this->graph = Graph(
                this->dimension,
                GraphType::DIRECTED,
                GraphRepresentation::ADJACENCY_LIST
            );
            for (int i = 0; i < this->edges_dimension; i++) {
                getline(this->file_stream, line);
                int id1 = stoi(line.substr(0, line.find(" "))) - 1;
                int id2 = stoi(line.substr(line.find(" ") + 1)) - 1;
                float weight = this->graph_points[id1].get_distance(this->graph_points[id2]);
                this->graph.add_edge(id1, id2, weight);
            }
        }
        else if(line.find("CONSTRUCTIONS_SECTION") != string::npos) {
            for (int i = 0; i < this->construction_dimension; i++) {
                getline(this->file_stream, line);
                int id = stoi(line.substr(0, line.find(" ")));
                double x = stod(line.substr(line.find(" ") + 1, line.find_last_of(" ")));
                double y = stod(line.substr(line.find_last_of(" ") + 1));
                this->construction_points.push_back(Point(id, x, y));
            }
        }

    }
}


string ScpFileReader::get_name() {
    return this->name;
}


int ScpFileReader::get_dimension() {
    return this->dimension;
}


int ScpFileReader::get_edges_dimension() {
    return this->edges_dimension;
}


int ScpFileReader::get_construction_dimension() {
    return this->construction_dimension;
}


Graph& ScpFileReader::get_graph() {
    return this->graph;
}

vector<Point>& ScpFileReader::get_graph_points() {
    return this->graph_points;
}

vector<Point>& ScpFileReader::get_construction_points() {
    return this->construction_points;
}

void ScpFileReader::calculate_coverage_matrix(double range) {
    this->matrix = Matrix(this->construction_dimension, this->dimension);
    for (int i = 0; i < this->construction_dimension; i++) {
        for (int j = 0; j < this->dimension; j++) {
            matrix.set(i, j, this->construction_points[i].get_distance(this->graph_points[j]) <= range);
        }
    }
}

Matrix& ScpFileReader::get_coverage_matrix() {
    return this->matrix;
}
