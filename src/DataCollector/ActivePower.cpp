#include <iostream>
#include <string.h>
#include <cmath>
#include "../headers/DataCollector.h"

float DataCollector::getActivePower() {
    float activePower = 0.0f;
    int sensorAddress = 0x01;           // Адреса датчика
    int activePowerRegister = 0x0000;   // Регістр для активної потужності

    std::string response = RS485(sensorAddress, activePowerRegister, activePower);
    if (response.find("Error") != std::string::npos) {
        std::string errorMessage = "Failed to obtain active power: " + response;
        std::cerr << errorMessage << "\n";
        logError(errorMessage);
    } else {
        std::cout << "Data received: " << response << "\n";
    }

    return activePower;
}