#include "../headers/Accounts.h"
#include <iostream>
#include <string>
#include <sstream>

std::string Accounts::getUserData(const std::string& uid) {
    try {
        mysqlConnect();
        std::string useDBQuery = "USE " + getDBName() + ";";
        if (mysql_query(conn, useDBQuery.c_str())) {
            throw std::runtime_error("Failed to switch to database: " + std::string(mysql_error(conn)));
        }

        // Запит для отримання даних користувача
        std::string query = "SELECT uid, name, email, role FROM " + getDBUsersName() + " WHERE uid = '" + uid + "'";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
            logError("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
            logError("Failed to store result: " + std::string(mysql_error(conn)));
        }

        // Якщо користувача немає в базі
        if (mysql_num_rows(res) == 0) {
            std::cerr << "User not found.\n";
            logError("User not found.\n");
            mysqlDisconnection(res);
            return "{\"error\": \"User not found\"}";
        }

        // Отримання даних користувача
        MYSQL_ROW row = mysql_fetch_row(res);
        std::string userUID = row[0] ? row[0] : "";
        std::string userName = row[1] ? row[1] : "";
        std::string userEmail = row[2] ? row[2] : "";
        std::string userRole = row[3] ? row[3] : "";

        // Формування JSON-рядка
        std::stringstream json;
        json << "{"
            << "\"uid\": \"" << userUID << "\", "
            << "\"name\": \"" << userName << "\", "
            << "\"email\": \"" << userEmail << "\", "
            << "\"role\": \"" << userRole << "\""
        << "}";

        mysqlDisconnection(res);

        return json.str();

    } catch (const std::exception& e) {
        std::string errorMessage = "Error: " + std::string(e.what()) + '\n';
        std::cerr << errorMessage;
        logError(errorMessage);
        mysqlDisconnection();
        return "{\"error\": \"Error retrieving user data\"}";
    }
}