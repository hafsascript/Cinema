#include "gui.h"
#include <iostream>

GUI::GUI() {
    
    window.create(sf::VideoMode(800, 600), "Cinema Management System");

    
    if (!font.loadFromFile("assets/monaco.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
}

void GUI::createButton(const std::string& label, float x, float y, float width, float height) {
    
    auto button = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height));
    button->setPosition(x, y);
    button->setFillColor(sf::Color::Green);  
    buttons.push_back(std::move(button));

    
    auto text = std::make_unique<sf::Text>();
    text->setFont(font);
    text->setString(label);
    text->setCharacterSize(24);
    text->setFillColor(sf::Color::Black);
    text->setPosition(x + 10, y + 10); 
    buttonLabels.push_back(std::move(text));
}

void GUI::display() {
    window.clear();

    
    for (size_t i = 0; i < buttons.size(); ++i) {
        window.draw(*buttons[i]);          
        window.draw(*buttonLabels[i]);     
    }

    window.display();
}

bool GUI::isButtonPressed(const sf::RectangleShape& button, sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (button.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
            return true;
        }
    }
    return false;
}

sf::RenderWindow& GUI::getWindow() {
    return window;
}

std::vector<std::unique_ptr<sf::RectangleShape>>& GUI::getButtonShapes() {
    return buttons;
}

std::vector<std::unique_ptr<sf::Text>>& GUI::getButtonLabels() {
    return buttonLabels;
}

