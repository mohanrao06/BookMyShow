#include "Seats.h"
#include <iostream>

Seat::Seat(const std::string& label):seatLabel(label),isBooked(true){

}

void Seat::displayStatus() const {
    std::string status = isBooked ? "B" : "F"; // 'B' for Booked, 'F' for Free
    std::cout << " [" << seatLabel << "-" << status << "] ";
}