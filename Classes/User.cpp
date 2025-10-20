#include "user.h"
#include<iostream>
#include "User.h"
#include "Utils.h"
User::User(const std::string& id, const std::string& user, const std::string& pass, const std::string& r)
    : userId(id), username(user), passwordHash(pass), role(r) {}

bool User::isPasswordCorrect(const std::string &password)const{
    return password==passwordHash;
}

std::string User::toCSV()const{
    // Format: ID,Username,Password(hash),Role
    return userId + "," + username + "," + passwordHash + "," + role;
}

User User::fromCSV(const std::string& csvLine){
    std::vector<std::string> tokens = splitString(csvLine, ',');
    if (tokens.size() < 4) {
        // Return a default error user if line is malformed
        return User("E0", "ERROR", "", "USER"); 
    }
    return User(tokens[0], tokens[1], tokens[2], tokens[3]);
}