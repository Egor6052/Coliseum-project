#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string.h>
#include "../../lib/mysql/mysql.h"
#include "Logger.h"
#include <string>

class Database : public Logger {
    private:
        std::string name;
        std::string password;
        std::string adminPassword;
        std::string host_name;
        std::string dbName;
        std::string db_Data_Table;
        std::string db_Users_Table;

    public:
        Database();
        ~Database();

        // User DB
        MYSQL* conn;
        void mysqlConnect();
        void mysqlDisconnection(MYSQL_RES* res = nullptr);
        void setAdminPassword(std::string valueAdminPassword);
        void createDB();
        std::string getUserDBName();
        std::string getUserDBPassword();
        std::string getAdminPassword();
        std::string getDBName();
        std::string getTableName();
        std::string getDBUsersName();
        std::string getUser();

        // DB
        std::string getCurrentDateTime();
        void CreateTable();
        void setData(std::string data, std::string ipAddress, std::string nameSensor, float current, float voltage, float activePower, float reactivePower);
        void deleteData(std::string valueID);
        void createBackup();
        std::string getData();
        std::string getAllUsers();
};

#endif