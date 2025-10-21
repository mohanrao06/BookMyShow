#ifndef BOOKMYSHOWAPP_H
#define BOOKMYSHOWAPP_H
#include "Booking.h"
#include "User.h"
#include<map>
#include "Movie.h"  
#include "Theatre.h"
const std::string MOVIE_FILE = "data/movies.txt";
const std::string THEATRE_FILE = "data/theatres.txt";
const std::string USER_FILE="data/user.txt";
const std::string BOOKING_FILE="data/bookings.txt";
class BookMyShowApp{
    private:
        std::map<int,Movie> movies;
        std::map<std::string,Theatre> theatres;
        std::map<std::string, Booking> bookings;
        std::map<std::string, User> users;       // Map to store User objects
        User* currentUser = nullptr;
    public:
        BookMyShowApp();

        void runMenu();

        void viewMovies()const;
        void viewTheatres()const;

        void loadData();
        void saveData();
        void userRegister();

        std::string generateUserId();
        User* userLogin();
        void showAuthMenu();
        void bookTicketFlow();
        void viewMyBookings() const;

        void adminMenu();
        void addMovie();
        void viewAllBookings() const;
        void addTheatre();

};






#endif