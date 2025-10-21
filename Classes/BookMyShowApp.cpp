#include "BookMyShowApp.h"
#include "User.h"
#include<iostream>
#include<limits> 
#include <fstream>    // NEW: For file stream operations
#include <sstream>
#include<vector>




BookMyShowApp::BookMyShowApp(){
    movies.emplace(101, Movie(101, "Inception", "7:00 PM", 148)); 
    movies.emplace(102, Movie(102, "The Matrix", "9:30 PM", 136));

    // Theatres were not the source of the crash, but let's keep them for testing.
    theatres.emplace("T01", Theatre("T01", "PVR Screen 3"));
    theatres.emplace("T02", Theatre("T02", "Cineplex Grande"));
    
    loadData(); // This is still running, but the app won't crash if it fails
    
    std::cout << "\n[System Status: Data Loaded]\n";
    


}
void BookMyShowApp::loadData(){
    std::cout << "Loading data...\n";

    std::ifstream movieFile("data/movies.txt");
    std::string line;
    int count=0;
    if(movieFile.is_open()){
        while(std::getline(movieFile,line)){
            if(line.empty() || line.find_first_not_of(' ') == std::string::npos)continue;

            Movie m=Movie::fromCSV(line);


            movies.emplace(m.getId(),m);
            count++;
        }
        movieFile.close();
        std::cout<<"-> Loaded " << count << " movies.\n";
        
    }else{
        std::cerr << "Warning: data/movies.txt not found. Starting with 0 movies.\n";

    }


    std::ifstream userFile(USER_FILE);
    
    if (userFile.is_open()) {
        while (std::getline(userFile, line)) {
            if (line.empty() || line.find_first_not_of(' ') == std::string::npos) continue;
            // NOTE: Add try/catch block here if using C++11 or higher for robustness
            User u = User::fromCSV(line);
            users.emplace(u.getId(), u); // Assuming getId() returns the string ID
        }
        userFile.close();
    }

    std::ifstream bookingFile(BOOKING_FILE);
count = 0; // Reuse count variable
if (bookingFile.is_open()) {
    while (std::getline(bookingFile, line)) {
        if (line.empty() || line.find_first_not_of(' ') == std::string::npos) continue;
        
        try {
            // CRITICAL: Ensure you defined BOOKING_FILE globally in BookMyShowApp.h
            Booking b = Booking::fromCSV(line);
            bookings.emplace(b.getId(), b);
            count++;
        } catch (const std::exception& e) {
            std::cerr << "Error loading booking: " << e.what() << "\n";
        }
    }
    bookingFile.close();
    std::cout << "-> Loaded " << count << " bookings.\n"; // Add confirmation message
}
    
}
void BookMyShowApp::saveData(){
    std::cout<<"Saving data...\n";


    std::ofstream movieFiles(MOVIE_FILE);
    if(movieFiles.is_open()){
        for(const auto& pair:movies){
            movieFiles<<pair.second.toCSV()<<"\n";
        }
        movieFiles.close();
        std::cout << "-> Saved " << movies.size() << " movies.\n";

    }else {
        std::cerr << "Error: Could not open " << MOVIE_FILE << " for writing.\n";
    }

    std::ofstream userFile(USER_FILE); 
    if (userFile.is_open()) {
        for (const auto& pair : users) {
            // Use the User::toCSV() method you implemented in Step 6.1
            userFile << pair.second.toCSV() << "\n"; 
        }
        userFile.close();
        std::cout << "-> Saved " << users.size() << " users.\n";
    } else {
        std::cerr << "Error: Could not open " << USER_FILE << " for writing.\n";
    }
    std::ofstream bookingFile(BOOKING_FILE); 
    if (bookingFile.is_open()) {
        for (const auto& pair : bookings) {
            
            bookingFile << pair.second.toCSV() << "\n"; 
        }
        bookingFile.close();
        std::cout << "-> Saved " << bookings.size() << " bookings.\n"; // Optional: Add success message
    } else {
        std::cerr << "Error: Could not open " << BOOKING_FILE << " for writing.\n";
    }
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
        // FIX: Remove the conditional block that called displaySeats()
        std::cout << "  [" << pair.first << "] " << pair.second.getName() << "\n";
    }
    std::cout << "\n--------------------------\n";
}
void BookMyShowApp::runMenu() {
    int choice = 0;
    do {
        std::cout << "\n\n=== BookMyShow Console App ===\n"
                  << "1. View Movies & Showtimes\n"
                  << "2. BOOK TICKETS\n"
                  << "3. View My Bookings\n"      // MODIFIED OPTION
                  << "4. Admin/Login\n"          // Moved to 4
                  << "5. Exit\n"                 // Moved to 5
                  << "Enter your choice: ";

        // ... (input handling) ...
        if (!(std::cin >> choice)) {
    // This only runs if the loop condition is evaluated, but the stream is already bad.
    std::cout << "Invalid input. Please enter a number.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    choice=0;
    continue;
}

        switch(choice){
            case 1: viewMovies(); break;
            case 2: bookTicketFlow(); break;
            case 3: viewMyBookings(); break; // NEW: Call the history viewer
            case 4: showAuthMenu(); break;   // Login/Register
            case 5: saveData(); std::cout << "Exiting BookMyShow. Goodbye!\n"; break;
            default: std::cout << "Choice not recognized.\n";
        }
    } while (choice != 5);
}
std::string BookMyShowApp::generateUserId() {
    // Format: "U" followed by the current size of the users map + 1
    return "U" + std::to_string(users.size() + 1);
}

