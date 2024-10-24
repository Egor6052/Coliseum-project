 
#include <iostream>
#include <string>
#include "SensorData.h"
#include "SensorDataRepository.h"

SensorData::SensorData(){
	current = 0.0f;
    voltage = 0.0f;

    activePower = 0.0f;
    reactivePower = 0.0f;
}

 void SensorData::processData(const std::string& rawData) {
        try {
            // Розбираємо сирі дані (наприклад, формат "current:2.3,voltage:220,...")
            size_t currentPos = rawData.find("current:");
            size_t voltagePos = rawData.find("voltage:");

            if (currentPos != std::string::npos && voltagePos != std::string::npos) {
               
                this->current = std::stof(rawData.substr(currentPos + 8, rawData.find(",", currentPos) - currentPos - 8));
                this->voltage = std::stof(rawData.substr(voltagePos + 8, rawData.find(",", voltagePos) - voltagePos - 8));

                this->activePower = this->current * this->voltage;

                // Conditional value
                this->reactivePower = this->activePower * 0.9;
            } else {
                throw std::invalid_argument("Invalid raw data format");
            }
        } catch (const std::exception& e) {
            std::cerr << "Error processing data: " << e.what() << std::endl;
        }
    }

// Sending parameters to the repository class
void SensorData::sendParametrsToRepository(Repository& repository) {
    repository.SensorDataRepository(current, voltage, activePower, reactivePower);
}