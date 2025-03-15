#include <iostream>
#include <mysql/mysql.h>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include "../../lib/Database.h"


void Database::deleteData(std::string valueID) {
    try {
        MYSQL *conn = mysql_init(nullptr);
        if (!conn) {
            throw std::runtime_error("MySQL initialization failed!");
            logError("MySQL initialization failed!");
        }

        if (!mysql_real_connect(conn, "localhost", getUserDBName().c_str(), getUserDBPassword().c_str(), getDBName().c_str(), 0, nullptr, 0)) {
            throw std::runtime_error(mysql_error(conn));
            logError(mysql_error(conn));
        }

        std::string query = "DELETE FROM " + getDBName() + " WHERE id = " + valueID + ";";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error(mysql_error(conn));
            logError(mysql_error(conn));
        }

        std::cout << "\033[36mNote with ID " << valueID << " deleted successfully.\033[0m" << std::endl;
        mysql_close(conn);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        logError("Error: " + e.what() + '\n');
    }
}