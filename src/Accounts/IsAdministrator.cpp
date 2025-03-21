#include <iostream>
#include <string>
#include <mariadb/mysql.h>
#include "../headers/Database.h"

bool Accounts::isAdministrator(std::string login, std::string password) {
    try {
        mysqlConnect();

        // Запит для перевірки ролі користувача за його логіном і паролем
        std::string query = "SELECT role FROM " + getDBUsersName() + " WHERE login = '" + login + "' AND password = '" + password + "'";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
            logError("Failed to execute query: " + std::string(mysql_error(conn)));
        }   

        // Обробка результату запиту
        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
            logError("Failed to store result: " + std::string(mysql_error(conn)));
        }

        MYSQL_ROW row;
        bool isAdmin = false;

        // Перевірка на роль адміністратора
        if ((row = mysql_fetch_row(res))) {
            std::string role = row[0];
            if (role == "admin") {
                isAdmin = true;
            }
        }

        mysqlDisconnection(res);

        return isAdmin;

    } catch (const std::exception &e) {
        std::string errorMessage = "Error: " + std::string(e.what()) + "\n";
        std::cerr << errorMessage;
        logError(errorMessage);
        mysqlDisconnection();
        return false;
    }
}