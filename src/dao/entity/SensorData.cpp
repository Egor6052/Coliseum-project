 
#include <iostream>
#include <string>
#include "./headers/SensorData.h"
#include "../repository/SensorDataRepository.h"

SensorData::SensorData(){
    nameSensor = "NoName";

	current = 0.0f;
    voltage = 0.0f;

    activePower = 0.0f;
    reactivePower = 0.0f;
}

void SensorData::processData(const std::string& rawData) {
    try {
        // Витягуємо ідентифікатор датчика (номер або IP)
        size_t idPos = rawData.find("sensor_id:");
        if (idPos != std::string::npos) {
            nameSensor = rawData.substr(idPos + 10, rawData.find(",", idPos) - idPos - 10);
        }

        size_t currentPos = rawData.find("current:");
        size_t voltagePos = rawData.find("voltage:");

        if (currentPos != std::string::npos && voltagePos != std::string::npos) {
            // Виділяємо значення струму та напруги
            current = std::stof(rawData.substr(currentPos + 8, rawData.find(",", currentPos) - currentPos - 8));
            voltage = std::stof(rawData.substr(voltagePos + 8, rawData.find(",", voltagePos) - voltagePos - 8));

            // Розрахунок активної потужності
            activePower = current * voltage;
            // Розрахунок реактивної потужності з умовою
            reactivePower = activePower * 0.9;

        } else {
            throw std::invalid_argument("Invalid raw data format");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error processing data: " << e.what() << std::endl;
    }
}


void SensorData::sendParametrsToRepository(Repository& repository) {
    repository.saveData(current, voltage, activePower, reactivePower, nameSensor);
}