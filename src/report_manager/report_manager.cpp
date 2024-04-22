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
