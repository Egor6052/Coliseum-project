#include <iostream>
#include <string.h>
#include "../../lib/UserDB.h"

UserDB::UserDB(){
    this->name = "data_writer";
    this->password = "MySqlStrongPassword123!";
    this->dbName = "SensorData";
    this->dbUsersName = "users";
}
UserDB::~UserDB(){  }

void UserDB::setAdminPassword(std::string valueAdminPassword){
    if (valueAdminPassword == "") {
        std::string errorMessage = "\033[32mError: Password must not be null!\033[0m\n";
        std::cerr << errorMessage;
        logError(errorMessage);
    }
    this->adminPassword = valueAdminPassword;
}

std::string UserDB::getAdminPassword(){
    return adminPassword;
}

std::string UserDB::getDBName(){
    return this->dbName;
}

std::string UserDB::getDBUsersName(){
    return this->dbUsersName;
}

std::string UserDB::getUserDBName(){
    return this->name;
}
std::string UserDB::getUserDBPassword(){
    return this->password;
}

std::string UserDB::getUser(){
    std::string user = "Name: " + name + "\npassword: " + password;
    return user;
}