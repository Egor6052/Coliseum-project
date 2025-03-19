#include <iostream>
#include <string.h>
#include <random>
#include "../../headers/Database.h"


std::string Database::getNameSensor(){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 3);
    int randomInt = distribution(generator);

    std::string SensorName = "Sensor" + std::to_string(randomInt);
    
    return SensorName;
}
