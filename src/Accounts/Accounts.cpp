#include "../headers/Accounts.h"
#include <string.h>
#include <iostream>

Accounts::Accounts(){
    this->Uid = "";
    this->UserName = "";
    this->UserPassword = "";
    this->phoneNumber = " ";
    this->UserEmail = " ";
}

Accounts::~Accounts(){  }

bool Accounts::isNotEmpty(const std::string& str) {
    return !str.empty();
}

void Accounts::setName(std::string valueName){
    if (isNotEmpty(valueName)) {
        this->UserName = valueName;
    } else {
        std::cerr << "Error: User name cannot be empty!" << std::endl;
        logError("Error: User name cannot be empty!");
    }
}

void Accounts::setPassword(std::string valuePassword){
    if (isNotEmpty(valuePassword)) {
        this->UserPassword = valuePassword;
    } else {
        std::cerr << "Error: Password cannot be empty!" << std::endl;
        logError("Error: Password cannot be empty!");
    }   
}

void Accounts::setUID(){
    this->Uid = generateUID();
}

std::string Accounts::getUserName(){
    return UserName;
}

std::string Accounts::getUserPassword(){
    return UserPassword;
}

std::string Accounts::getUID(){
    return Uid;
}