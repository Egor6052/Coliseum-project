#include <iostream>
#include <string.h>
#include <random>
#include "../lib/Database.h"

std::string Database::getIpAddress(){
    std::string IP1 = "192.168.1.1";
    std::string IP2 = "192.168.2.2";
    std::string IP3 = "192.168.3.3";

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 3);
    int randomInt = distribution(generator);

    if (randomInt == 1){
        return IP1;
    } else if (randomInt == 2){
        return IP2;
    } else if (randomInt == 3){
        return IP3;
    } else {
        return "NoIP";
    }
}