void BookMyShowApp::userRegister(){
    std::string username, password;
    std::cout << "\n--- New User Registration ---\n";
    std::cout << "Enter username: ";
    std::cin >> username;

    for(const auto& pair:users){
        if(pair.second.getUsername()==username){
            std::cout << "Error: Username '" << username << "' already taken.\n";
            return;
        }
    }
    std::cout << "Create password: ";
    std::cin >> password;

    std::string newId = generateUserId();
    User newUser(newId, username, password, "USER");
    users.emplace(newId, newUser);
    saveData();
    std::cout << "\nRegistration successful! Your User ID is " << newId << ".\n";
}
User* BookMyShowApp::userLogin() {
    std::string username, password;
    std::cout << "\n--- User Login ---\n";
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    // 1. Search the 'users' map by iterating and comparing usernames
    for (auto& pair : users) {
        if (pair.second.getUsername() == username) {
            // 2. Check password using the User class method
            if (pair.second.isPasswordCorrect(password)) {
                std::cout << "Login successful! Welcome, " << username << ".\n";
                // Return a pointer to the User object found in the map
                return &pair.second; 
            } else {
                std::cout << "Login failed: Incorrect password.\n";
                return nullptr;
            }
        }
    }

    std::cout << "Login failed: User not found.\n";
    return nullptr;
}
// Implement the new sub-menu function
void BookMyShowApp::showAuthMenu() {
    int choice = 0;
    
    do {
        std::cout << "\n--- Authentication Menu ---\n";
        // Check if a user is currently logged in
        if (currentUser) {
            std::cout << "Logged in as: " << currentUser->getUsername() << " (" << currentUser->getRole() << ")\n";
            std::cout << "1. Logout\n"; // New option for logging out
            std::cout << "2. Go Back\n";
        } else {
            std::cout << "1. Login\n";
            std::cout << "2. Register New User\n";
            std::cout << "3. Go Back to Main Menu\n";
        }
        std::cout << "Enter choice: ";
        
        if (!(std::cin >> choice)) {
            // Input clearing logic remains the same
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0;
            continue;
        }

        if (currentUser) {
            // Logic for when the user IS logged in
            if (choice == 1) {
                currentUser = nullptr; // Logout
                std::cout << "\nLogged out successfully.\n";
            } else if (choice == 2) {
                return; // Go Back
            }
        } else {
            // Logic for when the user is NOT logged in
            if (choice == 1) {
                currentUser = userLogin(); // Attempt Login
                if (currentUser) {
                    if (currentUser->isAdmin()) {
                        std::cout << "\nAdmin Login Successful. Redirecting to Admin Panel...\n";
                        adminMenu();
                    }
                    return;
                }// Go back to main menu on success
            } else if (choice == 2) {
                userRegister(); // Register New User
            } else if (choice == 3) {
                return; // Go Back
            }
        }
    } while (choice != (currentUser ? 2 : 3)); // Loop until 'Go Back' is chosen
}
void BookMyShowApp::bookTicketFlow(){
    if (!currentUser) {
        std::cout << "\nAccess Denied: Please login first (Option 3).\n";
        return;
    }
    std::cout << "\n--- Starting Ticket Booking for " << currentUser->getUsername() << " ---\n";
    viewMovies();
    int movieId;
    std::cout << "Enter Movie ID to book: ";
    if(!(std::cin>>movieId)){return;}

    auto movieIt=movies.find(movieId);
    if(movieIt==movies.end()){
        std::cout << "Error: Invalid Movie ID.\n";
        return;
    }
    Movie& selectedMovie=movieIt->second;

    

    viewTheatres(); // Show available theatres list (T01, T02, etc.)
    std::string theatreId;
    std::cout << "Enter Theatre ID for booking: ";
    std::cin >> theatreId;
    auto theatreIt = theatres.find(theatreId);
    if (theatreIt == theatres.end()) { 
        std::cout << "Error: Theatre T01 not found.\n"; 
        return; 
    }
    Theatre& selectedTheatre = theatreIt->second;

    selectedTheatre.displaySeats();
    std::string seatLabel;
    std::cout << "Enter desired Seat Label (e.g., A5): ";
    std::cin >> seatLabel;
    if (selectedTheatre.bookSeat(seatLabel)) {
        
        // --- Step D: Payment Simulation ---
        std::cout << "\n[Payment Simulation]: Initiating transaction...\n";
        
        // Simple success check
        if (rand() % 10 < 1) { // 20% chance of failure
            
            selectedTheatre.unbookSeat(seatLabel); // Unbook the seat
            std::cout << "Payment Failed! Seat reservation released.\n";
            std::cout << "Data Rollback Complete.\n";
            return; // Stop the function here
        }
        std::cout << "Payment Successful! \n";
        std::string bookingId = "B" + std::to_string(bookings.size() + 1);
        Booking newBooking(
            bookingId, 
            currentUser->getId(), 
            selectedMovie.getId(), 
            theatreId, 
            seatLabel, 
            "BOOKED"
        );
        bookings.emplace(bookingId, newBooking);
        saveData();
        std::cout << "\nSUCCESS! Booking " << bookingId << " confirmed.\n";
        newBooking.displayReceipt();
    } 
    else {
        std::cout << "\nBooking Failed. Check seat availability/label.\n";
    }



}
void BookMyShowApp::viewMyBookings() const {
    if (!currentUser) {
        std::cout << "\nAccess Denied: Please login to view your history (Option 3).\n";
        return;
    }

    std::cout << "\n=== Bookings for " << currentUser->getUsername() << " (ID: " << currentUser->getId() << ") ===\n";

    bool found = false;
    // Iterate through all bookings in the system
    for (const auto& pair : bookings) {
        // Check if the booking belongs to the current user
        if (pair.second.getUserId() == currentUser->getId()) {
            pair.second.displayReceipt();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No bookings found for this user.\n";
    }
}


void BookMyShowApp::adminMenu(){
    if(!currentUser || currentUser->getRole() != "ADMIN"){
        std::cout << "\nADMIN ACCESS DENIED: Insufficient permissions.\n";
        return;

    }

    int choice=0;
  
    do {
        std::cout << "\n=== ADMIN PANEL ===\n"
                  << "Logged in as: " << currentUser->getUsername() << "\n"
                  << "1. Add New Movie\n"
                  << "2. View All System Bookings\n"
                  << "3. Add New Theatre\n" // NEW OPTION
                  << "4. Go Back to Main Menu\n" // Exit is now 4
                  << "Enter choice: ";

        // ... (input handling) ...
        if (!(std::cin >> choice)) {
            // Input clearing logic remains the same
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: addMovie(); break;
            case 2: viewAllBookings(); break;
            case 3: addTheatre(); break; // NEW CASE
            case 4: return; // Exits the adminMenu function
            default: std::cout << "Invalid choice.\n";
        }
    } while (true);
}
void BookMyShowApp::addMovie() {
    std::string title, showtime;
    int duration;
    
    std::cout << "\n--- Add New Movie ---\n";
    std::cout << "Enter Title (no spaces): "; 
    std::cin >> title;

    std::cout << "Enter Showtime (e.g., 8:00PM): "; 
    std::cin >> showtime;

    std::cout << "Enter Duration (minutes): "; 
    if (!(std::cin >> duration)) { 
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid duration. Aborting.\n";
        return; 
    }

    // Generate a simple ID based on current size
    int newId = 100 + movies.size() + 1;
    Movie newMovie(newId, title, showtime, duration);
    movies.emplace(newId, newMovie);
    
    saveData(); // CRITICAL: Save the new movie list
    std::cout << "\nSUCCESS! Movie '" << title << "' added with ID " << newId << ".\n";
}
void BookMyShowApp::viewAllBookings() const {
    std::cout << "\n=== ALL SYSTEM BOOKINGS ===\n";
    if (bookings.empty()) {
        std::cout << "No bookings recorded in the system.\n";
        return;
    }
    // Iterate through the central bookings map and display each receipt
    for (const auto& pair : bookings) {
        pair.second.displayReceipt();
    }
}

void BookMyShowApp::addTheatre() {
    std::string name;
    std::cout << "\n--- Add New Theatre ---\n";
    std::cout << "Enter Theatre Name (no spaces): "; 
    std::cin >> name;

    // Generate a simple ID
    std::string newId = "T" + std::to_string(theatres.size() + 1);

    // CRITICAL: Theatre constructor should handle seat creation
    Theatre newTheatre(newId, name); 
    theatres.emplace(newId, newTheatre);

    // NOTE: We skip Theatre persistence for the final step due to complexity, 
    // but this adds it to the map for the session.
    // If you were to persist, Theatre::toCSV() would be complex.

    std::cout<< "\nSUCCESS! Theatre '" << name << "' added with ID " << newId << ".\n";
}