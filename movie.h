#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>
using namespace std;

class Movie {
private:
    string title;
    string genre;
    vector<string> showtimes;
    int duration;
    string leadCast;
    

public:
    Movie(string title, string genre, const vector<string>& showtimes, int duration, string leadCast);
    
    string getTitle() const;
    string getGenre() const;
    string getLeadCast() const;
    vector<string> getShowtimes() const;
    int getDuration() const;

    void addShowtime(const string& showtime);
    void removeShowtime(const string& showtime);

    static void addMovie(vector<Movie*>& movieList, const string& title, const string& genre, const vector<string>& showtimes, int duration, const string& leadCast);
    static void removeMovie(vector<Movie*>& movieList, const string& title);

    static void saveMoviesToFile(const vector<Movie*>& movieList, const string& filename);  // New method
    static void loadMoviesFromFile(vector<Movie*>& movieList, const string& filename);     // New method
};

#endif



