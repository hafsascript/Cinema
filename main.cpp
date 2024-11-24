#include <iostream>
#include <vector>
#include "movie.h"
#include "gui.h"
#include "seating.h"
#include "fooditem.h"
#include "receipt.h"
#include "report.h"

using namespace std;
string lastSavedFile = "default_movies.txt";

vector<FoodItem> foodMenu;

void showAdminOptions(GUI& gui) {
    gui.createButton("Add Movie", 50, 50, 200, 50);
    gui.createButton("Remove Movie", 50, 120, 200, 50);
    gui.createButton("Add Food Item", 50, 190, 200, 50);
    gui.createButton("Save Movies", 50, 260, 200, 50);
    gui.createButton("Load Movies", 50, 330, 200, 50);
    gui.createButton("Exit", 50, 400, 200, 50);
    gui.createButton("Generate Report", 50, 500, 200, 50);
}

void showCustomerOptions(GUI& gui, vector<Movie*>& movieList) {
    if (movieList.empty()) {
        Movie::loadMoviesFromFile(movieList, lastSavedFile); 
    }

    if (movieList.empty()) {
        gui.createButton("No Movies Available", 50, 50, 500, 50);
    } else {
        for (size_t i = 0; i < movieList.size(); ++i) {
            gui.createButton(movieList[i]->getTitle(), 50, 50 + (i * 70), 500, 50);
        }
    }

    gui.createButton("View Menu", 50, 50 + (movieList.size() * 70) + 70, 200, 50);
    gui.createButton("Exit", 50, 50 + (movieList.size() * 70) + 140, 200, 50);
}

void handleAdminActions(GUI& gui, sf::Event& event, vector<Movie*>& movieList,Report& report) {
    for (size_t i = 0; i < gui.getButtonShapes().size(); ++i) {
        if (gui.isButtonPressed(*gui.getButtonShapes()[i], event)) {
            switch (i) {
                case 0: {
                    string title, genre, leadCast;
                    int duration;
                    vector<string> showtimes;
                    float ticketPrice;

                    cout << "Enter movie title: ";
                    getline(cin, title);
                    cout << "Enter movie genre: ";
                    getline(cin, genre);
                    cout << "Enter movie lead cast: ";
                    getline(cin, leadCast);
                    cout << "Enter movie duration (in minutes): ";
                    cin >> duration;
                    cin.ignore();
                    cout << "Enter ticket price: ";
                    cin >> ticketPrice;
                    cin.ignore();

                    cout << "Enter showtimes (enter 'done' to stop):" << endl;
                    string showtime;
                    while (true) {
                        cout << "Showtime: ";
                        getline(cin, showtime);
                        if (showtime == "done") break;
                        showtimes.push_back(showtime);
                    }

                    Movie::addMovie(movieList, title, genre, showtimes, duration, leadCast, ticketPrice);
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
                    string name;
                    float price;

                    cout << "Enter food item name: ";
                    getline(cin, name);
                    cout << "Enter food item price: ";
                    cin >> price;
                    cin.ignore();

                    foodMenu.push_back(FoodItem(name, price));
                    cout << "Food item added successfully!" << endl;
                    break;
                }

                case 3: {
                    Movie::saveMoviesToFile(movieList, lastSavedFile);
                    cout << "Movies saved to " << lastSavedFile << "!" << endl;
                    break;
                }

                case 4: {
                    Movie::loadMoviesFromFile(movieList, lastSavedFile);
                    cout << "Movies loaded from " << lastSavedFile << "!" << endl;
                    break;
                }

                case 5:
                    gui.getWindow().close();
                    return;
                case 6: // Generate Report
                    report.generateReport(movieList);
                    break;
            }
        }
    }
}

