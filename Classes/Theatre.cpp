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