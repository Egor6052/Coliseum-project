#include "../headers/Accounts.h"
#include <iostream>
#include <string>
#include <sstream>

std::string Accounts::getUserData(std::string uid) {
    try {
        mysqlConnect();

        // Запит для отримання даних користувача
        std::string query = "SELECT uid, name, email FROM " + getDBUsersName() + " WHERE uid = '" + uid + "'";
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

        // Формування JSON-рядка
        std::stringstream json;
        json << "{"
                << "\"uid\": \"" << userUID << "\", "
                << "\"name\": \"" << userName << "\", "
                << "\"email\": \"" << userEmail << "\""
                << "}";

        mysqlDisconnection(res);

        return json.str();

    } catch (const std::exception &e) {
        std::string errorMessage = "Error: " + std::string(e.what()) + '\n';
        std::cerr << errorMessage;
        logError(errorMessage);
        mysqlDisconnection();
        return "{\"error\": \"Error retrieving user data\"}";
    }
}