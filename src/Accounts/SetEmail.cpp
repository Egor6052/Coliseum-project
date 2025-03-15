#include "../../lib/Accounts.h"
#include <string>
#include <iostream>
#include <mysql/mysql.h>
#include <regex>
#include <stdexcept>

void Accounts::setEmail(std::string uid, std::string valueEmail) {
    std::regex emailRegex(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");

    if (!std::regex_match(valueEmail, emailRegex)) {
        throw std::invalid_argument("Invalid email format!");
        logError("Invalid email format!");
    }

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

        // SQL-запит для оновлення email користувача за UID
        std::string updateQuery = "UPDATE " + getDBUsersName() + 
                                " SET email = '" + valueEmail + 
                                "' WHERE uid = '" + uid + "'";

        if (mysql_query(conn, updateQuery.c_str())) {
            throw std::runtime_error("Failed to update email: " + std::string(mysql_error(conn)));
            logError("Failed to update email: " + std::string(mysql_error(conn)));
        }

        mysql_close(conn);

        // Зберігаємо новий email у класі
        this->UserEmail = valueEmail;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        logError("Error: " + e.what());
        throw;
    }
}

std::string Accounts::getUserEmail() {
    return this->UserEmail;
}
