#include "gui.h"
#include <iostream>
#include <numeric>

using namespace std;

GUI::GUI() {
    window.create(sf::VideoMode(1200, 800), "Cinema Management System");

    if (!font.loadFromFile("assets/monaco.ttf")) {
        cerr << "Error loading font!" << endl;
    }
}

void GUI::createButton(const string& label, float x, float y, float width, float height) {
    auto button = make_unique<sf::RectangleShape>(sf::Vector2f(width, height));
    button->setPosition(x, y);
    button->setFillColor(sf::Color::Green);  
    buttons.push_back(std::move(button));

    auto text = make_unique<sf::Text>();
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

vector<unique_ptr<sf::RectangleShape>>& GUI::getButtonShapes() {
    return buttons;
}

vector<unique_ptr<sf::Text>>& GUI::getButtonLabels() {
    return buttonLabels;
}

void GUI::setFont(const sf::Font& font) {
    this->font = font;
}

void GUI::displayBookingConfirmation(const string& message) {
    sf::Text confirmationText(message, font, 24);
    confirmationText.setPosition(400, 500);
    confirmationText.setFillColor(sf::Color::White);
    window.draw(confirmationText);
}
void GUI::createFoodMenuButton(const string& label, float x, float y, float width, float height) {
    auto button = make_unique<sf::RectangleShape>(sf::Vector2f(width, height));
    button->setPosition(x, y);
    button->setFillColor(sf::Color::Yellow);  
    buttons.push_back(std::move(button));

    auto text = make_unique<sf::Text>();
    text->setFont(font);
    text->setString(label);
    text->setCharacterSize(24);
    text->setFillColor(sf::Color::Black);
    text->setPosition(x + 10, y + 10);
    buttonLabels.push_back(std::move(text));
}

void GUI::displayTotalCost(float cost) {
    sf::Text totalCostText("Total Cost: $" + to_string(cost), font, 30);
    totalCostText.setPosition(400, 600);
    totalCostText.setFillColor(sf::Color::White);
    window.draw(totalCostText);
}

void GUI::createOrderButton(const string& label, float x, float y, float width, float height) {
    auto button = make_unique<sf::RectangleShape>(sf::Vector2f(width, height));
    button->setPosition(x, y);
    button->setFillColor(sf::Color::Blue);  
    buttons.push_back(std::move(button));

    auto text = make_unique<sf::Text>();
    text->setFont(font);
    text->setString(label);
    text->setCharacterSize(24);
    text->setFillColor(sf::Color::Black);
    text->setPosition(x + 10, y + 10);
    buttonLabels.push_back(std::move(text));
}

void GUI::displayFoodOrderMenu(const vector<string>& items, const vector<double>& prices) {
    for (size_t i = 0; i < items.size(); ++i) {
        cout << items[i] << " - " << prices[i] << " USD" << endl;
    }
    cout << "Total: " << accumulate(prices.begin(), prices.end(), 0.0) << " USD" << endl;
}