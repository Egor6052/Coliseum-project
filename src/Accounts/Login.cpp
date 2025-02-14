#include <iostream>
#include <string>
#include <mysql/mysql.h>
#include "../../lib/Database.h"

bool Accounts::Login() {
    try {
        MYSQL *conn = mysql_init(nullptr);
        if (!conn) {
            throw std::runtime_error("MySQL initialization failed!");
        }

        conn = mysql_real_connect(conn, "localhost", getUserDBName().c_str(), getUserDBPassword().c_str(), getDBName().c_str(), 0, nullptr, 0);
        if (!conn) {
            throw std::runtime_error("Failed to connect to MySQL database!");
        }

        // Перевірка, чи існує користувач з таким логіном
        std::string checkQuery = "SELECT * FROM " + getDBUsersName() + " WHERE login = '" + getUserName() + "'";
        if (mysql_query(conn, checkQuery.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
        }

        // Якщо користувача немає в базі
        if (mysql_num_rows(res) == 0) {
            std::cerr << "User not found.\n";
            mysql_free_result(res);
            mysql_close(conn);
            return false;
        }

        // Перевірка пароля
        MYSQL_ROW row = mysql_fetch_row(res);
        std::string storedPassword = row[2];

        if (storedPassword != getUserPassword()) {
            std::cerr << "Incorrect password.\n";
            mysql_free_result(res);
            mysql_close(conn);
            return false;
        }

        mysql_free_result(res);
        mysql_close(conn);
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
}
