#include "movie.h"
#include <iostream>
#include <fstream>

using namespace std;

Movie::Movie(string title, string genre, const vector<string>& showtimes, int duration, string leadCast)
    : title(title), genre(genre), showtimes(showtimes), duration(duration), leadCast(leadCast) {
    
    for (const auto& showtime : showtimes) {
        showtimeSeatingMap[showtime] = new Seating(5, 5);  
    }
}

string Movie::getTitle() const {
    return title;
}

string Movie::getGenre() const {
    return genre;
}

string Movie::getLeadCast() const {
    return leadCast;
}

vector<string> Movie::getShowtimes() const {
    return showtimes;
}

int Movie::getDuration() const {
    return duration;
}

Seating* Movie::getSeatingForShowtime(const string& showtime) {
    if (showtimeSeatingMap.find(showtime) != showtimeSeatingMap.end()) {
        return showtimeSeatingMap[showtime];
    }
    return nullptr;  
}

void Movie::addShowtime(const string& showtime) {
    showtimes.push_back(showtime);
    showtimeSeatingMap[showtime] = new Seating(5, 5);  
}

void Movie::removeShowtime(const string& showtime) {
    for (auto it = showtimes.begin(); it != showtimes.end(); ++it) {
        if (*it == showtime) {
            showtimes.erase(it);
            delete showtimeSeatingMap[showtime]; 
            showtimeSeatingMap.erase(showtime);
            return;
        }
    }
}

void Movie::addMovie(vector<Movie*>& movieList, const string& title, const string& genre, const vector<string>& showtimes, int duration, const string& leadCast) {
    movieList.push_back(new Movie(title, genre, showtimes, duration, leadCast));
    cout << "Movie \"" << title << "\" added successfully!" << endl;  
}

void Movie::removeMovie(vector<Movie*>& movieList, const string& title) {
    for (auto it = movieList.begin(); it != movieList.end(); ++it) {
        if ((*it)->getTitle() == title) {
            cout << "Removing movie: \"" << (*it)->getTitle() << "\"" << endl;  
            delete *it;  
            movieList.erase(it);
            cout << "Movie \"" << title << "\" removed successfully!" << endl;
            return;
        }
    }
    cout << "Movie \"" << title << "\" not found!" << endl;  


}

void Movie::saveMoviesToFile(const vector<Movie*>& movieList, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error: Could not open file for writing!" << endl;
        return;
    }

    for (const auto& movie : movieList) {
        outFile << movie->title << "\n"
                << movie->genre << "\n"
                << movie->leadCast << "\n"
                << movie->duration << "\n";
        
        for (const auto& showtime : movie->showtimes) {
            outFile << showtime << ",";
        }
        outFile << "\n";
    }
    outFile.close();
    cout << "Movies saved to file \"" << filename << "\" successfully!" << endl;
}


void Movie::loadMoviesFromFile(vector<Movie*>& movieList, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Could not open file for reading!" << endl;
        return;
    }

    string title, genre, leadCast, showtimesLine;
    int duration;

    while (getline(inFile, title) && getline(inFile, genre) && getline(inFile, leadCast) && inFile >> duration) {
        inFile.ignore();  

        
        bool movieExists = false;
        for (const auto& movie : movieList) {
            if (movie->getTitle() == title) {
                movieExists = true;
                break;
            }
        }

        if (!movieExists) {
            cout << "Reading movie: " << title << ", Duration: " << duration << endl;

            
            if (getline(inFile, showtimesLine)) {
                
                if (!showtimesLine.empty() && showtimesLine.back() == ',') {
                    showtimesLine.pop_back();
                }

                vector<string> showtimes;
                size_t pos = 0;
                while ((pos = showtimesLine.find(',')) != string::npos) {
                    showtimes.push_back(showtimesLine.substr(0, pos));
                    showtimesLine.erase(0, pos + 1);
                }

                if (!showtimesLine.empty()) {
                    showtimes.push_back(showtimesLine);
                }

                
                movieList.push_back(new Movie(title, genre, showtimes, duration, leadCast));
            }
        } else {
            cout << "Movie \"" << title << "\" already exists, not adding again." << endl;
        }
    }
    inFile.close();

    cout << "Movies loaded from file \"" << filename << "\" successfully!" << endl;

    
    for (const auto& movie : movieList) {
        cout << "Title: " << movie->getTitle() << ", Genre: " << movie->getGenre() 
             << ", Duration: " << movie->getDuration() << ", Lead Cast: " << movie->getLeadCast() << endl;

        cout << "Showtimes: ";
        for (const auto& showtime : movie->getShowtimes()) {
            cout << showtime << " ";
        }
        cout << endl;
    }
}
