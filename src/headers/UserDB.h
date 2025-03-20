#pragma once
#ifndef USERDB_H
#define USERDB_H

#include <iostream>
#include <string.h>
#include <mysql/mysql.h>

#include "Logger.h"

class UserDB : public Logger {
    private:
    std::string name;
    std::string password;
    std::string adminPassword;
    
    std::string host_name;
    std::string dbName;
    std::string dbUsersName;

    public:
        UserDB();
        ~UserDB();
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
};

#endif