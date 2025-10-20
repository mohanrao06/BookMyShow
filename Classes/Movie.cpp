#include "Movie.h"
#include <iostream>
#include<vector>
#include <sstream>
#include "Utils.h"

std::vector<std::string> splitString(const std::string& str, char delimiter){
    std::vector<std::string> tokens;
    std::string token;
    std:: istringstream tokenStream(str);
    while(std::getline(tokenStream,token,delimiter)){
        tokens.push_back(token);
    }
    return tokens;
}
Movie::Movie(int id, const std::string& t, const std::string& st, int dur)
    : movieId(id), title(t), showtime(st), durationMinutes(dur) {}


std::string time(int min){
    std::string ans;
    int t=min/60;
    int m=min%60;
    ans=std::to_string(t)+"h "+std::to_string(m)+"m";
    return ans;

}
void Movie::displayInfo() const {
    std::cout << "  [" << movieId << "] " << title
              << " (" << time(durationMinutes) << ") @ " << showtime << std::endl;
}
std::string Movie::toCSV() const {
    
    return std::to_string(movieId) + "," + title + "," + showtime + "," + std::to_string(durationMinutes);
}

Movie Movie::fromCSV(const std::string& csvLine){
    std::vector<std::string> tokens = splitString(csvLine, ',');
    if (tokens.size() < 4) {
        
        return Movie(0, "ERROR", "N/A", 0); 
    }
    int id = std::stoi(tokens[0]);
    int duration = std::stoi(tokens[3]);
    return Movie(id, tokens[1], tokens[2], duration);
}
