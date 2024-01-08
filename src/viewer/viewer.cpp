#include "viewer.hpp"

void Viewer::run(void *package) {
    Package* p = (Package*) package;
    string name = p->name;
    int width = p->width;
    int height = p->height;
    double range = p->range;
    Graph& graph = *p->graph;
    Solution& res = *p->solution;
    vector<Point>& points = *p->points;
    vector<Point>& graph_points = *p->graph_points;


    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(width, height), name, Style::Default, settings);
    window.setActive(false);
    window.setFramerateLimit(60);


    // activate the window's context
    window.setActive(true);

    // Pinta o fundo de branco
    window.clear(Color::White);

    // Cria a view
    View view = window.getDefaultView();

    // Define o tamanho da view
    view.setSize(window.getSize().x * 16.0f, window.getSize().y * 16.0f);

    // Define o centro da view
    Vector2f view_center = view.getCenter();
    view.setCenter(view_center.x, -(window.getSize().y * 2.0f));

    // Declara as variáveis de controle do efeito de arrastar
    Vector2f mouse_position, last_mouse_position;
    bool is_panning = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            // Se a tela for redimensionada, atualiza a view
            else if (event.type == Event::Resized) {
                view.setSize(event.size.width, event.size.height);
            }

            // Ao scrollar o mouse, dá zoom na view
            else if (event.type == Event::MouseWheelScrolled) {
                // obtém o fator de zoom
                float zoom_factor = 1 - event.mouseWheelScroll.delta * 0.1;

                // obtém o centro da view
                Vector2f view_center = view.getCenter();

                // obtém o tamanho da view
                Vector2f view_size = view.getSize();

                // atualiza o tamanho da view
                view.setSize(view_size * zoom_factor);

                // atualiza o centro da view
                view.setCenter(view_center);
            }

            // Ao pressionar a tecla R, reseta a view
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
                View view = window.getDefaultView();
                Vector2f view_center = view.getCenter();
                view.setCenter(view_center);
                window.setView(view);
            }

            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                // Iniciar o efeito de arrastar
                is_panning = true;
                last_mouse_position = Vector2f(Mouse::getPosition(window));
            }
            else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                // Parar o efeito de arrastar
                is_panning = false;
            }
        }

        if (is_panning) {
            // Atualizar a posição da view com base no movimento do mouse
            mouse_position = Vector2f(Mouse::getPosition(window));
            Vector2f delta = last_mouse_position - mouse_position;
            view.move(delta);
            last_mouse_position = mouse_position;
        }

        /* ===================== LIMPA A JANELA ===================== */
        window.clear(Color::White);


        /* ===================== DESENHA FORMAS ===================== */
        for (Point &p : points) {
            point_draw(window, p, 3, Color::Red);
        }
        solution_draw(window, res, graph_points, range);
        graph_draw(window, graph, graph_points);


        /* ===================== ATUALIZA A JANELA ===================== */
        window.setView(view);
        window.display();
    }
}

void Viewer::point_draw(RenderWindow &window, Point &point, double radius, Color color) {
    CircleShape shape(radius);
    shape.setFillColor(color);
    double dx = (point.get_x() - radius) * 1;
    double dy = (point.get_y() * -1) - radius;
    shape.setPosition(dx, dy);
    window.draw(shape);
}

void Viewer::graph_draw(RenderWindow &window, Graph &graph, vector<Point> &points) {
    for (int i = 0; i < graph.get_V(); i++) {
        for (const auto &to : graph.get_neighbors(i)) {
            Vertex line[2] = {
                Vertex(Vector2f(points[i].get_x(), points[i].get_y()*-1)),
                Vertex(Vector2f(points[to].get_x(), points[to].get_y()*-1))
            };
            line[0].color = Color::Black;
            line[1].color = Color::Black;
            window.draw(line, 2, Lines);
        }
    }
}

void Viewer::solution_draw(RenderWindow &window, Solution &solution, vector<Point> &graph_points, double range) {
    for (int i = 0; i < solution.get_n(); i++) {
        if (solution.get(i)) {
            Point &point = graph_points[i];
            point_draw(window, point, range, Color(0, 255, 0, 50));
            point_draw(window, point, 3, Color(0, 255, 0));
        }
    }
}
