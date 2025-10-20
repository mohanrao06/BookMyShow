#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

// Function DECLARATION (tells other files WHAT the function is)
// The actual definition (HOW it works) remains in Movie.cpp
std::vector<std::string> splitString(const std::string& str, char delimiter);

#endif // UTILS_H