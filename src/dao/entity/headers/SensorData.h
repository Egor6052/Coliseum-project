#pragma once
#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <iostream>
#include <string>

class SensorData {
private:
    float current;
    float voltage;
    float activePower;
    float reactivePower;
public:
    SensorData();

    // Data processing from RS485
    void processData(const std::string& rawData);

    // Sending parameters
    void sendParametrsToRepository(Repository& repository);
};

#endif