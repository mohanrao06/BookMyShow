#include "BookMyShowApp.h"
#include<iostream>
#include<limits> 

BookMyShowApp::BookMyShowApp(){
    movies.emplace(101,Movie(101,"KGF1","7:00 AM",148));
    movies.emplace(102, Movie(102, "KGF2", "9:30 PM", 136));

    theatres.emplace("T01", Theatre("T01", "PVR Screen 3"));
    theatres.emplace("T02", Theatre("T02", "Cineplex Grande"));
    std::cout << "\n[System Status: Initial data loaded]\n";


}
void BookMyShowApp::viewMovies()const{
    std::cout<< "\n --- Available Movies --- \n";
    if(movies.empty()){
        std::cout<<"No movies currently scheduled.\n";
        return;
    }
    for (const auto& pair : movies) {
        pair.second.displayInfo(); // Calls the Movie::displayInfo() method
    }

}
void BookMyShowApp::viewTheatres()const{
    std::cout << "\n--- Available Theatres ---\n";
    if (theatres.empty()) {
        std::cout << "No theatres available.\n";
        return;
    }
    for(const auto& pair:theatres){
        std::cout<<"\n--- "<<pair.second.getName()<<" (" << pair.first << ") ---\n";
        if (pair.first == "T01") {
            pair.second.displaySeats(); 
        } else {
            std::cout << "Seats not displayed for this theatre.\n";
        }
    }
}
void BookMyShowApp::runMenu(){
    int choice=0;
    do{
        std::cout << "\n\n=== BookMyShow Console App ===\n"
                  << "1. View Movies & Showtimes\n"
                  << "2. View Theatres/Seat Layout (WIP)\n"
                  << "3. Admin/Login (WIP)\n"
                  << "4. Exit\n"
                  << "Enter your choice: ";
        
        if(!(std::cin>>choice)){
            std::cout<< "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            choice=0;
            continue;
        }
        switch(choice){
            case 1:viewMovies();break;
            case 2:viewTheatres();break;
            case 3: std::cout << "Admin/Login functionality coming soon...\n"; break;
            case 4: 
                // saveData(); // Will be implemented in Step 5
                std::cout << "Exiting BookMyShow. Goodbye!\n"; 
                break;
            default: std::cout << "Choice not recognized. Please try again.\n";
        }

    }while(choice!=4);
}
