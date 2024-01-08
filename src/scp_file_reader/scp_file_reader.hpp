#ifndef SCP_FILE_READER_HPP
#define SCP_FILE_READER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../graph/graph.hpp"
#include "../point/point.hpp"
#include "../matrix/matrix.hpp"

using namespace std;


class ScpFileReader {
    private:
        string file_path;
        string name;
        int dimension;
        int edges_dimension;
        int construction_dimension;
        ifstream file_stream;
        Graph graph;
        Matrix matrix;
        vector<Point> graph_points;
        vector<Point> construction_points;
    public:
        ScpFileReader(string file_path);
        ~ScpFileReader();

        void read_file();

        string get_name();
        int get_dimension();
        int get_edges_dimension();
        int get_construction_dimension();
        Graph& get_graph();
        vector<Point>& get_graph_points();
        vector<Point>& get_construction_points();
        void calculate_coverage_matrix(double range);
        Matrix& get_coverage_matrix();
};

#endif // SCP_FILE_READER_HPP