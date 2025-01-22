#include <iostream>
#include <string.h>
#include <random>
#include "../lib/Database.h"


std::string Database::getNameSensor(){
    std::string NoName = "NoName";
    std::string Name1 = "Sensor1";
    std::string Name2 = "Sensor2";
    std::string Name3 = "Sensor3";

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 3);
    int randomInt = distribution(generator);

    if (randomInt == 1){
        return Name1;
    } else if (randomInt == 2){
        return Name2;
    } else if (randomInt == 3){
        return Name3;
    } else {
        return NoName;
    }
}
