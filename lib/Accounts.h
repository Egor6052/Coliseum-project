#pragma once
#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <iostream>
#include <string.h>

class Accounts {
    private:
    std::string UserName; 
    std::string UserPassword;
    std::string Uid;

    public:
        Accounts();
        ~Accounts();

        void setName(std::string valueName);
        void setPassword(std::string valuePassword);
        void registerUser();

        std::string getUserPassword();
        std::string getUserName();
};

#endif