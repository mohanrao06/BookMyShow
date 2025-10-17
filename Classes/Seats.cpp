#include "Seats.h"
#include <iostream>

Seat::Seat(const std::string& label):seatLabel(label),isBooked(false){

}

void Seat::displayStatus() const {
    std::string status = isBooked ? "BOOKED" : "FAILED"; // 'B' for Booked, 'F' for Free
    std::cout << "[" << seatLabel << "-" << status << "]";
}