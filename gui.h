#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory> 

using namespace std;

class GUI {
private:
    sf::RenderWindow window;
    vector<unique_ptr<sf::RectangleShape>> buttons;  
    vector<unique_ptr<sf::Text>> buttonLabels;      
    sf::Font font;                                           

public:
    GUI();
    void createButton(const string& label, float x, float y, float width, float height);
    void display();
    bool isButtonPressed(const sf::RectangleShape& button, sf::Event& event);
    sf::RenderWindow& getWindow();
    vector<unique_ptr<sf::RectangleShape>>& getButtonShapes();  
    vector<unique_ptr<sf::Text>>& getButtonLabels();
    void setFont(const sf::Font& font);
    void displayBookingConfirmation(const string& message);
};

#endif


