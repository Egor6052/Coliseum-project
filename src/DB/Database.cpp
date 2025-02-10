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
        }

        if (!mysql_real_connect(conn, "localhost", getUserName().c_str(), getUserPassword().c_str(), getDBName().c_str(), 0, nullptr, 0)) {
            throw std::runtime_error(mysql_error(conn));
        }

        // Insert data directly into the table
        std::string query = "INSERT INTO " + getDBName() + " (date, ip_address, sensor_name, current, voltage, active_power, reactive_power) VALUES ('" +
                            data + "', '" + ipAddress + "', '" + nameSensor + "', " + std::to_string(current) + ", " + std::to_string(voltage) + ", " +
                            std::to_string(activePower) + ", " + std::to_string(reactivePower) + ");";

        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error(mysql_error(conn));
        }

        std::cout << "\033[36m Data saved successfully!\033[0m" << std::endl;
        mysql_close(conn);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}


std::string Database::getData() {
    try {
        MYSQL *conn = mysql_init(nullptr);
        if (!conn) {
            throw std::runtime_error("MySQL initialization failed!");
        }

        if (!mysql_real_connect(conn, "localhost", getUserName().c_str(), getUserPassword().c_str(), getDBName().c_str(), 0, nullptr, 0)) {
            throw std::runtime_error(mysql_error(conn));
        }

        std::string query = "SELECT id, date, ip_address, sensor_name, current, voltage, active_power, reactive_power FROM " + getDBName() + " ORDER BY id DESC;";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error(mysql_error(conn));
        }

        MYSQL_RES *result = mysql_store_result(conn);
        if (!result) {
            throw std::runtime_error(mysql_error(conn));
        }

        nlohmann::json jsonData = nlohmann::json::array();
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            nlohmann::json sensor = {
                {"id", std::stoi(row[0])},
                {"date", row[1]},
                {"ip_address", row[2]},
                {"sensor_name", row[3]},
                {"current", std::stof(row[4])},
                {"voltage", std::stof(row[5])},
                {"active_power", std::stof(row[6])},
                {"reactive_power", std::stof(row[7])}
            };
            jsonData.push_back(sensor);
        }

        mysql_free_result(result);
        mysql_close(conn);

        return jsonData.dump(4);
    } catch (const std::exception &e) {
        nlohmann::json errorResponse = {{"error", e.what()}};
        return errorResponse.dump(4);
    }
}

void Database::deleteData(std::string valueID) {
    try {
        MYSQL *conn = mysql_init(nullptr);
        if (!conn) {
            throw std::runtime_error("MySQL initialization failed!");
        }

        if (!mysql_real_connect(conn, "localhost", getUserName().c_str(), getUserPassword().c_str(), getDBName().c_str(), 0, nullptr, 0)) {
            throw std::runtime_error(mysql_error(conn));
        }

        std::string query = "DELETE FROM " + getDBName() + " WHERE id = " + valueID + ";";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error(mysql_error(conn));
        }

        std::cout << "\033[36mNote with ID " << valueID << " deleted successfully.\033[0m" << std::endl;
        mysql_close(conn);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}
