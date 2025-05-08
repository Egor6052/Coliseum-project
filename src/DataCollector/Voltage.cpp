#include <iostream>
#include <string.h>
#include <random>
#include "../headers/DataCollector.h"

float DataCollector::getVoltage(){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> distribution(0.0f, 440.0f);
    float randomFloat = distribution(generator);

    float voltage = randomFloat;
    return voltage;
}