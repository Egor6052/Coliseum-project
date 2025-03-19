#include <iostream>
#include <string>
#include <mysql/mysql.h>
#include "../headers/Database.h"

bool Accounts::isAdministrator() {
    try {
        MYSQL *conn = mysql_init(nullptr);
        if (!conn) {
            throw std::runtime_error("MySQL initialization failed!");
            logError("MySQL initialization failed!");
        }

        conn = mysql_real_connect(conn, "localhost", getUserDBName().c_str(), getUserDBPassword().c_str(), getDBName().c_str(), 0, nullptr, 0);
        if (!conn) {
            throw std::runtime_error("Failed to connect to MySQL database!");
            logError("Failed to connect to MySQL database!");
        }

        // Запит для перевірки ролі користувача за його логіном і паролем
        std::string query = "SELECT role FROM " + getDBUsersName() + " WHERE login = '" + getUserName() + "' AND password = '" + getUserPassword() + "'";
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

        mysql_free_result(res);
        mysql_close(conn);

        return isAdmin;

    } catch (const std::exception &e) {
        std::string errorMessage = "Error: " + std::string(e.what()) + "\n";
        std::cerr << errorMessage;
        logError(errorMessage);
        return false;
    }
}
