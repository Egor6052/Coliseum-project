#include "../headers/Accounts.h"
#include <iostream>
#include <string>
#include <sstream>
#include <nlohmann/json.hpp>

std::string Accounts::getUserPassword(const std::string& uid) {
    try {
        mysqlConnect();

        // Окремий запит, оскільки password не включено в getUserData
        std::string query = "SELECT password FROM " + getDBUsersName() + " WHERE uid = '" + uid + "'";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
            logError("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
            logError("Failed to store result: " + std::string(mysql_error(conn)));
        }

        if (mysql_num_rows(res) == 0) {
            std::cerr << "User not found.\n";
            logError("User not found.\n");
            mysqlDisconnection(res);
            return "";
        }

        MYSQL_ROW row = mysql_fetch_row(res);
        std::string password = row[0] ? row[0] : "";

        mysqlDisconnection(res);
        return password;

    } catch (const std::exception& e) {
        std::string errorMessage = "Error: " + std::string(e.what()) + '\n';
        std::cerr << errorMessage;
        logError(errorMessage);
        mysqlDisconnection();
        return "";
    }
}