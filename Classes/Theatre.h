#ifndef THEATRE_H
#define THEATRE_H
#include<string>
#include<vector>
#include "Seats.h"

class Theatre{
    private:
        std::string theaterId;
        std::string name;
        std::vector<Seat> seats;
        const int totalRows=26;
        const int seatsPerRow=12;

    public:
        Theatre(const std::string& id,const std::string& n);
        void displaySeats() const;
        std::string getName()const{return name;}
        
        bool bookSeat(const std::string& seatLabel);
        bool unbookSeat(const std::string& seatLabel);



};




#endif