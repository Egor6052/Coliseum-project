#include <iostream>
#include <string.h>
#include "../lib/User.h"

User::User(){
    this->id = 0;
    this->userName = "";
    this->userPassword = "";
    this->hostName = "";
}

User::~User(){}

void User::setID(int valueID) {
    if (valueID > 0) {
        this->id = valueID;
    } else {
        std::cerr << "Invalid ID. It must be a positive integer.\n";
    }
}

void User::setUserName(std::string nameValue) {
    if (!nameValue.empty() && nameValue.length() <= 50) {
        this->userName = nameValue;
    } else {
        std::cerr << "Invalid user name. It must not be empty and should not exceed 50 characters.\n";
    }
}

void User::setUserPassword(std::string passwordValue) {
    if (!passwordValue.empty()) {
        this->userPassword = passwordValue;
    } else {
        std::cerr << "Invalid password. It must not be empty.\n";
    }
}

int User::getID(){
    return id;
}
std::string User::getUserName(){
    return userName;
}
std::string User::getUserPassword(){
    return userPassword;
}



