#pragma once
#ifndef USERDB_H
#define USERDB_H

#include <iostream>
#include <string.h>

class UserDB {
    private:
    std::string name; 
    std::string password;
    std::string adminPassword;
    std::string dbName;

    public:
        UserDB();
        ~UserDB();
        void setUserDBName(std::string valueName);
        void setUserDBPassword(std::string valuePassword);
        void setAdminPassword(std::string valueAdminPassword);
        void createMySQLUser();

        std::string getUserDBPassword();
        std::string getUserDBName();
        std::string getAdminPassword();
        
        std::string getDBName();
        std::string getUser();
};

#endif