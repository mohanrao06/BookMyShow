#include "Movie.h"
#include <iostream>

Movie::Movie(int id,const std::string& t):movieId(id),title(t){

}
void Movie::displayInfo()const{
    std::cout << "Movie ID: " << movieId << ", Title: " << title << std::endl;
}