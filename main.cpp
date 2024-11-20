#include <iostream>
#include <vector>
#include "movie.h"
#include "gui.h"
#include "seating.h"

using namespace std;
string lastSavedFile = "default_movies.txt"; 

void showAdminOptions(GUI& gui) {
    gui.createButton("Add Movie", 50, 50, 200, 50);
    gui.createButton("Remove Movie", 50, 120, 200, 50);
    gui.createButton("Save Movies", 50, 190, 200, 50);
    gui.createButton("Load Movies", 50, 260, 200, 50);
    gui.createButton("Exit", 50, 330, 200, 50);
}

void showCustomerOptions(GUI& gui, vector<Movie*>& movieList) {
    if (movieList.empty()) {
        Movie::loadMoviesFromFile(movieList, lastSavedFile); // Automatically load default file
    }

    if (movieList.empty()) {
        gui.createButton("No Movies Available", 50, 50, 500, 50);
    } else {
        for (size_t i = 0; i < movieList.size(); ++i) {
            gui.createButton(movieList[i]->getTitle(), 50, 50 + (i * 70), 500, 50);
        }
    }

    gui.createButton("Exit", 50, 50 + (movieList.size() * 70) + 70, 200, 50);
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

                case 2: { // Save Movies
                    Movie::saveMoviesToFile(movieList, lastSavedFile);
                    cout << "Movies saved to " << lastSavedFile << "!" << endl;
                    break;
                }
                case 3: { // Load Movies
                    Movie::loadMoviesFromFile(movieList, lastSavedFile);
                    cout << "Movies loaded from " << lastSavedFile << "!" << endl;
                    break;
                }
                case 4:
                    gui.getWindow().close();
                    return;
            }
        }
    }
}

void handleCustomerActions(GUI& gui, sf::Event& event, vector<Movie*>& movieList, Seating& seating) {
    for (size_t i = 0; i < gui.getButtonShapes().size(); ++i) {
        if (gui.isButtonPressed(*gui.getButtonShapes()[i], event)) {
            if (i == movieList.size()) {
                cout << "Thank you for visiting! Generating ticket placeholder...\n";
                gui.getWindow().close();
                return;
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
                    string selectedShowtime = showtimes[showtimeChoice - 1];
                    cout << "You selected showtime: " << selectedShowtime << endl;

                    Seating* seatingForShowtime = selectedMovie->getSeatingForShowtime(selectedShowtime);

                    if (seatingForShowtime) {
                        bool seatSelected = false;
                        while (!seatSelected && gui.getWindow().isOpen()) {
                            while (gui.getWindow().pollEvent(event)) {
                                if (event.type == sf::Event::Closed) {
                                    gui.getWindow().close();
                                    return;
                                }
                                if (event.type == sf::Event::MouseButtonPressed) {
                                    seatSelected = seatingForShowtime->handleSeatSelection(event, 50, 250, 40, 40, 10);
                                    if (seatSelected) {
                                        cout << "Seat booked successfully!" << endl;
                                    }
                                }
                            }

                            gui.getWindow().clear();
                            seatingForShowtime->displaySeats(gui.getWindow(), 50, 250, 40, 40, 10);
                            gui.getWindow().display();
                        }
                    } else {
                        cout << "No seating arrangement found for this showtime." << endl;
                    }
                }
            }
        }
    }
}

int main() {
    vector<Movie*> movieList;

    bool running = true;

    while (running) {
        string userChoice;
        cout << "Are you an Admin or a Customer? (Enter 'admin', 'customer', or 'exit'):" << endl;
        cin >> userChoice;
        cin.ignore();

        if (userChoice == "admin") {
            GUI gui; 
            showAdminOptions(gui);

            sf::Event event;
            while (gui.getWindow().isOpen()) {
                while (gui.getWindow().pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        gui.getWindow().close();
                        break;
                    }

                    handleAdminActions(gui, event, movieList);
                }

                gui.display();
            }
        } else if (userChoice == "customer") {
            GUI gui;
            showCustomerOptions(gui, movieList);

            Seating seating(5, 5);
            sf::Event event;
            while (gui.getWindow().isOpen()) {
                while (gui.getWindow().pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        gui.getWindow().close();
                        break;
                    }

                    handleCustomerActions(gui, event, movieList, seating);
                }

                gui.display();
            }
        } else if (userChoice == "exit") {
            running = false;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    for (auto movie : movieList) {
        delete movie;
    }

    return 0;
}

















