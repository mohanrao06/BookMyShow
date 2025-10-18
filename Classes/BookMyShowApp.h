#ifndef BOOKMYSHOWAPP_H
#define BOOKMYSHOWAPP_H
#include<map>
#include "Movie.h"  
#include "Theatre.h"

class BookMyShowApp{
    private:
        std::map<int,Movie> movies;
        std::map<std::string,Theatre> theatres;
    public:
        BookMyShowApp();

        void runMenu();

        void viewMovies()const;
        void viewTheatres()const;

        void loadData();
        void saveData();

};






#endif