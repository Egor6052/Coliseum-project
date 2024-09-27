#pragma once
#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <iostream>
#include <string>

class SensorData {
public:
    float current;      // Струм
    float voltage;      // Напруга
    float activePower;  // Активна потужність
    float reactivePower;// Реактивна потужність
    float frequency;    // Частота

    SensorData();
    void processData(const std::string& rawData);  // Обробка даних з RS485
};

#endif