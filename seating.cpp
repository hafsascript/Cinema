#include "seating.h"
#include <iostream>

using namespace std;

Seating::Seating(int rows, int cols) : rows(rows), cols(cols) {
    seats.resize(rows, vector<string>(cols, "O"));  
}

void Seating::displaySeats(sf::RenderWindow& window, float startX, float startY, float seatWidth, float seatHeight, float padding) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            
            sf::RectangleShape seat(sf::Vector2f(seatWidth, seatHeight));
            seat.setPosition(startX + j * (seatWidth + padding), startY + i * (seatHeight + padding));

            
            if (seats[i][j] == "X") {
                seat.setFillColor(sf::Color::Red);  
            } else {
                seat.setFillColor(sf::Color::Green);  
            }

            window.draw(seat);  

            
            sf::Font font;
            if (!font.loadFromFile("assets/monaco.ttf")) {
                cerr << "Error loading font!" << endl;
                return;
            }

            sf::Text text(seats[i][j], font, 20);
            text.setFillColor(sf::Color::Black);
            text.setPosition(startX + j * (seatWidth + padding) + seatWidth / 4, startY + i * (seatHeight + padding) + seatHeight / 4);
            window.draw(text);  
        }
    }
}

bool Seating::handleSeatSelection(sf::Event& event, float startX, float startY, float seatWidth, float seatHeight, float padding) {
    if (event.type == sf::Event::MouseButtonPressed) {
        float mouseX = event.mouseButton.x;
        float mouseY = event.mouseButton.y;

        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                float seatLeft = startX + j * (seatWidth + padding);
                float seatTop = startY + i * (seatHeight + padding);

                if (mouseX >= seatLeft && mouseX <= seatLeft + seatWidth && mouseY >= seatTop && mouseY <= seatTop + seatHeight) {
                    if (seats[i][j] == "O") {  
                        seats[i][j] = "X";  
                        cout << "Seat at (" << i << ", " << j << ") booked!" << endl;
                        return true;
                    } else {
                        cout << "Seat already booked!" << endl;
                        return false;
                    }
                }
            }
        }
    }
    return false;
}

bool Seating::bookSeat(int row, int col) {
    if (seats[row][col] == "O") {
        seats[row][col] = "X";
        return true;
    }
    return false;
}

bool Seating::isSeatAvailable(int row, int col) const {
    return seats[row][col] == "O";
}

void Seating::printSeats() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << seats[i][j] << " ";
        }
        cout << endl;
    }
}
void Seating::testDisplay(sf::RenderWindow& window) {
    sf::RectangleShape seat(sf::Vector2f(100, 100));  
    seat.setPosition(100, 100);  

    seat.setFillColor(sf::Color::Green);  

    window.draw(seat); 

    
    sf::Font font;
    if (!font.loadFromFile("assets/monaco.ttf")) {
        cerr << "Error loading font!" << endl;
    }

    sf::Text text("Seat", font, 20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(120, 120);  

    window.draw(text);  
}


