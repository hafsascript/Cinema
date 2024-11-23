#ifndef SEATING_H
#define SEATING_H

#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class Seating {
private:
    vector<vector<string>> seats;  
    int rows;
    int cols;

public:
    Seating(int rows, int cols);
    void displaySeats(sf::RenderWindow& window, float startX, float startY, float seatWidth, float seatHeight, float padding);
    bool handleSeatSelection(sf::Event& event, float startX, float startY, float seatWidth, float seatHeight, float padding);
    bool bookSeat(int row, int col);
    bool isSeatAvailable(int row, int col) const;
    void printSeats();  
    void testDisplay(sf::RenderWindow& window);
};

#endif

