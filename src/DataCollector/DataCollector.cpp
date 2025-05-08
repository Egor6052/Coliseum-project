#include <iostream>
#include <string.h>
#include "../headers/DataCollector.h"

DataCollector::DataCollector() {
    this->data = "";
    this->ipAddress = "";
    this->nameSensor = "";
    this->current = 0.0f;
    this->voltage = 0.0f;
    this->activePower = 0.0f;
    this->reactivePower = 0.0f;

}

DataCollector::~DataCollector() {  }


void DataCollector::setData(std::string data, std::string ipAddress, std::string nameSensor, float current, float voltage, float activePower, float reactivePower){
    this->data = data;
    this->ipAddress = ipAddress;
    this->nameSensor = nameSensor;
    this->current = current;
    this->voltage = voltage;
    this->activePower = activePower;
    this->reactivePower = reactivePower;
}

void DataCollector::dataCollector(){
    std::string data = getDateTime();
    std::string ipAddress = getIpAddress();
    std::string nameSensor = getNameSensor();
    float current = roundNumber(getCurrent());
    float voltage = roundNumber(getVoltage());
    float activePower = roundNumber(getActivePower());
    float reactivePower = roundNumber(getReactivePower());

    setData(data, ipAddress, nameSensor, current, voltage, activePower, reactivePower);
}

void DataCollector::processData() {
    // TODO
    std::cout << "Processing data..." << std::endl;
}

void DataCollector::sendDataToServer() {
    // TODO
    std::cout << "Sending data to server..." << std::endl;
}