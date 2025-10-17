#include <iostream>
#include "classes/Movie.h"
#include "classes/Seats.h"

int main() {
    std::cout << "--- BookMyShow Testing ---\n";

    // Test the Movie class
    Movie inception(101, "Inception");
    inception.displayInfo(); 

    // Test the Seat class
    Seat seatA1("A1");
    Seat seatB5("B5");

    seatA1.displayStatus(); 
    seatB5.displayStatus(); 
    std::cout << "\n--------------------------\n";

    // In a real project, you compile everything with: 
    // g++ main.cpp classes/Movie.cpp classes/Seat.cpp -o app
    // Then run: ./app
    
    return 0;
}