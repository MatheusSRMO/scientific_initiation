#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <valarray>

using namespace std;
using namespace sf;

class Graphic {
    private:
        int x_pos;
        int y_pos;
        int graph_width;
        int graph_height;
        VertexArray graph;
        vector<float> data_matrix;

        float xScale;
        float yScale;

    public:
        Graphic(int x_pos, int y_pos, int graph_width, int graph_height);

        void update(float new_data);

        void draw(RenderWindow& window);
};

#endif // GRAPHIC_HPP