#include "Booking.h"
#include <iostream>
#include "User.h"
#include "Utils.h"

Booking::Booking(const std::string& bid, const std::string& uid, int mid, 
                 const std::string& tid, const std::string& sl, const std::string& s)
    : bookingId(bid), userId(uid), movieId(mid), theatreId(tid), seatLabel(sl), status(s) {}

void Booking::displayReceipt()const{
    std::cout << "\n--- Booking Receipt ---\n";
    std::cout << "  Booking ID: " << bookingId << "\n";
    std::cout << "  User ID: " << userId << "\n";
    std::cout << "  Movie ID: " << movieId << "\n";
    std::cout << "  Theatre ID: " << theatreId << "\n";
    std::cout << "  Seat: " << seatLabel << "\n";
    std::cout << "  Status: " << status << "\n";
    std::cout << "-----------------------\n";
}
std::string Booking::toCSV() const {
    // Format: BookingID,UserID,MovieID,TheatreID,SeatLabel,Status
    return bookingId + "," + userId + "," + std::to_string(movieId) + "," + 
           theatreId + "," + seatLabel + "," + status;
}

Booking Booking::fromCSV(const std::string& csvLine) {
    // Requires splitString helper function to be available
    std::vector<std::string> tokens = splitString(csvLine, ',');
    
    if (tokens.size() < 6) return Booking("E0", "", 0, "", "", "");

    // Convert MovieID (tokens[2]) to int
    int mid = std::stoi(tokens[2]);

    return Booking(tokens[0], tokens[1], mid, tokens[3], tokens[4], tokens[5]);
}