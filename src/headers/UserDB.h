#pragma once
#ifndef USERDB_H
#define USERDB_H

#include <iostream>
#include <string.h>

#include "Logger.h"

class UserDB : public Logger {
    private:
    std::string name; 
    std::string password;
    std::string adminPassword;
    std::string dbName;
    std::string dbUsersName;

    public:
        UserDB();
        ~UserDB();
        // void setUserDBName(std::string valueName);
        // void setUserDBPassword(std::string valuePassword);
        void setAdminPassword(std::string valueAdminPassword);

        std::string getUserDBName();
        std::string getUserDBPassword();
        std::string getAdminPassword();
        
        std::string getDBName();
        std::string getDBUsersName();
        std::string getUser();
};

#endif