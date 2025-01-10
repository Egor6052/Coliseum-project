#pragma once
#ifndef USER_H
#define USER_H

#include <iostream>
#include <string.h>

class User {

private:
    int id;
    std::string userName, userPassword;
    std::string hostName;

// DB: server
// User: user1

public:
    User();
    ~User();

    void setID(int valueID);
    int getID();

    void setUserName(std::string nameValue);
    void setUserPassword(std::string passwordValue);
    void setHostName(std::string hostNameValue);

    std::string getUserName();
    std::string getUserPassword();
    std::string getHostName();


    void installDB(std::string valueAnswer);
    void CreateUser(std::string valueAnswer);
    void CreateTable(std::string valueAnswer);

};

#endif