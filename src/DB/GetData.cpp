#include <iostream>
#include "../../lib/mysql/mysql.h"
#include <nlohmann/json.hpp>
#include <stdexcept>
#include "../headers/Database.h"

std::string Database::getData() {
    try {
        mysqlConnect();

        std::string query = "SELECT id, date, ip_address, sensor_name, current, voltage, active_power, reactive_power FROM " + getDBName() + " ORDER BY id DESC;";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error(mysql_error(conn));
            logError(mysql_error(conn));
        }

        MYSQL_RES *result = mysql_store_result(conn);
        if (!result) {
            throw std::runtime_error(mysql_error(conn));
            logError(mysql_error(conn));
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

        mysqlDisconnection(result);

        return jsonData.dump(4);
    } catch (const std::exception &e) {
        nlohmann::json errorResponse = {{"error", e.what()}};
        logError(errorResponse);
        mysqlDisconnection(nullptr);
        return errorResponse.dump(4);
    }
}