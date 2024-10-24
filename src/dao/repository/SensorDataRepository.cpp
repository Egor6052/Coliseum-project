#include "SensorDataRepository.h"

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

void SensorDataRepository::setData(float currentValue, float voltageValue, float activePowerValue, float reactivePowerValue) {
	
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
}

void setName(std::string nameValue) {
	if (nameValue != nullptr){
		this->nameSensor = nameValue;
	} else {
		throw std::invalid_argument("Name value is null.");
	}
}

float SensorDataRepository::getCurrent(){
	return current;
}

float SensorDataRepository::getVoltage(){
	return voltage;
}

std::string SensorDataRepository::getNameSensor(){
	return nameSensor;
}

int SensorDataRepository::getID(){
	return id;
}

nlohmann::json Repository::toJson() const {
    nlohmann::json jsonData;
    jsonData["current"] = current;
    jsonData["voltage"] = voltage;
    jsonData["nameSensor"] = nameSensor;
    return jsonData;
}