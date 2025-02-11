#include "../../lib/Accounts.h"
#include <string.h>

Accounts::Accounts(){
    this->UserName = "";
    this->UserPassword ="";
    this->Uid = "";
}

Accounts::~Accounts(){  }

void Accounts::setName(std::string valueName){
    this->UserName = valueName;
}

void Accounts::setPassword(std::string valuePassword){
    this->UserPassword = valuePassword;
}

void Accounts::registerUser(){

}

std::string Accounts::getUserPassword(){
    return UserPassword;
}

std::string Accounts::getUserName(){
    return UserName;
}