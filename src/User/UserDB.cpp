#include <iostream>
#include <string.h>
// #include <pqxx/pqxx>
#include "../../lib/UserDB.h"

UserDB::UserDB(){
    this->name = "data_writer";
    this->password = "MySqlStrongPassword123!";
    this->dbName = "SensorData";
}
UserDB::~UserDB(){

}
void UserDB::setName(std::string valueName){
    if (valueName == ""){
        std::cerr << "\033[32mError: Name must not be null!\033[0m" << "\n";
    } else {
        this->name = valueName;
    }
}
void UserDB::setPassword(std::string valuePassword){
    if (valuePassword == "") {
        std::cerr << "\033[32mError: Password must not be null!\033[0m" << "\n";
    }
    this->password = valuePassword;
}

std::string UserDB::getUserPassword(){
    return this->password;
}
std::string UserDB::getUserName(){
    return this->name;
}
std::string UserDB::getDBName(){
    return this->dbName;
}

std::string UserDB::getUser(){
    std::string user = "Name: " + name + "\npassword: " + password;
    return user;
}