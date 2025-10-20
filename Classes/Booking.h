#ifndef BOOKING_H
#define BOOKING_H
#include <string>
#include <vector>

class Booking {
private:
    std::string bookingId;
    std::string userId;
    int movieId;
    std::string theatreId;
    std::string seatLabel;
    std::string status; // "BOOKED" or "CANCELLED"

public:
    // Constructor
    Booking(const std::string& bid, const std::string& uid, int mid, 
            const std::string& tid, const std::string& sl, const std::string& s);

    // Getters for core IDs
    std::string getId() const { return bookingId; }
    std::string getUserId() const { return userId; }
    
    // Display method
    void displayReceipt() const;

    // Persistence Methods (CSV)
    std::string toCSV() const;
    static Booking fromCSV(const std::string& csvLine);
};

#endif // BOOKING_H