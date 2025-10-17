#ifndef SEAT_H
#define SEAT_H
#include<string>

class Seat{
    private:
        std::string seatLabel;
        bool isBooked;
    public:
        Seat(const std::string& label);

        void displayStatus()const;
};
#endif