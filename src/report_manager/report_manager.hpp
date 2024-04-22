#if !defined REPORT_MANAGER_HPP
#define REPORT_MANAGER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


#include "../solution/solution.hpp"

using namespace std;

class ReportManager {
    private:
        string file_name; // name of the file to write the report
        vector<Point> points; // points to be plotted in the graphic
        int iterations; // number of iterations

    public:
        /**
         * @brief Constructs a new ReportManager object.
         */
        ReportManager();

        /**
         * @brief Constructs a new ReportManager object.
         * 
         * @param file_name The name of the file to write the report.
         */
        ReportManager(string file_name);

        /**
         * @brief Adds a partial solution to the report manager.
         * 
         * This function adds a partial solution to the report manager. The partial solution
         * is represented by the `solution` parameter.
         * 
         * @param solution The partial solution to be added.
         */
        void add_partial_solution(Solution solution);

        /**
         * @brief Writes the report to the file.
         * 
         * This function writes the report to the file. The report contains the points
         * added to the report manager.
         */
        void write_report();

};

#endif // REPORT_MANAGER_HPP