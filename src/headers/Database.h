#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string.h>
#include "../../lib/mysql/mysql.h"

// #include "Accounts.h"
#include "Logger.h"
#include <string>

class Database : public Logger {
    private:
        std::string data;
        std::string ipAddress;
        std::string nameSensor;
        float current;
        float voltage;
        float activePower;
        float reactivePower;

        std::string name;
        std::string password;
        std::string adminPassword;
        std::string host_name;
        std::string dbName;
        std::string dbUsersName;

    public:
        Database();
        ~Database();

        // User DB
        MYSQL* conn;
        void mysqlConnect();
        void mysqlDisconnection(MYSQL_RES* res = nullptr);
        void setAdminPassword(std::string valueAdminPassword);

        std::string getUserDBName();
        std::string getUserDBPassword();
        std::string getAdminPassword();
        
        std::string getDBName();
        std::string getDBUsersName();
        std::string getUser();

        // DB
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
        void dataCollector();
        void setData(std::string data, std::string ipAddress, std::string nameSensor, float current, float voltage, float activePower, float reactivePower);

        void deleteData(std::string valueID);
        void createBackup();
        std::string getData();
        std::string getAllUsers();
};

#endif