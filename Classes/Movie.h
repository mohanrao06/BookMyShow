#ifndef MOVIE_H
#define MOVIE_H
#include<string>

class Movie{
    private:
        int movieId;
        std::string title;
    public:
        Movie(int id,const std::string& t);

        void displayInfo() const;
};

#endif