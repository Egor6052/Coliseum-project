#pragma once
#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <iostream>
#include <string.h>

#include "Database.h"

class Accounts : public Database {
    private:
    std::string Uid;
    // std::string UserName;
    // std::string UserPassword;
    // std::string UserEmail;

    bool isNotEmpty(const std::string& str);
    std::string generateUID();

    public:
        Accounts();
        ~Accounts();
        bool Login(const std::string& email, const std::string& password);
        std::string generateAccessToken(const std::string& email, const std::string& key, const std::string& fingerPrint = "");
        std::string generateRefreshToken(const std::string& email, const std::string& key, const std::string& fingerPrint = "");
        std::string getUserData(const std::string& uid);
        std::string getUserRole(const std::string& uid);
        std::string getUserName(const std::string& uid);
        std::string getUserPassword(const std::string& uid);
        std::string getUserEmail(const std::string& uid);
        std::string getUID(std::string email);

        // void setName(std::string valueName);
        // void setPassword(std::string valuePassword);
        // void setEmail(std::string valueEmail);

        void registerNewUser(std::string login, std::string password, std::string email, std::string userRole);

        std::string getAllUsersFromDB();        

        bool isAdministrator(std::string value_uid);

};

#endif