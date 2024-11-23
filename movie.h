#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>
#include <map>
#include "seating.h"  

using namespace std;

class Movie {
private:
    string title;
    string genre;
    vector<string> showtimes;
    int duration;
    string leadCast;
    map<string, Seating*> showtimeSeatingMap; 
    double ticketPrice; 
public:
    Movie(string title, string genre, const vector<string>& showtimes, int duration, string leadCast,double ticketPrice);
    
    string getTitle() const;
    string getGenre() const;
    string getLeadCast() const;
    vector<string> getShowtimes() const;
    int getDuration() const;
    double getTicketPrice() const;  
    void setTicketPrice(double price); 
    Seating* getSeatingForShowtime(const string& showtime);  
    void addShowtime(const string& showtime);
    void removeShowtime(const string& showtime);

    static void addMovie(vector<Movie*>& movieList, const string& title, const string& genre, const vector<string>& showtimes, int duration, const string& leadCast,double ticketPrice);
    static void removeMovie(vector<Movie*>& movieList, const string& title);

    static void saveMoviesToFile(const vector<Movie*>& movieList, const string& filename);
    static void loadMoviesFromFile(vector<Movie*>& movieList, const string& filename);
};

#endif




