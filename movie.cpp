#include "movie.h"
#include <iostream>

Movie::Movie(string title, string genre, const vector<string>& showtimes, int duration, string leadCast)
    : title(title), genre(genre), showtimes(showtimes), duration(duration), leadCast(leadCast) {}

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

void Movie::addShowtime(const string& showtime) {
    showtimes.push_back(showtime);
}

void Movie::removeShowtime(const string& showtime) {
    for (auto it = showtimes.begin(); it != showtimes.end(); ++it) {
        if (*it == showtime) {
            showtimes.erase(it);
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






