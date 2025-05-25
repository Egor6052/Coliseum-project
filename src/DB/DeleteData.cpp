#include <iostream>
#include "../../lib/mysql/mysql.h"
#include <nlohmann/json.hpp>
#include <stdexcept>
#include "../headers/Database.h"

void Database::deleteData(std::string valueID) {
    try {
        mysqlConnect();

        std::string useDBQuery = "USE " + getDBName() + ";";
        if (mysql_query(conn, useDBQuery.c_str())) {
            throw std::runtime_error("Failed to switch to database: " + std::string(mysql_error(conn)));
        }

        std::string query = "DELETE FROM " + getTableName() + " WHERE id = " + valueID + ";";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error(mysql_error(conn));
            logError(mysql_error(conn));
        }

        std::cout << "\033[36mNote with ID " << valueID << " deleted successfully.\033[0m" << std::endl;
        mysqlDisconnection();

    } catch (const std::exception &e) {
        std::string errorMessage = "Error: " + std::string(e.what()) + "\n";
        std::cerr << errorMessage;
        logError(errorMessage);
        mysqlDisconnection();
    }
}