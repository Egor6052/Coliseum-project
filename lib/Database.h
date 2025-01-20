#pragma once
#ifndef DATABASE
#define NOTE_H

#include <iostream>
#include <string.h>
#include "UserDB.h"

class Database : public UserDB{
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

        void CreateTable();

        void setData();

        void deleteData(std::string valueID);
        void createBackup();
        std::string getData();
};

#endif