void handleCustomerActions(GUI& gui, sf::Event& event, vector<Movie*>& movieList, Seating& seating, Receipt& receipt,Report& report) {
    bool seatSelected = false;
    bool foodOrderCompleted = false;

    for (size_t i = 0; i < gui.getButtonShapes().size(); ++i) {
        if (gui.isButtonPressed(*gui.getButtonShapes()[i], event)) {
           
            if (i < movieList.size()) {
                Movie* selectedMovie = movieList[i];
                vector<string> showtimes = selectedMovie->getShowtimes();

                if (showtimes.empty()) {
                    cout << "No showtimes available for this movie." << endl;
                    continue;
                }

                int showtimeChoice = -1;
                cout << "Select a showtime for \"" << selectedMovie->getTitle() << "\":" << endl;
                for (size_t j = 0; j < showtimes.size(); ++j) {
                    cout << j + 1 << ". " << showtimes[j] << endl;
                }

                cout << "Enter showtime number: ";
                while (!(cin >> showtimeChoice) || showtimeChoice < 1 || showtimeChoice > showtimes.size()) {
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice. Enter a valid showtime number: ";
                }
                cin.ignore();

                string selectedShowtime = showtimes[showtimeChoice - 1];
                Seating* seatingForShowtime = selectedMovie->getSeatingForShowtime(selectedShowtime);

                if (seatingForShowtime) {
                    
                    while (!seatSelected) {
                        while (gui.getWindow().pollEvent(event)) {
                            if (event.type == sf::Event::Closed) {
                                gui.getWindow().close();
                                return;
                            }
                            if (event.type == sf::Event::MouseButtonPressed) {
                                seatSelected = seatingForShowtime->handleSeatSelection(event, 50, 250, 40, 40, 10);
                                if (seatSelected) {
                                    receipt.addTicket(selectedMovie->getTitle(), selectedMovie->getTicketPrice(), 1);
                                    cout << "Seat booked successfully! Ticket price: $" << selectedMovie->getTicketPrice() << endl;
                                    
                                    report.recordTicketSale(selectedMovie->getTitle(), 1, selectedMovie->getTicketPrice());

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
           
            else if (i == movieList.size()) {
                while (!foodOrderCompleted) {
                    cout << "\n--- Food Menu ---" << endl;
                    if (foodMenu.empty()) {
                        cout << "No food items available." << endl;
                        break;
                    }
                    for (size_t j = 0; j < foodMenu.size(); ++j) {
                        cout << j + 1 << ". " << foodMenu[j].getName() << " - $" << foodMenu[j].getPrice() << endl;
                    }
                    cout << "Enter item number to order or 0 to finish: ";
                    int choice;
                    if (!(cin >> choice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid choice. Try again." << endl;
                        continue;
                    }
                    if (choice == 0) {
                        foodOrderCompleted = true;
                        cout << "Food order completed." << endl;
                    } else if (choice >= 1 && choice <= foodMenu.size()) {
                        receipt.addItem(foodMenu[choice - 1].getName(), foodMenu[choice - 1].getPrice(), 1);
                        cout << "Added " << foodMenu[choice - 1].getName() << " to your order." << endl;
                        report.recordFoodSale(foodMenu[choice - 1].getName(), foodMenu[choice - 1].getPrice());

                    } else {
                        cout << "Invalid choice. Try again." << endl;
                    }
                }
            }

            else if (i == movieList.size() + 1) {
                cout << "Thank you for visiting!" << endl;
                receipt.displayReceipt();
                gui.getWindow().close();
                return;
            }
        }
    }
}


int main() {
    vector<Movie*> movieList;
    bool running = true;
    Report report;

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

                    handleAdminActions(gui, event, movieList, report);
                }

                gui.display();
            }
        } else if (userChoice == "customer") {
            Receipt receipt;  
            Seating seating(5, 5);

            GUI gui;
            showCustomerOptions(gui, movieList);

            sf::Event event;
            while (gui.getWindow().isOpen()) {
                while (gui.getWindow().pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        gui.getWindow().close();
                        break;
                    }

                    handleCustomerActions(gui, event, movieList, seating, receipt, report);
                }

                gui.display();
            }
        } else if (userChoice == "exit") {
            running = false;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    for (Movie* movie : movieList) {
        delete movie;
    }

    return 0;
}





















