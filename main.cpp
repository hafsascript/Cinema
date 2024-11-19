#include <iostream>
#include <vector>
#include "movie.h"
#include "gui.h"
#include "seating.h"

using namespace std;

void showAdminOptions(GUI& gui) {
    gui.createButton("Add Movie", 50, 50, 200, 50);
    gui.createButton("Remove Movie", 50, 120, 200, 50);
    gui.createButton("Save Movies", 50, 190, 200, 50);
    gui.createButton("Load Movies", 50, 260, 200, 50);
    gui.createButton("Exit", 50, 330, 200, 50);
}

void showCustomerOptions(GUI& gui, vector<Movie*>& movieList) {
    string filename = "movies.txt"; 
    Movie::loadMoviesFromFile(movieList, filename);

    if (movieList.empty()) {
        gui.createButton("No Movies Available", 50, 50, 500, 50);
    } else {
        for (size_t i = 0; i < movieList.size(); ++i) {
            gui.createButton(movieList[i]->getTitle(), 50, 50 + (i * 70), 500, 50);
        }
    }

    gui.createButton("Exit", 50, 50 + (movieList.size() * 50) + 70, 200, 50);
}

void handleAdminActions(GUI& gui, sf::Event& event, vector<Movie*>& movieList) {
    for (size_t i = 0; i < gui.getButtonShapes().size(); ++i) {
        if (gui.isButtonPressed(*gui.getButtonShapes()[i], event)) {
            switch (i) {
                case 0: {
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
                    break;
                }

                case 1: {
                    string title;
                    cout << "Enter movie title to remove: ";
                    getline(cin, title);
                    Movie::removeMovie(movieList, title);
                    break;
                }

                case 2: {
                    string filename;
                    cout << "Enter filename to save movies (e.g., movies.txt): ";
                    getline(cin, filename);
                    Movie::saveMoviesToFile(movieList, filename);
                    break;
                }

                case 3: {
                    string filename;
                    cout << "Enter filename to load movies (e.g., movies.txt): ";
                    getline(cin, filename);
                    Movie::loadMoviesFromFile(movieList, filename);
                    break;
                }

                case 4:
                    gui.getWindow().close();
                    break;
            }
        }
    }
}

void handleCustomerActions(GUI& gui, sf::Event& event, vector<Movie*>& movieList, Seating& seating) {
    for (size_t i = 0; i < gui.getButtonShapes().size(); ++i) {
        if (gui.isButtonPressed(*gui.getButtonShapes()[i], event)) {
            if (i == movieList.size()) {
                gui.getWindow().close(); 
            } else {
                Movie* selectedMovie = movieList[i];

                
                vector<string> showtimes = selectedMovie->getShowtimes();
                int showtimeChoice = -1;
                cout << "Select a showtime for \"" << selectedMovie->getTitle() << "\":" << endl;

               
                for (size_t j = 0; j < showtimes.size(); ++j) {
                    cout << j + 1 << ". " << showtimes[j] << endl;
                }

                
                cout << "Enter showtime number: ";
                cin >> showtimeChoice;
                cin.ignore();

                if (showtimeChoice < 1 || showtimeChoice > showtimes.size()) {
                    cout << "Invalid showtime choice!" << endl;
                } else {
                    cout << "You selected showtime: " << showtimes[showtimeChoice - 1] << endl;

                    
                    bool seatSelected = false;
                    while (!seatSelected && gui.getWindow().isOpen()) {
                        while (gui.getWindow().pollEvent(event)) {
                            if (event.type == sf::Event::Closed) {
                                gui.getWindow().close();
                                return;
                            }
                            if (event.type == sf::Event::MouseButtonPressed) {
                                
                                seatSelected = seating.handleSeatSelection(event, 50, 250, 40, 40, 10);
                                if (seatSelected) {
                                    cout << "Seat booked successfully!" << endl;
                                }
                            }
                        }

                        
                        gui.getWindow().clear();
                        seating.displaySeats(gui.getWindow(), 50, 250, 40, 40, 10);
                        gui.getWindow().display();
                    }
                }
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
        showCustomerOptions(gui, movieList); 
    }

    Seating seating(5, 5);  

    sf::Event event;
    while (gui.getWindow().isOpen()) {
        while (gui.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gui.getWindow().close();
            }

            if (userChoice == "admin") {
                handleAdminActions(gui, event, movieList); 
            } else if (userChoice == "customer") {
                handleCustomerActions(gui, event, movieList, seating);  
            }
        }

        gui.display();  
    }

    
    for (auto movie : movieList) {
        delete movie;
    }

    return 0;
}















