#pragma once
#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <iostream>
#include <string.h>

#include "UserDB.h"

class Accounts : public UserDB {
    private:
    std::string UserName; 
    std::string UserPassword;
    std::string Uid;

    bool isNotEmpty(const std::string& str);
    std::string generateUID();

    public:
        Accounts();
        ~Accounts();

        void setName(std::string valueName);
        void setPassword(std::string valuePassword);
        void setUID();
        void registerUser();

        void registerAsUser();
        void registerAsAdmin();

        std::string getAllUsersFromDB();
        std::string getAllAdminsFromDB();

        std::string getUserPassword();
        std::string getUserName();
        std::string getUID();

        bool Login();
        bool isAdministrator();
        
};

#endif