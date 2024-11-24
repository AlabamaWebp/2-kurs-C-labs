#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "vector.h"

void setupText(sf::Text& text, const sf::Font& font, const std::string& str, unsigned int size, float x, float y, sf::Color color = sf::Color::White) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setPosition(x, y);
    text.setFillColor(color);
}

void handleInput(const sf::Event& event, sf::Text& inputField, bool vectorSelected, Vector*& vector) {
    if (event.type == sf::Event::TextEntered && vectorSelected) {
        if (event.text.unicode == '\b' && inputField.getString().getSize() > 0) {
            std::string str = inputField.getString();
            str.pop_back();
            inputField.setString(str);
        } else if (event.text.unicode < 128 && event.text.unicode != '\b') {
            inputField.setString(inputField.getString() + static_cast<char>(event.text.unicode));
        }
    }
}

Vector* createVectorFromInput(const sf::Text& inputField) {
    std::istringstream iss(inputField.getString().toAnsiString());
    std::vector<double> elements;
    double value;
    while (iss >> value) {
        elements.push_back(value);
    }
    Vector* vector = new Vector(elements.size());
    for (size_t i = 0; i < elements.size(); ++i) {
        (*vector)[i] = elements[i];
    }
    return vector;
}

void displayVector(sf::RenderWindow& window, Vector* vector, const sf::Text& vectorOutput) {
    // Отрисовка вектора
    sf::VertexArray lines(sf::LinesStrip, vector->size);
    float centerX = window.getSize().x / 2;
    float centerY = window.getSize().y / 2;
    for (int i = 0; i < vector->size; ++i) {
        lines[i].position = sf::Vector2f(centerX + (*vector)[i], centerY - (*vector)[i]);
        lines[i].color = sf::Color::Red;
    }
    window.draw(lines);
    window.draw(vectorOutput);
}

void setupExitButton(sf::Text& exitButton, const sf::Font& font) {
    setupText(exitButton, font, "Exit to Menu", 20, 350, 500, sf::Color::Blue);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Math Objects Interface");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }

    sf::Text title;
    setupText(title, font, "Select Math Object", 30, 300, 50);

    sf::RectangleShape vectorButton(sf::Vector2f(200, 50));
    vectorButton.setPosition(300, 200);
    vectorButton.setFillColor(sf::Color::Green);

    sf::Text vectorButtonText;
    setupText(vectorButtonText, font, "Vector", 20, 370, 215);

    sf::Text inputPrompt;
    setupText(inputPrompt, font, "Enter vector elements separated by space:", 20, 50, 300, sf::Color::Transparent);

    sf::Text inputField;
    setupText(inputField, font, "", 20, 50, 350, sf::Color::Transparent);

    sf::RectangleShape displayButton(sf::Vector2f(200, 50));
    displayButton.setPosition(300, 400);
    displayButton.setFillColor(sf::Color::Transparent);

    sf::Text displayButtonText;
    setupText(displayButtonText, font, "Display", 20, 370, 415, sf::Color::Transparent);

    sf::Text vectorOutput;
    setupText(vectorOutput, font, "", 20, 600, 50, sf::Color::White);

    sf::Text exitButton;
    setupExitButton(exitButton, font);

    bool vectorSelected = false;
    bool vectorDisplayed = false;
    Vector* vector = nullptr;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (vectorButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    vectorSelected = true;
                    inputPrompt.setFillColor(sf::Color::White);
                    inputField.setFillColor(sf::Color::White);
                    displayButton.setFillColor(sf::Color::Blue);
                    displayButtonText.setFillColor(sf::Color::White);
                } else if (displayButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    if (vector) {
                        delete vector;
                    }
                    vector = createVectorFromInput(inputField);
                    vectorOutput.setString("Vector: " + vector->toString());
                    vectorDisplayed = true;
                } else if (exitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    vectorSelected = false;
                    vectorDisplayed = false;
                    inputPrompt.setFillColor(sf::Color::Transparent);
                    inputField.setFillColor(sf::Color::Transparent);
                    displayButton.setFillColor(sf::Color::Transparent);
                    displayButtonText.setFillColor(sf::Color::Transparent);
                    vectorOutput.setString("");
                    delete vector;
                    vector = nullptr;
                }
            }
            handleInput(event, inputField, vectorSelected, vector);
        }

        window.clear();
        if (!vectorSelected) {
            window.draw(title);
            window.draw(vectorButton);
            window.draw(vectorButtonText);
        } else {
            window.draw(inputPrompt);
            window.draw(inputField);
            window.draw(displayButton);
            window.draw(displayButtonText);
            window.draw(exitButton);
            if (vectorDisplayed && vector) {
                displayVector(window, vector, vectorOutput);
            }
        }
        window.display();
    }

    delete vector;
    return 0;
}
