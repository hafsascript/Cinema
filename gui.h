#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>  

class GUI {
private:
    sf::RenderWindow window;
    std::vector<std::unique_ptr<sf::RectangleShape>> buttons;  
    std::vector<std::unique_ptr<sf::Text>> buttonLabels;      
    sf::Font font;                                           
public:
    GUI();
    void createButton(const std::string& label, float x, float y, float width, float height);
    void display();
    bool isButtonPressed(const sf::RectangleShape& button, sf::Event& event);
    sf::RenderWindow& getWindow();
    std::vector<std::unique_ptr<sf::RectangleShape>>& getButtonShapes();  
    std::vector<std::unique_ptr<sf::Text>>& getButtonLabels();            
};

#endif

