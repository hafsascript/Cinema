#include <iostream>
#include <vector>
#include "movie.h"
#include "gui.h"

using namespace std;

void showAdminOptions(GUI& gui) {
    gui.createButton("Add Movie", 50, 50, 200, 50);
    gui.createButton("Remove Movie", 50, 120, 200, 50);
    gui.createButton("Exit", 50, 190, 200, 50);
}

void showCustomerOptions(GUI& gui) {
    gui.createButton("Book Ticket", 50, 50, 200, 50);
    gui.createButton("Exit", 50, 120, 200, 50);
}

void handleAdminActions(GUI& gui, sf::Event& event, vector<Movie*>& movieList) {
    for (size_t i = 0; i < gui.getButtonShapes().size(); ++i) {
        if (gui.isButtonPressed(*gui.getButtonShapes()[i], event)) {
            switch (i) {
                case 0:  
                    {
                        string title, genre, leadCast;
                        int duration;
                        vector<string> showtimes;
                        cout << "Enter movie title: ";
                        getline(cin, title);
                        cout << "Enter movie genre: ";
                        getline(cin, genre);
                        cout << "Enter movie lead cast: ";
                        getline(cin, leadCast);
                        cout << "Enter movie duration (in minutes): ";
                        cin >> duration;
                        cin.ignore();  
                        
                        cout << "Enter showtimes (enter 'done' to stop):" << endl;
                        string showtime;
                        while (true) {
                            cout << "Showtime: ";
                            getline(cin, showtime);
                            if (showtime == "done") break;
                            showtimes.push_back(showtime);
                        }

                        Movie::addMovie(movieList, title, genre, showtimes, duration, leadCast);
                    }
                    break;
                case 1:  
                    {
                        string title;
                        cout << "Enter movie title to remove: ";
                        getline(cin, title);
                        Movie::removeMovie(movieList, title);
                    }
                    break;
                case 2:  
                    gui.getWindow().close();
                    break;
            }
        }
    }
}

void handleCustomerActions(GUI& gui, sf::Event& event) {
    for (size_t i = 0; i < gui.getButtonShapes().size(); ++i) {
        if (gui.isButtonPressed(*gui.getButtonShapes()[i], event)) {
            switch (i) {
                case 0:  
                    cout << "Customer: Book Ticket functionality." << endl;
                    
                    break;
                case 1:  
                    gui.getWindow().close();
                    break;
            }
        }
    }
}

int main() {
    GUI gui;
    vector<Movie*> movieList;  

    
    string userChoice;
    cout << "Are you an Admin or a Customer? (Enter 'admin' or 'customer'):" << endl;
    cin >> userChoice;
    cin.ignore();  

    if (userChoice != "admin" && userChoice != "customer") {
        cout << "Invalid choice. Exiting program." << endl;
        return 1;
    }

    
    if (userChoice == "admin") {
        showAdminOptions(gui);
    } else if (userChoice == "customer") {
        showCustomerOptions(gui);
    }

    
    sf::Event event;
    while (gui.getWindow().isOpen()) {
        while (gui.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gui.getWindow().close();
            }

            // Handle actions for Admin or Customer
            if (userChoice == "admin") {
                handleAdminActions(gui, event, movieList);
            } else if (userChoice == "customer") {
                handleCustomerActions(gui, event);
            }
        }

        
        gui.display();
    }

    
    for (auto movie : movieList) {
        delete movie;  
    }

    return 0;
}







