#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string.h>
#include "Accounts.h"
#include "Logger.h"

class Database : public Accounts, public Logger {
    private:
        std::string data;
        std::string ipAddress;
        std::string nameSensor;
        float current;
        float voltage;
        float activePower;
        float reactivePower;

    public:
        Database();
        ~Database();

        std::string getCurrentDateTime();
        std::string getIpAddress();
        std::string getNameSensor();
        float getCurrent();
        float getVoltage();
        float getActivePower();
        float getPowerFactor();
        float getReactivePower();

        float roundNumber(float valueNumber);

        void CreateTable();

        void setData();

        void deleteData(std::string valueID);
        void createBackup();
        std::string getData();
};

#endif