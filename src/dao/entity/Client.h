#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>

class Client {
private:
    int clientID;          // Унікальний ID клієнта
    std::string name;      // Ім'я клієнта
    SensorData sensorData; // Показники споживання

public:
    Client(int id, const std::string& name);
    void updateData(const SensorData& data);
    int getClientID() const;
    std::string getName() const;
    SensorData getSensorData() const;
};

#endif