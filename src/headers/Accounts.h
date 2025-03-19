#pragma once
#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <iostream>
#include <string.h>

#include "UserDB.h"
#include "Logger.h"

class Accounts : public UserDB {
    private:
    std::string Uid;
    std::string UserName; 
    std::string UserPassword;
    std::string phoneNumber;
    std::string UserEmail;

    bool isNotEmpty(const std::string& str);
    std::string generateUID();

    public:
        Accounts();
        ~Accounts();

        void setUID();
        void setName(std::string valueName);
        void setPassword(std::string valuePassword);
        void setPhoneNumber(std::string uid, std::string valuePhoneNumber);
        void setEmail(std::string uid, std::string valueEmail);
        // void registerUser();

        void registerAsUser();
        void registerAsAdmin();

        // void sendToEmail();

        std::string getAllUsersFromDB();
        std::string getAllAdminsFromDB();

        std::string getUID();
        std::string getUserName();
        std::string getUserPassword();
        std::string getUserPhoneNumber();
        std::string getUserEmail();

        std::string getUserData();

        bool Login();
        bool isAdministrator();
        
};

#endif