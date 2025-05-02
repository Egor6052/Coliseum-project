#include <iostream>
#include "../../lib/mysql/mysql.h"
#include <nlohmann/json.hpp>
#include <stdexcept>
#include "../headers/Database.h"

Database::Database() {
    this->name = "data_writer";
    this->password = "MySqlStrongPassword123!";
    this->dbName = "SensorData";
    this->dbUsersName = "users";
    this->host_name = "localhost";
    this->conn = nullptr;
}

Database::~Database() {
    if (conn) {
        mysql_close(conn);
    }
}

void Database::setData(std::string data, std::string ipAddress, std::string nameSensor, float current, float voltage, float activePower, float reactivePower) {
    try {
        mysqlConnect();

        std::string query = "INSERT INTO " + getDBName() + " (date, ip_address, sensor_name, current, voltage, active_power, reactive_power) VALUES ('" +
                            data + "', '" + ipAddress + "', '" + nameSensor + "', " + 
                            std::to_string(current) + ", " + 
                            std::to_string(voltage) + ", " + 
                            std::to_string(activePower) + ", " + 
                            std::to_string(reactivePower) + ");";

        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error(mysql_error(conn));
            logError(mysql_error(conn));
        }

        std::cout << "\033[36m Data saved successfully!\033[0m" << std::endl;
        mysqlDisconnection();

    } catch (const std::exception &e) {
        std::string errorMessage = "Error: " + std::string(e.what()) + "\n";
        std::cerr << errorMessage;
        logError(errorMessage);
        mysqlDisconnection();
    }
}


inline void Database::mysqlConnect() {
    conn = mysql_init(nullptr);
    if (!conn) {
        std::string error = "MySQL initialization failed!";
        throw std::runtime_error(error);
        logError(error);
    }

    if (!mysql_real_connect(conn, host_name.c_str(), getUserDBName().c_str(), getUserDBPassword().c_str(), getDBName().c_str(), 0, nullptr, 0)) {
        throw std::runtime_error(mysql_error(conn));
        logError(mysql_error(conn));
    }
}

void Database::mysqlDisconnection(MYSQL_RES* res) {
    if (res) {
        mysql_free_result(res);
    }
    if (conn) {
        mysql_close(conn);
        conn = nullptr;
    }
}

void Database::setAdminPassword(std::string valueAdminPassword){
    if (valueAdminPassword == "") {
        std::string errorMessage = "\033[32mError: Password must not be null!\033[0m\n";
        std::cerr << errorMessage;
        logError(errorMessage);
    }
    this->adminPassword = valueAdminPassword;
}

std::string Database::getAdminPassword(){
    return adminPassword;
}

std::string Database::getDBName(){
    return this->dbName;
}

std::string Database::getDBUsersName(){
    return this->dbUsersName;
}

std::string Database::getUserDBName(){
    return this->name;
}
std::string Database::getUserDBPassword(){
    return this->password;
}

std::string Database::getUser(){
    std::string user = "Name: " + name + "\npassword: " + password;
    return user;
}