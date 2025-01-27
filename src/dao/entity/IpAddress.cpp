#include <iostream>
#include <string.h>
#include <random>
#include "../lib/Database.h"

std::string Database::getIpAddress(){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 3);
    int randomInt = distribution(generator);
    std::string IP = "192.168." + std::to_string(randomInt) + "." + std::to_string(randomInt);
    
    return IP;
}