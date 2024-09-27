#pragma once
#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <iostream>
#include <string>
class DatabaseConnection {
private:
    std::string dbName;       // Ім'я бази даних
    std::string dbUser;       // Користувач бази даних
    std::string dbPassword;   // Пароль
    std::string dbHost;       // Хост бази даних

public:
    DatabaseConnection(const std::string& dbName, const std::string& user, const std::string& password, const std::string& host);

    bool connect();           // Підключення до бази даних
    bool saveSensorData(const SensorData& data, int clientID); // Збереження даних у БД
    void close();             // Закриття з'єднання
};

#endif