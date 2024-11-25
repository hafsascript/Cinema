#include <iostream>
#include <vector>
#include "movie.h"
#include "gui.h"
#include "seating.h"
#include "fooditem.h"
#include "receipt.h"
#include "report.h"
#include "giftcard.h"

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
    gui.createButton("Generate Report", 50, 470, 300, 50);
    gui.createButton("Add Gift Card", 50, 540, 200, 50); 
    gui.createButton("Check Gift Card Balance", 50, 610, 350, 50); 
}

vector<Movie*> searchMovies(const vector<Movie*>& movieList) {
    vector<Movie*> results;
    int searchOption;

    while (true) {
        cout << "\nSearch movies by:\n";
        cout << "1. Title\n";
        cout << "2. Genre\n";
        cout << "3. Showtimes\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> searchOption) || searchOption < 0 || searchOption > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again.\n";
            continue;
        }
        cin.ignore();

        if (searchOption == 0) {
            break; 
        }

        string query;
        cout << "Enter search query: ";
        getline(cin, query);

      
        for (Movie* movie : movieList) {
            if (searchOption == 1 && movie->getTitle().find(query) != string::npos) {
                results.push_back(movie);
            } else if (searchOption == 2 && movie->getGenre().find(query) != string::npos) {
                results.push_back(movie);
            } else if (searchOption == 3) {
                for (const string& showtime : movie->getShowtimes()) {
                    if (showtime.find(query) != string::npos) {
                        results.push_back(movie);
                        break;
                    }
                }
            }
        }

        if (results.empty()) {
            cout << "No movies found matching your query.\n";
        } else {
            cout << "\nMovies found:\n";
            for (size_t i = 0; i < results.size(); ++i) {
                cout << i + 1 << ". " << results[i]->getTitle() << " (" << results[i]->getGenre() << ")\n";
            }
        }
        break; 
    }

    return results;
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

    
    gui.createButton("Search Movies", 50, 50 + (movieList.size() * 70) + 70, 200, 50);
    gui.createButton("View Menu", 50, 50 + (movieList.size() * 70) + 140, 200, 50);
    gui.createButton("Exit", 50, 50 + (movieList.size() * 70) + 210, 200, 50);
}
void handleAdminActions(GUI& gui, sf::Event& event, vector<Movie*>& movieList,Report& report, GiftCard&giftCard) {
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
                case 6: 
                    report.generateReport(movieList);
                    break;
                case 7: { 
                    string cardCode;
                    float balance;
                    cout << "Enter Gift Card Code: ";
                    getline(cin, cardCode);
                    cout << "Enter Gift Card Balance: ";
                    cin >> balance;
                    cin.ignore();
                    giftCard.addGiftCard(cardCode, balance);  
                    break;
                }
                case 8: { 
                    string cardCode;
                    cout << "Enter Gift Card Code: ";
                    getline(cin, cardCode);
                    float balance = giftCard.getBalance(cardCode);  
                    if (balance > 0) {
                        cout << "Gift Card Balance: $" << balance << endl;
                    }
                    break;
                }
            }
        }
    }
}

void handleCustomerActions(GUI& gui, sf::Event& event, vector<Movie*>& movieList, Seating& seating, Receipt& receipt, Report& report,GiftCard&giftCard) {
    bool seatSelected = false;
    bool foodOrderCompleted = false;

    for (size_t i = 0; i < gui.getButtonShapes().size(); ++i) {
        if (gui.isButtonPressed(*gui.getButtonShapes()[i], event)) {
            cout << "Button pressed at index: " << i << endl;


           \
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
                vector<Movie*> searchResults = searchMovies(movieList);
                if (!searchResults.empty()) {
                    cout << "\nSelect a movie from the search results:\n";
                    for (size_t j = 0; j < searchResults.size(); ++j) {
                        cout << j + 1 << ". " << searchResults[j]->getTitle() << endl;
                    }

                    int movieChoice = -1;
                    while (true) {
                        cout << "Enter movie number (or 0 to cancel): ";
                        if (!(cin >> movieChoice) || movieChoice < 0 || movieChoice > searchResults.size()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please try again.\n";
                        } else {
                            break;
                        }
                    }

                    if (movieChoice > 0) {
                        Movie* selectedMovie = searchResults[movieChoice - 1];
                        vector<string> showtimes = selectedMovie->getShowtimes();
                        if (showtimes.empty()) {
                            cout << "No showtimes available for this movie." << endl;
                        } else {
                            cout << "Select a showtime for \"" << selectedMovie->getTitle() << "\":" << endl;
                            for (size_t k = 0; k < showtimes.size(); ++k) {
                                cout << k + 1 << ". " << showtimes[k] << endl;
                            }

                            int showtimeChoice = -1;
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
                    }
                }
            }

          
             else if (i == movieList.size() + 1) {
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
           
            else if (i == movieList.size() + 2) {
                cout << "Thank you for visiting!" << endl;
                receipt.displayReceipt();
                gui.getWindow().close();
                string useGiftCard;
                cout << "Do you want to use a gift card for a discount? (yes/no): ";
                getline(cin, useGiftCard);
                
                if (useGiftCard == "yes") {
                    string cardCode;
                    cout << "Enter Gift Card Code: ";
                    getline(cin, cardCode);
                    
                    
                    receipt.applyGiftCard(giftCard, cardCode);
                    receipt.displayReceipt();  
                }
                else {
                    cout << "No gift card used. Total remains: $" << receipt.getTotalCost() << endl;
                }
                
                
                
            }
        }
    }
}




int main() {
    vector<Movie*> movieList;
    bool running = true;
    Report report;
    GiftCard giftCard;
    

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

                    handleAdminActions(gui, event, movieList, report, giftCard);
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

                    handleCustomerActions(gui, event, movieList, seating, receipt, report, giftCard);
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





















