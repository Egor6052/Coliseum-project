#include <iostream>
#include <string.h>
#include <mysql/mysql.h>
#include <nlohmann/json.hpp>
#include <stdexcept>

#include "../headers/UserDB.h"

UserDB::UserDB(){
    this->name = "data_writer";
    this->password = "MySqlStrongPassword123!";
    this->dbName = "SensorData";
    this->dbUsersName = "users";
    this->host_name = "localhost";
    this->conn = nullptr;
}
UserDB::~UserDB(){ 
    if (conn) {
        mysql_close(conn);
    }
}

void UserDB::mysqlConnect() {
    conn = mysql_init(nullptr);
    if (!conn) {
        throw std::runtime_error("MySQL initialization failed!");
        logError("MySQL initialization failed!");
    }

    if (!mysql_real_connect(conn, host_name.c_str(), getUserDBName().c_str(), getUserDBPassword().c_str(), getDBName().c_str(), 0, nullptr, 0)) {
        throw std::runtime_error(mysql_error(conn));
        logError(mysql_error(conn));
    }
}

void UserDB::mysqlDisconnection(MYSQL_RES* res) {
    if (res) {
        mysql_free_result(res);
    }
    if (conn) {
        mysql_close(conn);
        conn = nullptr;
    }
}

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