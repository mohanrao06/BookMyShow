#ifndef USER_H
#define USER_H
#include <string>
#include <vector> // Required for fromCSV to use splitString

class User{
    private:
        std::string userId;
        std::string username;
        std::string passwordHash;
        std::string role;
    public:
        User(const std::string& id, const std::string& user, const std::string& pass, const std::string& r);

        // Getters
    std::string getId() const { return userId; }
    std::string getUsername() const { return username; }
    std::string getRole() const { return role; }

    bool isPasswordCorrect(const std::string& password) const;

    std::string toCSV() const;
    static User fromCSV(const std::string& csvLine);
    bool isAdmin() const { return role == "ADMIN"; }
};

#endif