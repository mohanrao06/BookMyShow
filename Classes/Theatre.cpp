#include "Theatre.h"
#include <iostream>

Theatre:: Theatre(const std::string& id,const std::string& n)
    :theaterId(id), name(n)
    {
        char rowLabel='A';
        for(int r=0;r<totalRows;r++){
            for(int s=1;s<=seatsPerRow;s++){
                std::string seatLabel = rowLabel + std::to_string(s);
                seats.emplace_back(seatLabel);
            }
            rowLabel++;


        }
    }
void Theatre::displaySeats() const{
    std::cout<<"\n----Theater: "<<name << " (" << theaterId << ") ---\n";
    int count=0;
    for(const auto& seat :seats){
        seat.displayStatus();
        count++;
        if(count%seatsPerRow==0){
            std::cout<<"\n\n";
        }
    }
}
bool Theatre::bookSeat(const std::string& seatLabel) {
   
    for (auto& seat : seats) { 

        if (seat.getLabel() == seatLabel) {
            
            if (seat.isSeatBooked()) {
                std::cout << "Error: Seat " << seatLabel << " is already booked (X).\n";
                return false;
            }
            
            seat.setBooked(true);
            return true;
        }
    }
    std::cout << "Error: Seat " << seatLabel << " not found in theatre " << name << ".\n";
    return false; // Seat label was invalid
}
bool Theatre::unbookSeat(const std::string& seatLabel) {
    // Iterate through all seats in the vector
    for (auto& seat : seats) { 
        // We use getLabel() and setBooked() from the Seat class
        if (seat.getLabel() == seatLabel) { 
            // Mark the seat as free (false)
            seat.setBooked(false); 
            return true; // Success
        }
    }
    return false; // Seat label was not found
}