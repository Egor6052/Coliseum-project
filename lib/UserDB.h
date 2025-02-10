#pragma once
#ifndef USERDB_H
#define USERDB_H

#include <iostream>
#include <string.h>

class UserDB {
    private:
    std::string name; 
    std::string password;
    std::string dbName;

    public:
        UserDB();
        ~UserDB();
        void setName(std::string valueName);
        void setPassword(std::string valuePassword);
        void createMySQLUser(const std::string& adminPassword);

        std::string getUserPassword();
        std::string getUserName();
        std::string getDBName();
        std::string getUser();
};

#endif