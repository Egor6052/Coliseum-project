#include <iostream>
#include "../../lib/mysql/mysql.h"
#include <nlohmann/json.hpp>
#include <stdexcept>
#include "../headers/Database.h"

Database::Database() {
    // this->data = "";
    // this->ipAddress = "";
    // this->nameSensor = "";
    // this->voltage = 0.0f;
    // this->activePower = 0.0f;
    // this->reactivePower = 0.0f;
}

Database::~Database() {}

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
