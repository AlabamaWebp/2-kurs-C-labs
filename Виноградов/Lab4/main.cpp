#include <SFML/Graphics.hpp>
// #include "Triangle.h"
// #include "Rectangle.h"
// Подключите остальные классы фигур

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Math Objects and Shapes");

    // Пример использования фигуры Треугольник
    // Triangle triangle(300, 200);
    // triangle.move(100, 100);
    // triangle.rotate(45);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}
