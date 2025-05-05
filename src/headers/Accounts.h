#pragma once
#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <iostream>
#include <string.h>

#include "Database.h"

class Accounts : public Database {
    private:
    std::string Uid;
    std::string UserName;
    std::string UserPassword;
    std::string UserEmail;

    bool isNotEmpty(const std::string& str);
    std::string generateUID();

    public:
        Accounts();
        ~Accounts();

        void setName(std::string valueName);
        void setPassword(std::string valuePassword);
        void setEmail(std::string valueEmail);

        void registerNewUser(std::string login, std::string password, std::string email, std::string userRole);

        std::string getAllUsersFromDB();

        std::string getUID();
        std::string getUserName(std::string uid);
        std::string getUserPassword(std::string uid);
        std::string getUserEmail(std::string uid);
        std::string getUserRole(std::string uid);

        std::string getUserData();
        bool Login(std::string login, std::string password);
        void handleLoginFromAPI();
        void refreshAccessToken(const std::string& refreshToken);
        void renameData(const std::string& name, const std::string& idEditNameDialog);
        void exportExcelData(const std::string& periodDate);
        void exportCSVData(const std::string& periodDate);
        bool isAdministrator(std::string value_uid);
        
};

#endif