#include "Movie.h"
#include <iostream>

Movie::Movie(int id, const std::string& t, const std::string& st, int dur)
    : movieId(id), title(t), showtime(st), durationMinutes(dur) {}


void Movie::displayInfo() const {
    std::cout << "  [" << movieId << "] " << title
              << " (" << durationMinutes << " min) @ " << showtime << std::endl;
}