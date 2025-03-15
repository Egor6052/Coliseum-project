#include <iostream>
#include <mysql/mysql.h>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include "../../lib/Database.h"

Database::Database() {
    this->data = "";
    this->ipAddress = "";
    this->nameSensor = "";
    this->voltage = 0.0f;
    this->activePower = 0.0f;
    this->reactivePower = 0.0f;
}

Database::~Database() {}

void Database::setData() {
    try {
        this->data = getCurrentDateTime();
        this->ipAddress = getIpAddress();
        this->nameSensor = getNameSensor();
        this->current = roundNumber(getCurrent());
        this->voltage = roundNumber(getVoltage());
        this->activePower = roundNumber(getActivePower());
        this->reactivePower = roundNumber(getReactivePower());

        MYSQL *conn = mysql_init(nullptr);
        if (!conn) {
            throw std::runtime_error("MySQL initialization failed!");
            logError("MySQL initialization failed!");
        }

        if (!mysql_real_connect(conn, "localhost", getUserDBName().c_str(), getUserDBPassword().c_str(), getDBName().c_str(), 0, nullptr, 0)) {
            throw std::runtime_error(mysql_error(conn));
            logError(mysql_error(conn));
        }

        // Insert data directly into the table
        std::string query = "INSERT INTO " + getDBName() + " (date, ip_address, sensor_name, current, voltage, active_power, reactive_power) VALUES ('" +
                            data + "', '" + ipAddress + "', '" + nameSensor + "', " + std::to_string(current) + ", " + std::to_string(voltage) + ", " +
                            std::to_string(activePower) + ", " + std::to_string(reactivePower) + ");";

        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error(mysql_error(conn));
            logError(mysql_error(conn));
        }

        std::cout << "\033[36m Data saved successfully!\033[0m" << std::endl;
        mysql_close(conn);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        logError("Error: " + e.what() + '\n');
    }
}
