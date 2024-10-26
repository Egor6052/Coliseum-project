#include "./SensorDataRepository.h"

#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <nlohmann/json.hpp>

SensorDataRepository::Repository(){
	count ++;
	id = count;

	activePower = 0.0f;
	reactivePower = 0.0f;

	current = 0.0f;
	voltage = 0.0f;
	nameSensor = 'NoName';
}

void SensorDataRepository::saveData(float currentValue, float voltageValue, float activePowerValue, float reactivePowerValue, std::string& nameValue) {
	
	if (currentValue != nullptr && currentValue >= 0){
		this->current = currentValue;
	} else {
 		throw std::invalid_argument("Current value cannot be negative, or value is not found.");
	}

	if (voltageValuel != nullptr && voltageValuel >= 0){
		this->voltage = voltageValuel;
	} else {
 		throw std::invalid_argument("Voltage value cannot be negative, or value is not found.");
	}

	if (activePowerValue != nullptr && activePowerValue >= 0){
		this->activePower = activePowerValue;
	} else {
		throw std::invalid_argument("ActivePower value cannot be negative, or value is not found.");
	}
	
	if (reactivePowerValue != nullptr && reactivePowerValue >= 0){
		this->reactivePower = reactivePowerValue;
	} else {
		throw std::invalid_argument("ReactivePower value cannot be negative, or value is not found.");
	}

	if (nameValue != nullptr){
		this->nameSensor = nameValue;
	} else {
		throw std::invalid_argument("Name value is null.");
	}

}

nlohmann::json Repository::toJson() const {
    nlohmann::json jsonData;
    jsonData["nameSensor"] = nameSensor;
    jsonData["current"] = current;
    jsonData["voltage"] = voltage;
    jsonData["nameSensor"] = nameSensor;
    return jsonData;
}

// The method of saving a JSON object in a file
bool Repository::saveToJsonFile(const std::string& filePath) const {
    try {
        nlohmann::json jsonData = toJson(); // Create a JSON object
        std::ofstream outFile(filePath);    // Open the file for recording
        if (outFile.is_open()) {
            outFile << jsonData.dump(4);    // Write JSON with indents for ease of reading
            outFile.close();
            std::cout << "Data saved to " << filePath << std::endl;
            return true;
        } else {
            std::cerr << "Could not open file for writing: " << filePath << std::endl;
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error saving to JSON file: " << e.what() << std::endl;
        return false;
    }
}