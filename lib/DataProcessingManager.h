#pragma once
#ifndef DATAPROCESSINGMANAGER_H
#define DATAPROCESSINGMANAGER_H

#include <iostream>
#include <vector>

class DataProcessingManager {
private:
    RS485Connection rs485;
    DatabaseConnection db;
    std::vector<Client> clients;

public:
    DataProcessingManager(const RS485Connection& rs485, const DatabaseConnection& db);

    void processClientData();              // Обробка даних із датчиків і передача в базу
    void addClient(const Client& client);  // Додавання нового клієнта
    void removeClient(int clientID);       // Видалення клієнта
};

#endif