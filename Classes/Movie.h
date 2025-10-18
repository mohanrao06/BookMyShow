#ifndef MOVIE_H
#define MOVIE_H
#include<string>

class Movie{
    private:
        int movieId;
        std::string title;
        std::string showtime;
        int durationMinutes;
        

    public:
       Movie(int id, const std::string& t, const std::string& st, int dur);

        void displayInfo() const;
};

#endif