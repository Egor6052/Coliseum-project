#include <iostream>
#include <string.h>
#include <random>
#include "../headers/DataCollector.h"


std::string DataCollector::getNameSensor(){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 3);
    int randomInt = distribution(generator);

    std::string SensorName = "Office" + std::to_string(randomInt);
    
    return SensorName;
}
