#include "graphic.hpp"

Graphic::Graphic(int x_pos, int y_pos, int graph_width, int graph_height)
: x_pos(x_pos), y_pos(y_pos), graph_width(graph_width), graph_height(graph_height) {
    graph.setPrimitiveType(LineStrip);
}

void Graphic::update(float new_data)  {
    data_matrix.push_back(new_data);
    float size = static_cast<float>(data_matrix.size());

    // Atualiza a amplitude máxima dos dados
    float max_amplitude = *max_element(data_matrix.begin(), data_matrix.end());
    float min_amplitude = *min_element(data_matrix.begin(), data_matrix.end());
    max_amplitude = max(abs(max_amplitude), abs(min_amplitude));

    // Calcula a escala para ajustar os dados ao tamanho da janela e à amplitude dos dados
    xScale = static_cast<float>(graph_width) / size;
    yScale = static_cast<float>(graph_height) * 2 / max_amplitude;
}

void Graphic::draw(RenderWindow& window) {
    // Pega o menor valor da matriz de dados
    float min = *min_element(data_matrix.begin(), data_matrix.end());

    // Pega o maior valor da matriz de dados
    float max = *max_element(data_matrix.begin(), data_matrix.end());

    // Desenha o retângulo que ficará em volta do gráfico
    RectangleShape rectangle(Vector2f(graph_width, graph_height));
    rectangle.setFillColor(Color::White);
    rectangle.setPosition(x_pos, y_pos);
    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor(Color::Black);
    window.draw(rectangle);

    // Desenha o gráfico
    // Adiciona novos pontos ao gráfico a partir da matriz de dados, escalando-os conforme necessário
    graph.clear();
    size_t n = data_matrix.size()-1;
    bool centralize = true;

    for (size_t i = 0; i < data_matrix.size(); ++i) {
        float x = static_cast<float>(i) * xScale + x_pos;
        float y = graph_height - (data_matrix[i] * yScale) + y_pos;

        // Aumenta a escala do eixo y, para que os dados fiquem mais visíveis, por serem pequenos
        // y *= 10;
        // y += graph_height / 2;

        if(centralize) {
            y += graph_height;
        }

        if(data_matrix[i] == min) {
            graph.append(Vertex(Vector2f(x, y), Color::Green));
            continue;
        }

        if(data_matrix[i] == max) {
            graph.append(Vertex(Vector2f(x, y), Color::Red));
            continue;
        }

        if(i == n) {
            graph.append(Vertex(Vector2f(x, y), Color::Red));
            continue;
        }

        graph.append(Vertex(Vector2f(x, y), Color::Black));
    }
    // Escreve o valor do último ponto no gráfico
    Text text;
    sf::Font font;
    font.loadFromFile("src/graphic/arial.ttf");
    text.setFont(font);
    text.setString(to_string(static_cast<int>(data_matrix[n])));
    text.setCharacterSize(70);
    text.setFillColor(Color::Black);

    float x = static_cast<float>(n) * xScale + x_pos + 35;
    float y = graph_height*2 - (data_matrix[n] * yScale) + y_pos;

    text.setPosition(Vector2f(x, y - 35));
    window.draw(text);

    // Desenha a linha horizontal que representa o menor valor da matriz de dados
    y = graph_height*2 - (min* yScale) + y_pos;
    Vertex line[2] = {
        Vertex(Vector2f(x_pos, y), Color::Green),
        Vertex(Vector2f(x_pos + graph_width, y), Color::Green)
    };
    window.draw(line, 2, Lines);

    // Escreve o valor do menor ponto no gráfico
    text.setString(to_string(static_cast<int>(min)));
    text.setPosition(Vector2f(x, y-35));
    window.draw(text);

    // Desenha a linha horizontal que representa o maior valor da matriz de dados
    y = graph_height*2 - (max* yScale) + y_pos;
    line[0] = Vertex(Vector2f(x_pos, y), Color::Red);
    line[1] = Vertex(Vector2f(x_pos + graph_width, y), Color::Red);
    window.draw(line, 2, Lines);

    // Escreve o valor do maior ponto no gráfico
    text.setString(to_string(static_cast<int>(max)));
    text.setPosition(Vector2f(x, y-35));
    window.draw(text);

    // Desenha o gráfico
    window.draw(graph);
}
