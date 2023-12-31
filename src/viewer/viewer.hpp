#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../graph/graph.hpp"
#include "../point/point.hpp"
#include "../solution/solution.hpp"

using namespace std;
using namespace sf;


struct Package {
    string name;
    int width;
    int height;
    double range;
    Graph* graph;
    Solution* solution;
    vector<Point>* points;
    vector<Point>* graph_points;

    Package(
        string name,
        int width,
        int height,
        double range,
        Graph* graph,
        Solution* solution,
        vector<Point>* points,
        vector<Point>* graph_points
    ) {
        this->name = name;
        this->width = width;
        this->height = height;
        this->range = range;
        this->graph = graph;
        this->solution = solution;
        this->points = points;
        this->graph_points = graph_points;
    }
};



class Viewer {
    public:
        static void run(void *package);
        static void point_draw(RenderWindow &window, Point &point, double radius, Color color);
        static void graph_draw(RenderWindow &window, Graph &graph, vector<Point> &points);
        static void solution_draw(RenderWindow &window, Solution &solution, vector<Point> &graph_points, double range);
};


#endif // VIEWER_HPP