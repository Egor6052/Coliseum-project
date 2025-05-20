#include <iostream>
#include <string>
#include "../../lib/mysql/mysql.h"
#include "../headers/Accounts.h"

std::string Accounts::getUserRole(std::string uid){
    try {
        mysqlConnect();

        // Перевірка, чи існує користувач з таким логіном
        std::string checkQuery = "SELECT role FROM " + getDBUsersName() + " WHERE uid = '" + uid + "'";
        if (mysql_query(conn, checkQuery.c_str())) {
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
            return "User not found";
        }

        // Отримання ролі користувача
        MYSQL_ROW row = mysql_fetch_row(res);
        std::string userRole = row[0];

        mysqlDisconnection(res);

        return userRole;

        } catch (const std::exception &e) {
        std::string errorMessage = "Error: " + std::string(e.what()) + '\n';
        std::cerr << errorMessage;
        logError(errorMessage);
        mysqlDisconnection();
        return "Error";
    }
}