#include <iostream>
#include <string.h>
#include <cmath>
#include "../headers/DataCollector.h"

float DataCollector::getReactivePower() {
    float reactivePower = 0.0f;
    int sensorAddress = 0x01;           // Адреса датчика
    int reactivePowerRegister = 0x0004; // Регістр для реактивної потужності

    std::string response = RS485(sensorAddress, reactivePowerRegister, reactivePower);
    if (response.find("Error") != std::string::npos) {
        std::string errorMessage = "Failed to obtain reactive power: " + response;
        std::cerr << errorMessage << "\n";
        logError(errorMessage);
    } 
    else {
        std::cout << "Data received: " << response << "\n";
    }

    return reactivePower;
}

